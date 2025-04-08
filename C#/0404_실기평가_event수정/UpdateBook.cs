using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0404_실기평가
{
    class UpdateBook
    {
        public static void Invoke()
        {
            Console.WriteLine("\n[도서 수정]\n");
            try
            {
                BookControl bookControl = BookControl.Instance;
                string name = WbLib.InputString("도서명 입력");   // 계좌주 이름
                Book book = bookControl.NameToBook(name);
                int price = WbLib.InputInteger("가격 입력"); // 초기 잔액
                bookControl.Book_Update(book, price);
                Console.WriteLine("도서 수정 성공");
            }
            catch (Exception e)
            {
                Console.WriteLine("도서 수정 실패" + e);
            }
        }
    }
}
