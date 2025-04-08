using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.InteropServices;
using System.Security.Principal;
using System.Text;
using System.Threading.Tasks;

namespace _0404_실기평가
{
    class BookControl
    {
        private List<Book> books;
        //public Book Books { get; private set; }
        public static BookControl Instance { get; } = null;
        static BookControl()
        {
            Instance = new BookControl();
        }
        private BookControl()
        {
            books = new List<Book>();
        }
        public event LogDele LogEvent = null;
        public LogManager logManager = null;
        public void Init()
        {
            logManager = new LogManager();
            try
            {
                WbFile.Read_Books(ref books);
                Console.WriteLine("파일 읽기 성공");
            }
            catch (Exception e)
            {
                Console.WriteLine("파일 읽기 실패");
            }
            WbLib.Pause();
        }
        public void Exit()
        {
            logManager.Dispose();
            WbFile.Write_Books(ref books);
            WbLib.Pause();
        }
        public void Book_Insert(Book book)
        {
            try
            {
                books.Add(book);
            }
            catch (Exception)
            {
                throw;
            }
            LogEvent(this, new LogArgs(ELOGTYPE.INPUT, "도서 입력"));
        }
        public Book Book_Select()
        {
            Console.WriteLine("\n[도서 검색]\n");
            string name = WbLib.InputString("도서명 입력");   // 계좌주 이름
            try
            {
                Book book = NameToBook(name);
                LogEvent(this, new LogArgs(ELOGTYPE.SELECT, "도서 검색"));
                return book;
            }
            catch(Exception)
            {
                throw;
            }
        }
        public Book NameToBook(string name)
        {
            foreach(var book in books)
            {
                if(book.Title == name)
                {
                    return book;
                }
            }
            throw new ArgumentException("도서 검색 실패");
        }
        public void Book_Update(Book book, int price)
        {
            try
            {
                book.UpdatePrice(price);
                Console.WriteLine("도서 수정 성공");
            } 
            catch(Exception)
            {
                throw;
            }
            LogEvent(this, new LogArgs(ELOGTYPE.UPDATE, "도서 수정"));
        }
        public void Book_Delete(Book book)
        {
            try
            {
                books.Remove(book);
            }
            catch(Exception)
            {
                throw;
            }
            LogEvent(this, new LogArgs(ELOGTYPE.DELETE, "도서 삭제"));
        }
        public void PrintAllBooks()
        {
            Console.WriteLine("\n[모든 도서 출력]\n");
            foreach (var book in books)
            {
                Console.WriteLine($"도서명: {book.Title}, 가격: {book.Price}, 저자: {book.Author}");
            }
        }
        public void SortByPrice()
        {
            books.Sort();
            Console.WriteLine("도서 가격으로 정렬 완료");
            LogEvent(this, new LogArgs(ELOGTYPE.SORT, "도서 정렬"));
        }
    }
}
