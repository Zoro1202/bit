using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0415_데이터베이스
{
    class MyDB1
    {
        private const string server_name = "DESKTOP-JUDP5QH\\SQLEXPRESS";
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

        #region sqlProcedure Test
        public void AddProduct(string pname, int price, string description)
        {
            string comtext = "AddProduct";

            SqlCommand cmd = new SqlCommand(comtext, scon);

            cmd.CommandType = CommandType.StoredProcedure;


            SqlParameter param_pname = new SqlParameter("@pname", pname);
            cmd.Parameters.Add(param_pname);

            SqlParameter param_price = new SqlParameter();
            param_price.ParameterName = "@price";
            param_price.SqlDbType = SqlDbType.Int;
            param_price.Value = price;
            cmd.Parameters.Add(param_price);

            SqlParameter param_description = new SqlParameter("@Description", description);
            cmd.Parameters.Add(param_description);

            if (ExSqlCommand(cmd) == true)
            {
                Console.WriteLine("AddProduct 성공");
            }
            else
            {
                Console.WriteLine("AddProduct 실패");
            }

            cmd.Dispose();
        }
        public void FindCIDByName(string name)
        {
            string comtext = "FindCIDByName";

            SqlCommand cmd = new SqlCommand(comtext, scon);
            cmd.CommandType = CommandType.StoredProcedure;

            SqlParameter param_name = new SqlParameter("@cname", name);
            cmd.Parameters.Add(param_name);

            SqlParameter param_cid = new SqlParameter("@cid", SqlDbType.Int);
            param_cid.Direction = ParameterDirection.Output;
            cmd.Parameters.Add(param_cid);

            if (ExSqlCommand(cmd) == true)
            {
                Console.WriteLine("FindCIDByName 성공");
                Console.WriteLine("cid : " + param_cid.Value.ToString());
            }
            else
            {
                Console.WriteLine("FindCIDByName 실패");
            }
            cmd.Dispose();
        }
        #endregion

        #region DB 명령 함수(ExecuteNonQuery:I,U,D),(ExcecuteScalar:S)
        private bool ExSqlCommand(SqlCommand scom)
        {
            try
            {
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
