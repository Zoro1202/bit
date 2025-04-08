using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Reflection.Metadata.BlobBuilder;

namespace _0404_실기평가
{
    class DeleteBook
    {
        public static void Invoke()
        {
            Console.WriteLine("\n[도서 삭제]\n");
            try
            {
                string name = WbLib.InputString("도서명 입력");   // 계좌주 이름
                BookControl bookControl = BookControl.Instance;
                Book book = bookControl.NameToBook(name);
                bookControl.Book_Delete(book);
                Console.WriteLine("도서 삭제 성공");
            }
            catch (Exception e)
            {
                Console.WriteLine("도서 삭제 실패" + e);
            }
        }
    }
}
