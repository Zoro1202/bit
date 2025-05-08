using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace _0507_도서관리_WCFService
{
    class BookWCFService : IBook
    {
        public void AddBook(string title, string author, int price, byte[] image)
        {
            MyDB db = new MyDB();
            //db에 경로 올리기
            if (db.connect())
            {
                db.InsertBook(title, author, price, image);
                db.Close();
            }
        }

        public bool DeleteBook(string title, string author)
        {
            MyDB db = new MyDB();
            if (db.connect())
            {
                if(db.DeleteBook(title, author))
                {
                    string filepath = @"C:\aaa\" + title + author;
                    if (File.Exists(filepath))
                    {
                        File.Delete(filepath);
                    }
                    return true;
                } 
                else
                {
                    //Console.WriteLine("삭제 실패");
                }
                db.Close();
            }
            return false;
        }

        public void GetBook1(string title, string author, ref int price, ref byte[] image)
        {
            MyDB db = new MyDB();
            if (db.connect())
            {
                db.SelectBook(title,author, out price, out image);
                db.Close();
            }
            else
            {
                price = 0;
                image = null;
            }
        }

        public string[] GetBookList()
        {
            MyDB db = new MyDB();
            if (db.connect())
            {
                string[] arr = db.GetBookList().ToArray();
                if (arr == null)
                    return null;
                db.Close();
                return arr;
            }
            else
            {
                 return null;
            }
        }

        public void UpdateBook(string title, string author, int price, byte[] image)
        {
            MyDB db = new MyDB();
            if(db.connect())
            {
                db.UpdateBook(title, author, price, image);
                string filepath = @"C:\aaa\" + title + author;
                if (File.Exists(filepath))
                {
                    File.Delete(filepath);
                }
                FileStream writeFileStream = new FileStream(filepath, FileMode.Create, FileAccess.Write);
                BinaryWriter picWriter = new BinaryWriter(writeFileStream);
                picWriter.Write(image);
                writeFileStream.Close();
                db.Close();
            }
        }
    }
}
