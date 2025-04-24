using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0424_chat_client
{
    class myDB
    {
        private const string server_name = "DESKTOP-JUDP5QH\\SQLEXPRESS";
        private const string db_name = "wb41";
        private const string sql_id = "aaa";
        private const string sql_pw = "1234";

        private SqlConnection scon = null;




        public myDB()
        {
            string con = string.Format($"Data Source={server_name};Initial Catalog={db_name};User ID={sql_id};Password={sql_pw}");
            scon = new SqlConnection(con);

            
            //sqlDataAdapter.InsertCommand = InsertCustomCommand();
            //sqlDataAdapter.UpdateCommand = UpdateCustomCommand();
            //sqlDataAdapter.DeleteCommand = DeleteCustomCommand();
        }

        #region Select (Fill, 비연결형)
        public DataTable GetMemberTable()
        {
            SqlDataAdapter sqlDataAdapter = new SqlDataAdapter();
            sqlDataAdapter.SelectCommand = SelectAllCustomCommand();
            sqlDataAdapter.MissingSchemaAction = MissingSchemaAction.AddWithKey;

            DataTable m_Table = new DataTable("member");
            sqlDataAdapter.Fill(m_Table);

            return m_Table;
        }
        private SqlCommand SelectAllCustomCommand()
        {
            string comstr = "select * from Member";
            SqlCommand comm = new SqlCommand(comstr, scon);
            return comm;
        }
        #endregion

    }
}
