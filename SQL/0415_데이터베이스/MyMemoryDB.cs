//MyMemoryDB.cs
//메모리 DB를 직접 생성하고 구현.
using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlTypes;
using System.Linq;
using System.Security.Principal;
using System.Text;
using System.Threading.Tasks;

namespace _0415_데이터베이스
{
    class MyMemoryDB
    {
        private DataTable account_table = null;
        public DataTable AccountTable
        {
            get { return account_table; }
        }

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
        public void Account_Insert(string name, int balance, DateTime date)
        {
            try
            {
                DataRow r = account_table.NewRow();
                r["Name"] = name;
                r["balance"] = balance;
                r["date"] = date;
                account_table.Rows.Add(r);
                Console.WriteLine("저장 성공");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        public void Account_Insert(string name, int balance)
        {
            try
            {
                DataRow r = account_table.NewRow();
                r["Name"] = name;
                r["balance"] = balance;
                account_table.Rows.Add(r);
                Console.WriteLine("저장 성공");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        public void Account_Insert(string name)
        {
            try
            {
                DataRow r = account_table.NewRow();
                r["Name"] = name;
                account_table.Rows.Add(r);
                Console.WriteLine("저장 성공");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
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

        public Account SelectAccount(int _id)
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
        public void UpdateAccount_Input(int _id, int money)
        {
            try
            {
                DataRow dr = account_table.Rows.Find(_id);
                int balance = int.Parse(dr["balance"].ToString());
                dr["balance"] = balance + money;

                Console.WriteLine($"입금 성공 +{money}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"입금 실패 : {ex.Message}");
            }
        }
        #endregion

        #region XML
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
            #endregion
        }
    }
}
