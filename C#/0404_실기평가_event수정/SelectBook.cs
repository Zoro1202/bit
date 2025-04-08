using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0404_실기평가
{
    class SelectBook
    {
        public static void Invoke()
        {
            Console.WriteLine("\n[도서 검색]\n");
            try
            {
                string name = WbLib.InputString("도서명 입력");   // 계좌주 이름
                BookControl bookControl = BookControl.Instance;
                Book book = bookControl.NameToBook(name);

                Print(book);
            }
            catch (Exception e)
            {
                Console.WriteLine("도서 검색 실패" + e);
            }
        }

        public static void Print(Book book)
        {
            Console.WriteLine($"도서명 : {book.Title}\t가격 : {book.Price}\t저자 : {book.Author}");
        }
    }
}
