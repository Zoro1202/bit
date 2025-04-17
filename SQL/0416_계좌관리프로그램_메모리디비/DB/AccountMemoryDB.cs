using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0416_계좌관리프로그램_메모리디비
{
    class AccountMemoryDB
    {
        private DataTable account_table = null;
        public DataTable AccountTable
        {
            get { return account_table; }
        }

        private DataTable accountIO_table = null;
        public DataTable AccountIOTable
        {
            get { return accountIO_table; }
        }

        private DataSet accountDataset = new DataSet("Dataset");
        public DataSet AccountDataset
        {
            get { return accountDataset; }
        }

        //---------------------DATASET-------------------------
        #region 데이터셋 만들기
        public void InitData()
        {
            Account_ReadXML();
            AccountIO_ReadXML();
            Dataset_ReadXML();
        }
        public void InitFirstData()
        {
            accountDataset.Tables.Clear();
            CreateAccoutTable();
            CreateAccoutIOTable();

            DataColumn parentColumn = accountDataset.Tables["Account"].Columns["ID"];
            DataColumn childColumn = accountDataset.Tables["AccountIO"].Columns["Number"];

            DataRelation relation = new DataRelation("계좌정보", parentColumn, childColumn);
            accountDataset.Relations.Add(relation);

            Console.WriteLine("데이터셋 성공.");
        }

        public void Dataset_WriteXML()
        {
            accountDataset.WriteXmlSchema("datasets.xsd");
            accountDataset.WriteXml("datasets.xml");
        
        }
        public void Dataset_ReadXML()
        {
            if (accountDataset != null)
            {
                accountDataset.Dispose();
            }
            accountDataset = new DataSet();
            accountDataset.ReadXmlSchema("datasets.xsd");
            accountDataset.ReadXml("datasets.xml");
        }

        #endregion


        #region View Relations
        public void ViewRelations()
        {
            DataRelationCollection drc = accountDataset.Relations;
            Console.WriteLine($"관계 수 {drc.Count}");
            foreach (DataRelation dr in drc)
            {
                Console.WriteLine($"관계명 {dr.RelationName}");
                DataColumn dc_parent = dr.ParentColumns[0];
                DataColumn dc_child = dr.ChildColumns[0];
                Console.WriteLine($"부모:{dc_parent.Table.TableName}-{dc_parent.ColumnName}");
                Console.WriteLine($"자식:{dc_child.Table.TableName}-{dc_child.ColumnName}");
            }
        }
        public void ViewTalbes()
        {
            DataTableCollection dtc = accountDataset.Tables;
            foreach (DataTable dt in dtc)
            {
                int row_count = dt.Rows.Count;
                Console.WriteLine($"테이블명: {dt.TableName}");
                Console.WriteLine($"행 개수: {row_count}");
                for (int i = 0; i < row_count; i++)
                {
                    DataRow dr = dt.Rows[i];
                    foreach (DataColumn dc in dt.Columns)
                    {
                        Console.WriteLine($"{dc.ColumnName}:{dr[dc]}");
                    }
                }
            }
        }
        #endregion
        //---------------------ACCOUNT-----------------------
        #region 데이터 테이블 생성 및 스키마 출력
        public void CreateAccoutTable()
        {
            if (account_table != null)
            {
                account_table.Dispose();
            }
            account_table = new DataTable("Account");

            DataColumn col_id = new DataColumn("ID", typeof(int));
            col_id.AutoIncrement = true;
            col_id.AutoIncrementSeed = 1000;
            col_id.AutoIncrementStep = 10;
            account_table.Columns.Add(col_id);

            DataColumn col_name = new DataColumn("Name", typeof(string));
            col_name.AllowDBNull = false;
            account_table.Columns.Add(col_name);

            DataColumn col_balance = new DataColumn("balance", typeof(int));
            col_balance.AllowDBNull = false;
            col_balance.DefaultValue = 0;
            account_table.Columns.Add(col_balance);

            DataColumn col_date = new DataColumn("date", typeof(DateTime));
            col_date.AllowDBNull = false;
            col_date.DefaultValue = DateTime.Now;
            account_table.Columns.Add(col_date);

            DataColumn[] pk = new DataColumn[1];
            pk[0] = col_id;
            account_table.PrimaryKey = pk;

            accountDataset.Tables.Add(account_table);
        }
        public void PrintTableSchema(DataTable dt)
        {
            Console.WriteLine("테이블 명: " + dt.TableName);
            Console.WriteLine("Columns Count :" + dt.Columns.Count);
            Console.WriteLine("Rows Count :" + dt.Rows.Count);
            Console.WriteLine("Pk : " + dt.PrimaryKey[0]);
            Console.WriteLine("------------------------------------");
            foreach (DataColumn col in dt.Columns)
            {
                Console.Write($"Column Name : {col.ColumnName} \t| ");
                Console.Write($"Column Type : {col.DataType} \t| ");
                Console.Write($"Allow Null : {col.AllowDBNull} \t| ");
                Console.WriteLine($"Default Value : {col.DefaultValue}");
            }
            Console.WriteLine("------------------------------------");
        }
        #endregion

        #region Account Table Insert
        public int Account_Insert(string name, int balance, DateTime date)
        {
            try
            {
                DataRow r = account_table.NewRow();
                r["Name"] = name;
                r["balance"] = balance;
                r["date"] = date;
                account_table.Rows.Add(r);
                Console.WriteLine("저장 성공");
                return int.Parse(r["ID"].ToString());
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        public int Account_Insert(string name, int balance)
        {
            try
            {
                DataRow r = account_table.NewRow();
                r["Name"] = name;
                r["balance"] = balance;
                account_table.Rows.Add(r);
                Console.WriteLine("저장 성공");
                return int.Parse(r["ID"].ToString());
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        public int Account_Insert(string name)
        {
            try
            {
                DataRow r = account_table.NewRow();
                r["Name"] = name;
                account_table.Rows.Add(r);
                Console.WriteLine("저장 성공");
                return int.Parse(r["ID"].ToString());
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        #endregion

        #region Account Table Select
        public List<Account> SelectAllAccount()
        {
            List<Account> list = new List<Account>();
            int row_count = account_table.Rows.Count;
            foreach (DataRow dr in account_table.Rows)
            {
                int id = int.Parse(dr["ID"].ToString());
                string name = dr["Name"].ToString();
                int balance = int.Parse(dr["balance"].ToString());
                DateTime time = DateTime.Parse(dr["date"].ToString());
                list.Add(new Account(id, name, balance, time));
            }
            return list;
        }
        public Account SelectAccountNumber(int _id)
        {
            try
            {
                DataRow dr = account_table.Rows.Find(_id);

                int id = int.Parse(dr["ID"].ToString());
                string name = dr["Name"].ToString();
                int balance = int.Parse(dr["balance"].ToString());
                DateTime time = DateTime.Parse(dr["date"].ToString());
                Account account = new Account(id, name, balance, time);
                return account;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"{ex.Message}");
                return null;
            }
        }
        #endregion

        #region Account Delete
        public void DeleteAccount(int _id)
        {
            try
            {
                DataRow dr = account_table.Rows.Find(_id);
                account_table.Rows.Remove(dr);
                Console.WriteLine("삭제 성공");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"{ex.Message}");
            }
        }
        #endregion

        #region Account Update
        public int UpdateAccount_Input(int _id, int money)
        {
            try
            {
                DataRow dr = account_table.Rows.Find(_id);
                int balance = int.Parse(dr["balance"].ToString());
                dr["balance"] = balance + money;

                Console.WriteLine($"입금 성공 +{money}");
                return balance;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"입금 실패 : {ex.Message}");
                return 0;
            }
        }
        public int UpdateAccount_Output(int _id, int money)
        {
            try
            {
                DataRow dr = account_table.Rows.Find(_id);
                int balance = int.Parse(dr["balance"].ToString());
                if (balance - money > 0)
                {
                    dr["balance"] = balance - money;
                }
                else
                {
                    throw new Exception("잔액 부족");
                }

                Console.WriteLine($"입금 성공 +{money}");
                return balance;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"입금 실패 : {ex.Message}");
                return 0;
            }
        }
        #endregion

        #region XML save / load
        public void Account_WriteXML()
        {
            account_table.WriteXmlSchema("accounts.xsd", true);
            account_table.WriteXml("accounts.xml");
        }
        public void Account_ReadXML()
        {
            if (account_table != null)
            {
                account_table.Dispose();
            }
            account_table = new DataTable("Account");
            account_table.ReadXmlSchema("accounts.xsd");
            account_table.ReadXml("accounts.xml");
        }
        #endregion
        //--------------------ACCOUNT IO---------------------
        #region 데이터 테이블 생성 및 스키마 출력
        public void CreateAccoutIOTable()
        {
            if (accountIO_table != null)
            {
                accountIO_table.Dispose();
            }

            accountIO_table = new DataTable("AccountIO");

            DataColumn col_id = new DataColumn("ID", typeof(int));
            col_id.AutoIncrement = true;
            col_id.AutoIncrementSeed = 1;
            col_id.AutoIncrementStep = 1;
            accountIO_table.Columns.Add(col_id);

            DataColumn col_accNum = new DataColumn("Number", typeof(int));
            col_accNum.AllowDBNull = false;
            col_accNum.DefaultValue = 0;
            accountIO_table.Columns.Add(col_accNum);

            DataColumn col_input = new DataColumn("Input", typeof(int));
            col_input.AllowDBNull = false;
            col_input.DefaultValue = 0;
            accountIO_table.Columns.Add(col_input);

            DataColumn col_output = new DataColumn("Output", typeof(int));
            col_output.AllowDBNull = false;
            col_output.DefaultValue = 0;
            accountIO_table.Columns.Add(col_output);

            DataColumn col_balance = new DataColumn("Balance", typeof(int));
            col_balance.AllowDBNull = false;
            col_balance.DefaultValue = 0;
            accountIO_table.Columns.Add(col_balance);

            DataColumn col_date = new DataColumn("Date", typeof(DateTime));
            col_date.AllowDBNull = false;
            col_date.DefaultValue = DateTime.Now;
            accountIO_table.Columns.Add(col_date);

            DataColumn[] pk = new DataColumn[1];
            pk[0] = col_id;
            accountIO_table.PrimaryKey = pk;

            accountDataset.Tables.Add(accountIO_table);
        }
        public void PrintIOTableSchema(DataTable dt)
        {
            Console.WriteLine("테이블 명: " + dt.TableName);
            Console.WriteLine("Columns Count :" + dt.Columns.Count);
            Console.WriteLine("Rows Count :" + dt.Rows.Count);
            Console.WriteLine("Pk : " + dt.PrimaryKey[0]);
            Console.WriteLine("------------------------------------");
            foreach (DataColumn col in dt.Columns)
            {
                Console.Write($"Column Name : {col.ColumnName} \t| ");
                Console.Write($"Column Type : {col.DataType} \t| ");
                Console.Write($"Allow Null : {col.AllowDBNull} \t| ");
                Console.WriteLine($"Default Value : {col.DefaultValue}");
            }
            Console.WriteLine("------------------------------------");
        }
        #endregion

        #region AccountIO Table Insert
        public void AccountIO_Insert(int acc, int Input, int output, int balance, DateTime date)
        {
            try
            {
                DataRow r = accountIO_table.NewRow();
                r["Number"] = acc;
                r["Input"] = Input;
                r["Output"] = output;
                r["balance"] = balance;
                r["date"] = date;
                accountIO_table.Rows.Add(r);
                Console.WriteLine("저장 성공");
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        public void AccountIO_Insert(int acc, int Input, int output, int balance)
        {
            try
            {
                DataRow r = accountIO_table.NewRow();
                r["Number"] = acc;
                r["Input"] = Input;
                r["Output"] = output;
                r["balance"] = balance;
                accountIO_table.Rows.Add(r);
                Console.WriteLine("저장 성공");
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        #endregion

        #region AccountIO Table Select
        public List<AccountIO> SelectAllAccountIO()
        {
            List<AccountIO> list = new List<AccountIO>();
            int row_count = accountIO_table.Rows.Count;
            foreach (DataRow dr in accountIO_table.Rows)
            {
                int id = int.Parse(dr["ID"].ToString());
                int accNum = int.Parse(dr["Number"].ToString());
                int input = int.Parse(dr["Input"].ToString());
                int output = int.Parse(dr["Output"].ToString());
                int balance = int.Parse(dr["balance"].ToString());
                DateTime time = DateTime.Parse(dr["date"].ToString());
                list.Add(new AccountIO(id, accNum, input, output, balance, time));
            }
            return list;
        }

        public AccountIO SelectAccountIOID(int _id)
        {
            try
            {
                DataRow dr = accountIO_table.Rows.Find(_id);

                int id = int.Parse(dr["ID"].ToString());
                int accNum = int.Parse(dr["Number"].ToString());
                int input = int.Parse(dr["Input"].ToString());
                int output = int.Parse(dr["Output"].ToString());
                int balance = int.Parse(dr["balance"].ToString());
                DateTime time = DateTime.Parse(dr["date"].ToString());
                AccountIO account = new AccountIO(id, accNum, input, output, balance, time);
                return account;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"{ex.Message}");
                return null;
            }
        }
        #endregion

        #region AccountIO Delete
        public void DeleteAccountIO(int _id)
        {
            try
            {
                DataRow[] dataRowArray = AccountIOTable.Select($"Number = {_id}");
                foreach (DataRow row in dataRowArray)
                {
                    accountIO_table.Rows.Remove(row);
                }
                Console.WriteLine("삭제 성공");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"{ex.Message}");
            }
        }
        #endregion

        #region XML save / load
        public void AccountIO_WriteXML()
        {
            accountIO_table.WriteXmlSchema("accountIOs.xsd", true);
            accountIO_table.WriteXml("accountIOs.xml");
        }
        public void AccountIO_ReadXML()
        {
            if (accountIO_table != null)
            {
                accountIO_table.Dispose();
            }
            accountIO_table = new DataTable("AccountIO");
            accountIO_table.ReadXmlSchema("accountIOs.xsd");
            accountIO_table.ReadXml("accountIOs.xml");
        }
        #endregion
        

    }
}
