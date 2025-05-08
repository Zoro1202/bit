using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using static System.Net.Mime.MediaTypeNames;

namespace _0507_도서관리_WCFService
{
    class MyDB
    {
        private const string server_name = "COMP\\SQLEXPRESS";
        private const string db_name = "WB41";
        private const string sql_id = "aaa";
        private const string sql_pw = "1234";

        private SqlConnection sqlConnection = null; // Changed from const to instance field  

        public bool connect()
        {
            try
            {
                string con = string.Format($"Data Source={server_name};Initial Catalog={db_name};User ID={sql_id};Password={sql_pw}");

                sqlConnection = new SqlConnection(con);
                sqlConnection.Open();
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
                sqlConnection.Close();
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return false;
            }
        }
        // 파일 경로로 이미지 DB에 저장
        public bool InsertBook(string title, string author, int price, byte[] image)
        {
            string sql = "INSERT INTO books (title, author, price, image) VALUES (@title, @author, @price, @imagedata)";
            SqlCommand sComm = new SqlCommand(sql, sqlConnection);
            sComm.Parameters.AddWithValue("@title", title);
            sComm.Parameters.AddWithValue("@author", author);
            sComm.Parameters.AddWithValue("@price", price);
            SqlParameter param = new SqlParameter("@imagedata", System.Data.SqlDbType.Image);
            param.Value = image;
            sComm.Parameters.Add(param);

            return ExSqlCommand(sComm);
        }

        public bool DeleteBook(string title, string author)
        {
            string sql = string.Format($"DELETE FROM books WHERE title='{title}' and author = '{author}'");
            return ExSqlCommand(sql);
        }

        public void SelectBook(string title, string author, out int price, out byte[] image)
        {
            string sql = string.Format($"SELECT title, author, price, image FROM books WHERE title='{title}' and author='{author}'");
            SqlCommand sComm = new SqlCommand();
            sComm.Connection = sqlConnection;
            sComm.CommandText = sql;
            SqlDataReader reader = sComm.ExecuteReader();
            if (reader.Read())
            {
                price = int.Parse(reader["price"].ToString());
                image = (byte[])reader["image"];
            }
            else
            {
                price = -1;
                image = null;
            }
            reader.Close();
        }
        //id로 책정보 가져오기
        public void SelectBookId(int id, out string title, out string author, out int price, out byte[] image)
        {
            string sql = string.Format($"SELECT title, author, price, image FROM books WHERE id={id}");
            SqlCommand sComm = new SqlCommand();
            sComm.Connection = sqlConnection;
            sComm.CommandText = sql;
            SqlDataReader reader = sComm.ExecuteReader();
            if (reader.Read())
            {
                title = reader["title"].ToString();
                author = reader["author"].ToString();
                price = int.Parse(reader["price"].ToString());
                image = (byte[])reader["image"];
            }
            else
            {
                title = null;
                author = null;
                price = -1;
                image = null;
            }
            reader.Close();
        }
        // 그냥 DB에 파라미터로 저장(주정)
        public void UpdateBook(string title, string author, int price, byte[] image)
        {
            string sql = string.Format($"UPDATE books SET author='{author}', price={price}, image=@imagedata WHERE title='{title}'");
            SqlCommand sComm = new SqlCommand();
            sComm.Connection = sqlConnection;
            sComm.CommandText = sql;
            SqlParameter param = new SqlParameter("@imagedata", System.Data.SqlDbType.Image);
            param.Value = image;
            sComm.Parameters.Add(param);
            sComm.ExecuteNonQuery();
        }

        public List<string> GetBookList()
        {
            string sql = string.Format($"SELECT title, author FROM books");
            SqlCommand sComm = new SqlCommand();
            sComm.Connection = sqlConnection;
            sComm.CommandText = sql;
            SqlDataReader reader = sComm.ExecuteReader();
            List<string> fuck = new List<string>();
            if (reader.Read())
            {
                Dictionary<string, string> dict = new Dictionary<string, string>();
                do
                {
                    string a = string.Format($"{reader["title"].ToString()}/{reader["author"].ToString()}");
                    fuck.Add( a );
                } while (reader.Read());
                reader.Close();
                return fuck;
            }
            else
            {
                reader.Close();
                return null;
            }
        }

        //public byte[] GetImage(string filename)
        //{
        //    string sql = string.Format($"SELECT imagedata FROM {filename}");
        //    object obj = ExSqlScalar(sql);
        //    if (obj == null)
        //    {
        //        return null;
        //    }
        //    else
        //    {
        //        return (byte[])obj;
        //    }
        //}
        private bool ExSqlCommand(SqlCommand sComm)
        {
            try
            {
                sComm.Connection = sqlConnection;
                if (sComm.ExecuteNonQuery() == 0)
                {
                    return false;
                }
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return false;
            }
        }
        private bool ExSqlCommand(string sql)
        {
            try
            {
                SqlCommand sComm = new SqlCommand();
                sComm.Connection = sqlConnection;
                sComm.CommandText = sql;
                if (sComm.ExecuteNonQuery() == 0)
                {
                    return false;
                }
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return false;
            }
        }

        private object ExSqlScalar(string sql)
        {
            try
            {
                SqlCommand sComm = new SqlCommand();
                sComm.Connection = sqlConnection;
                sComm.CommandText = sql;

                return sComm.ExecuteScalar();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return null;
            }
        }
    }
}
