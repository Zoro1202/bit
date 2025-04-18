//MyDB.cs
using System;
using System.Data.SqlClient;

namespace _0415_데이터베이스
{
    internal class MyDB
    {
        private const string server_name = "DESKTOP-0I86BTV\\SQLEXPRESS";
        private const string db_name = "wb41";
        private const string sql_id = "aaa";
        private const string sql_pw = "1234";

        private SqlConnection scon = null;

        #region 연결, 종료
        public bool Connect()
        {
            try
            {
                string con = string.Format($"Data Source={server_name};Initial Catalog={db_name};User ID={sql_id};Password={sql_pw}");
                scon = new SqlConnection(con);
                scon.Open();
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return false;
            }
        }
        public bool Close()
        {
            try
            {
                scon.Close();
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return false;
            }
        }
        #endregion

        #region Insert, Update, Delete Test
        //INSERT INTO s_product VALUES('C# Network', 20000, 'C# Network 설명...');
        public bool Insert_Book(string name, int price, string description)
        {
            string sql = string.Format($"INSERT INTO s_product VALUES('{name}', {price}, '{description}')");
            return ExSqlCommand(sql);
        }
        //update s_product set price = 25000 where pid = 1010;
        public bool Update_Book1(int pid, int price)
        {
            string sql = string.Format($"update s_product set price = {price} where pid = {pid};");
            return ExSqlCommand(sql);
        }
        //update s_product set price = 25000 where pname = 'C언어';
        public bool update_Book2(string name, int price)
        {
            string sql = string.Format($"update s_product set price = {price} where pname = '{name}';");
            return ExSqlCommand(sql);
        }
        //delete from s_product where pid=20000;
        public bool Delete_Book1(int pid)
        {
            string sql = string.Format($"delete from s_product where pid={pid};");
            return ExSqlCommand(sql);
        }
        //delete from s_product where pname='C#';
        public bool Delete_Book2(string name)
        {
            string sql = string.Format($"delete from s_product where pname='{name}';");
            return ExSqlCommand(sql);
        }
        #endregion

        #region 하나의 값을 반환하는 Select
        //select SUM(Price) from s_product;
        public int Get_TotalPrice()
        {
            string sql = string.Format($"select SUM(Price) from s_product;");
            object obj = ExSqlScalarCommand(sql);
            if (obj == null)
                throw new Exception("오류 발생");
            return (int)obj;                
        }
        //select MAX(Price) from s_product;
        public int Get_MaxPrice()
        {
            string sql = string.Format($"select MAX(Price) from s_product;");
            object obj = ExSqlScalarCommand(sql);
            if (obj == null)
                throw new Exception("오류 발생");
            return (int)obj;
        }
        #endregion 

        #region DB 명령 함수(ExecuteNonQuery:I,U,D),(ExcecuteScalar:S)
        private bool ExSqlCommand(string sql)
        {
            try
            {
                SqlCommand scom = new SqlCommand();
                scom.Connection = scon;
                scom.CommandText = sql;

                if (scom.ExecuteNonQuery() == 0)
                    return false;
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return false;
            }
        }

        private object ExSqlScalarCommand(string sql)
        {
            try
            {
                SqlCommand scom = new SqlCommand();
                scom.Connection = scon;
                scom.CommandText = sql;

                return scom.ExecuteScalar();          
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return null;
            }
        }
        #endregion 
    }
}
