using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Drawing;


namespace _0424_chat_server_console
{
    internal class MyDB
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

        #region 도형 저장
        public bool Register_Member(string id, string pw, string name, Color color, DateTime date)
        {
            string sql = string.Format($"INSERT INTO Member VALUES('{id}', '{pw}','{name}', '{color.Name}', '{date.ToString()}', 0)");
            return ExSqlCommand(sql);
        }

        //로그인 검사 기능 -> string[2] id, name 반환
        public string[] Login_Member(string id, string pw)
        {
            string sql = string.Format($"select memberid, membername from Member where memberid = '{id}' and memberpw = '{pw}';");
            using (SqlCommand cmd = new SqlCommand(sql, scon))
            {
                SqlDataReader r = cmd.ExecuteReader();
                string[] res;
                if (r.Read())
                    res = new string[2] { r["memberid"].ToString(), r["membername"].ToString() };
                else 
                    res = null;
                r.Close();
                return res;
            }
        }
        public bool Login_Member_UPDATE(int islog, string id)
        {
            string sql = string.Format($"UPDATE Member SET Member.islog = {islog} WHERE memberid = '{id}'");
            return ExSqlCommand(sql);
        }
        // 6 점수 수정 기능
        public bool Update_Jumsu(int stuid, int subid, int jumsuNum)
        {
            string sql = string.Format($"update Jumsu set jumsu_num = {jumsuNum} where stu_id = {stuid} and sub_id = {subid};");
            return ExSqlCommand(sql);
        }
        // 7. 점수 삭제 기능
        public bool Delete_Jumsu(int stuid, int subid)
        {
            string sql = string.Format($"delete from Jumsu where stu_id = {stuid} and sub_id = {subid};");
            return ExSqlCommand(sql);
        }
        //combobox에 넣을 item (list_id) 가져오기 = list<int>
        public List<int> SelectAllShapesStr()
        {
            string sql = string.Format($"select shapelist_idx from Shape_List");
            List<int> list = new List<int>();
            using (SqlCommand cmd = new SqlCommand(sql, scon))
            {
                SqlDataReader r = cmd.ExecuteReader();
                while (r.Read())
                {
                    int shape_id = int.Parse(r["shapelist_idx"].ToString());
                    list.Add(shape_id);
                }
                r.Close();
            }
            return list;
        }
        //list의 idx에 맞는 전체 도형의 list 가져오기
        //public List<Shape> SelectAllShapes(int list_idx)
        //{
        //    string sql = string.Format($"select * from Shape, Shape_List l where l.shapelist_idx = {list_idx}");
        //    List<Shape> list = new List<Shape>();
        //    using (SqlCommand cmd = new SqlCommand(sql, scon))
        //    {
        //        SqlDataReader r = cmd.ExecuteReader();
        //        while(r.Read())
        //        {
        //            int shape_id = int.Parse(r["shape_id"].ToString());
        //            int point_x = int.Parse(r["point_x"].ToString());
        //            int point_y = int.Parse(r["point_y"].ToString());
        //            string colortext = r["color_text"].ToString();
        //            int color_index = int.Parse(r["solor_idx"].ToString());
        //            int size = int.Parse(r["size"].ToString());
        //            list.Add(new Shape(new Point(point_x, point_y), Color.FromName(colortext), color_index, size));
        //        }
        //        r.Close();
        //    }
        //    return list;
        //}
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

