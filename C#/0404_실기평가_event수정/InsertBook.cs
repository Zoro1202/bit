using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Reflection.Metadata.BlobBuilder;

namespace _0404_실기평가
{
    class InsertBook
    {
        public static void Invoke()
        {
            Console.WriteLine("\n[계좌 저장]\n");
            try
            {
                string name = WbLib.InputString("도서명 입력");   // 계좌주 이름
                int price = WbLib.InputInteger("가격 입력"); // 초기 잔액
                string author = WbLib.InputString("저자 입력"); // 계좌번호
                Book book = new Book(name, price, author);
                BookControl bookcontrol = BookControl.Instance;
                bookcontrol.Book_Insert(book);
                //거래 내역 저장
                Console.WriteLine("도서 저장 성공");
            }
            catch (Exception e)
            {
                Console.WriteLine("도서 저장 실패" + e);
            }
        }
    }
}
