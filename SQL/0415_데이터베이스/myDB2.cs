using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Security.Cryptography;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace _0415_데이터베이스
{
    class myDB2
    {
        private const string server_name = "DESKTOP-JUDP5QH\\SQLEXPRESS";
        private const string db_name = "wb41";
        private const string sql_id = "aaa";
        private const string sql_pw = "1234";

        private SqlConnection scon = null;

        private SqlDataAdapter sqlDataAdapter = new SqlDataAdapter();
        private DataSet ds = new DataSet("WB41");

        public myDB2()
        {
            string con = string.Format($"Data Source={server_name};Initial Catalog={db_name};User ID={sql_id};Password={sql_pw}");
            scon = new SqlConnection(con);

            sqlDataAdapter.SelectCommand = SelectAllCustomCommand();
            sqlDataAdapter.InsertCommand = InsertCustomCommand();
            sqlDataAdapter.UpdateCommand = UpdateCustomCommand();
            sqlDataAdapter.DeleteCommand = DeleteCustomCommand();
        }

        #region Select (Fill, 비연결형)
        public List<string> SelectAllCustom()
        {
            sqlDataAdapter.MissingSchemaAction = MissingSchemaAction.AddWithKey;
            sqlDataAdapter.Fill(ds, "s_Custom");

            PrintTableSchema(ds.Tables["s_Custom"]);
            return CustomToString(ds.Tables["s_Custom"]);
        }
        private SqlCommand SelectAllCustomCommand()
        {
            string comstr = "select * from s_custom"; 
            SqlCommand comm = new SqlCommand(comstr, scon);
            return comm;
        }
        private List<string> CustomToString(DataTable dt)
        {
            List<string> list = new List<string>();
            foreach (DataRow row in dt.Rows)
            {
                string str = string.Empty;
                str += row[0] + "#";
                str += row[1] + "#";
                str += row[2] + "#";
                str += row[3];
                list.Add(str);
            }
            return list;
        }
        #endregion

        #region Insert, 메모리디비에서 수행함, 업데이트 안하면 DB에는 안올라감
        //이름, 전화번호, 주소
        public void InsertCustom(string name, string phone, string address)
        {
            try
            {
                DataRow r = ds.Tables["s_Custom"].NewRow();
                r["cName"] = name;
                r["phone"] = phone;
                r["addr"] = address;
                ds.Tables["s_Custom"].Rows.Add(r);
                Console.WriteLine("저장 성공");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
        public SqlCommand InsertCustomCommand()
        {
            string strcom = "insert into s_custom values(@Name1, @Phone, @Addr)";
            SqlCommand comm = new SqlCommand(strcom, scon);
            comm.Parameters.Add("@Name1", SqlDbType.VarChar, 50, "cname");
            comm.Parameters.Add("@Phone", SqlDbType.VarChar, 50, "phone");
            comm.Parameters.Add("@Addr", SqlDbType.VarChar, 50, "addr");
            return comm;
        }
        #endregion

        #region Update (비동기)
        public void UpdateCustom(int cid, string phone, string address)
        {
            try
            {
                DataRow dr = ds.Tables["s_Custom"].Rows.Find(cid);

                dr["phone"] = phone;
                dr["Addr"] = address;

                Console.WriteLine($"수정 성공");
                MemoryToDBCustom(); // DB에 업데이트, 동기화
            }
            catch (Exception ex)
            {
                Console.WriteLine($"수정 실패 : {ex.Message}");
            }
        }
        private SqlCommand UpdateCustomCommand()
        {
            string strcom = "update s_Custom set phone = @Phone, Addr = @Addr where cid = @Cid";
            SqlCommand comm = new SqlCommand(strcom, scon);
            comm.Parameters.Add("@Phone", SqlDbType.VarChar, 50, "phone");
            comm.Parameters.Add("@Addr", SqlDbType.VarChar, 50, "addr");
            comm.Parameters.Add("@Cid", SqlDbType.Int, 4, "Cid");
            return comm;
        }
        #endregion

        #region Delete
        public void DeleteCustom(int cid)
        {
            try
            {
                DataRow dr = ds.Tables["s_Custom"].Rows.Find(cid);
                dr.Delete();
                Console.WriteLine("삭제 성공");

                MemoryToDBCustom(); // DB에 업데이트, 동기화
                ds.Tables["s_Custom"].Rows.Remove(dr);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"{ex.Message}");
            }
        }

        private SqlCommand DeleteCustomCommand()
        {
            string strcom = "delete from s_Custom where CID = @cid";
            SqlCommand comm = new SqlCommand(strcom, scon);
            comm.Parameters.Add("@cid", SqlDbType.Int, 4, "cid");
            return comm;
        }
        #endregion

        #region Update (디비에 올리기)
        public void MemoryToDBCustom()
        {
            sqlDataAdapter.Update(ds,"s_Custom");
        }
        #endregion

        #region 테이블 스키마 출력
        public void PrintTableSchema(DataTable dt)
        {
            Console.WriteLine("테이블 명: " + dt.TableName);
            Console.WriteLine("Columns Count :" + dt.Columns.Count);
            Console.WriteLine("Rows Count :" + dt.Rows.Count);
            Console.WriteLine("Pk : " + dt.PrimaryKey.ElementAtOrDefault(0));
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
    }
}
