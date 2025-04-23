using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Drawing;


namespace _0423_키보드로움직이는타원
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
        public bool Insert_Shape(Point pt, Color color, int idx, int size)
        {
            string sql = string.Format($"INSERT INTO Shape VALUES({pt.X}, {pt.Y}, '{color.Name}', {idx}, {size})");
            return ExSqlCommand(sql);
        }

        //5. 점수 검색 기능
        public int Select_Shape(int idx)
        {
            string sql = string.Format($"select jumsu_num from Jumsu where stu_id = {idx};");
            object obj = ExSqlScalarCommand(sql);
            if (obj == null)
                throw new Exception("오류 발생");
            return (int)obj;
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
        public List<Shape> SelectAllShapes(int list_idx)
        {
            string sql = string.Format($"select * from Shape, Shape_List l where l.shapelist_idx = {list_idx}");
            List<Shape> list = new List<Shape>();
            using (SqlCommand cmd = new SqlCommand(sql, scon))
            {
                SqlDataReader r = cmd.ExecuteReader();
                while(r.Read())
                {
                    int shape_id = int.Parse(r["shape_id"].ToString());
                    int point_x = int.Parse(r["point_x"].ToString());
                    int point_y = int.Parse(r["point_y"].ToString());
                    string colortext = r["color_text"].ToString();
                    int color_index = int.Parse(r["solor_idx"].ToString());
                    int size = int.Parse(r["size"].ToString());
                    list.Add(new Shape(new Point(point_x, point_y), Color.FromName(colortext), color_index, size));
                }
                r.Close();
            }
            return list;
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

