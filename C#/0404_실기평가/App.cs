using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0404_실기평가
{
    class App
    {
        public App()
        {
            book.Init();
            Run();
            Exit();
        }
        BookControl book = new BookControl();
        public void Init()
        {
            WbLib.Logo();
        }

        public void Run()
        {
            while (true)
            {
                Console.Clear();
                book.PrintAllBooks();
                switch (WbLib.MenuPrint())
                {
                    case ConsoleKey.Escape: return;
                    case ConsoleKey.F1: book.Book_Insert(); break;
                    case ConsoleKey.F2: book.Book_Select(); break;
                    case ConsoleKey.F3: book.Book_Update(); break;
                    case ConsoleKey.F4: book.Book_Delete(); break;
                    case ConsoleKey.F5: book.SortByPrice(); break;
                    default: Console.WriteLine("잘못 입력하셨습니다."); break;
                }
                WbLib.Pause();
            }
        }

        public void Exit()
        {
            book.Exit();
            WbLib.Ending();
        }
    }
}
