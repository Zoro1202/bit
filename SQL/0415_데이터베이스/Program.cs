using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace _0415_데이터베이스
{
    internal class Program
    {
        static void Main(string[] args)
        {
            myDataAdapter();
        }

        private static void myDataAdapter()
        {
            myDB2 db = new myDB2();
            List<string> list = db.SelectAllCustom();
            foreach (string s in list)
            {
                Console.WriteLine(s);
            }
            //db.InsertCustom("제갈공명","010-1234-1234","중국");
            db.UpdateCustom(6, "080-335-0020", "보니하니");
            db.DeleteCustom(5);
        }

        private static void MyMemoryDBTest()
        {
            MyMemoryDB myDB = new MyMemoryDB();
            //myDB.CreateAccoutTable();
            myDB.Account_ReadXML();
            //myDB.PrintTableSchema(myDB.AccountTable);
            //myDB.Account_Insert("홍길동");
            //myDB.Account_Insert("남궁길동", 20000);
            //myDB.Account_Insert("제갈길동", 30000, DateTime.Now);
            myDB.PrintTableSchema(myDB.AccountTable);
            List<Account> accs = myDB.SelectAllAccount();
            foreach (Account acc in accs)
            {
                Console.WriteLine(acc);
            }
            Console.WriteLine("선택 : 1000");
            Account acc1 = myDB.SelectAccount(1000);
            if (acc1 != null)
                Console.WriteLine(acc1);
            else
                Console.WriteLine("없는 id");
            //myDB.DeleteAccount(1010);
            myDB.UpdateAccount_Input(1000, 1000);
            List<Account> accs1 = myDB.SelectAllAccount();
            foreach (Account acc in accs1)
            {
                Console.WriteLine(acc);
            }
            myDB.Account_WriteXML();
        }

        private static void SQLDBProcedure()
        {
            MyDB1 myDB = new MyDB1();
            if (myDB.Connect() == false)
                return;
            Console.WriteLine("DB연결");

            //myDB.AddProduct("C# Network", 20000, "C# Network 설명...");
            myDB.FindCIDByName("홍길동");
            if (myDB.Close() == true)
                Console.WriteLine("DB연결종료");
        }

        private static void NewMethod()
        {
            MyDB myDB = new MyDB();
            if (myDB.Connect() == false)
                return;
            Console.WriteLine("DB연결");

            //myDB.Insert_Book("C언어", 15000, "C언어의 설명문.....");
            //myDB.Update_Book1(1000, 30000);
            //myDB.update_Book2("C언어", 18000);
            //myDB.Delete_Book1(1000);
            //myDB.Delete_Book2("C언어");
            int total = myDB.Get_TotalPrice();
            int max = myDB.Get_MaxPrice();
            Console.WriteLine(total + ", " + max);


            if (myDB.Close() == true)
                Console.WriteLine("DB연결종료");
        }
    }
}
