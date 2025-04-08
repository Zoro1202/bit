using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Principal;
using System.Text;
using System.Threading.Tasks;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace _0404_실기평가
{
    internal static class WbFile
    {
        private const string BOOKS_FILENAME = "books.txt";

        public static void Write_Books(ref List<Book> books)
        {
            StreamWriter writer = new StreamWriter(BOOKS_FILENAME);
            writer.WriteLine(books.Count);
            for (int i = 0; i < books.Count; i++)
            {
                Book book = (Book)books[i];
                string temp = string.Empty;
                temp += book.Title + "@";
                temp += book.Price + "@";
                temp += book.Author + "@";
                writer.WriteLine(temp);
            }
            writer.Dispose();
        }
        public static void Read_Books(ref List<Book> books)
        {
            StreamReader reader = new StreamReader(BOOKS_FILENAME);
            int size = int.Parse(reader.ReadLine());
            for (int i = 0; i < size; i++)
            {
                string temp = reader.ReadLine();
                string[] sp = temp.Split('@');
                string title = sp[0];
                int price = int.Parse(sp[1]);
                string author = sp[2];
                books.Add(new Book(title, price, author));
            }
            reader.Dispose();
        }
    }
}
