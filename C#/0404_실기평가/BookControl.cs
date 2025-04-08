using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Principal;
using System.Text;
using System.Threading.Tasks;

namespace _0404_실기평가
{
    class BookControl
    {
        List<Book> books;
        public BookControl()
        {
            books = new List<Book>();
        }
        public void Init()
        {
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
            WbFile.Write_Books(ref books);
            WbLib.Pause();
        }
        public void Book_Insert()
        {
            try
            {
                Console.WriteLine("\n[계좌 저장]\n");

                string name = WbLib.InputString("도서명 입력");   // 계좌주 이름
                int price = WbLib.InputInteger("가격 입력"); // 초기 잔액
                string author = WbLib.InputString("저자 입력"); // 계좌번호
                Book book;
                book = new Book(name, price, author);

                books.Add(book);
                //거래 내역 저장
                Console.WriteLine("도서 저장 성공");
            }
            catch (Exception e)
            {
                Console.WriteLine("도서 저장 실패");
            }
        }
        public void Book_Select()
        {
            Console.WriteLine("\n[도서 검색]\n");
            string name = WbLib.InputString("도서명 입력");   // 계좌주 이름
            foreach(var book in books)
            {
                if (book.Title == name)
                {
                    Console.WriteLine($"도서명: {book.Title}, 가격: {book.Price}, 저자: {book.Author}");
                    return;
                }
            }
            Console.WriteLine("도서 검색 실패");
        }
        public void Book_Update()
        {
            Console.WriteLine("\n[도서 수정]\n");
            string name = WbLib.InputString("도서명 입력");   // 계좌주 이름
            foreach (var book in books)
            {
                if (book.Title == name)
                {
                    try
                    {
                        int price = WbLib.InputInteger("가격 입력"); // 초기 잔액
                        book.UpdatePrice(price);
                        Console.WriteLine("도서 수정 성공");
                        return;
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine("도서 수정 실패");
                        return;
                    }
                }
            }
            Console.WriteLine("도서 수정 실패");
        }
        public void Book_Delete()
        {
            Console.WriteLine("\n[도서 삭제]\n");
            string name = WbLib.InputString("도서명 입력");   // 계좌주 이름
            foreach (var book in books)
            {
                if (book.Title == name)
                {
                    books.Remove(book);
                    Console.WriteLine("도서 삭제 성공");
                    return;
                }
            }
            Console.WriteLine("도서 삭제 실패");
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
        }
    }
}
