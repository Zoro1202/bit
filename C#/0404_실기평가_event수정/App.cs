using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0404_실기평가
{
    class App
    {
        public static App Instance { get; } = null;
        private BookControl book = BookControl.Instance;
        static App()
        {
            Instance = new App();
        }
        public App()
        {
        }
        public void Init()
        {
            book.Init();
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
                    case ConsoleKey.F1: InsertBook.Invoke(); break;
                    case ConsoleKey.F2: SelectBook.Invoke(); break;
                    case ConsoleKey.F3: UpdateBook.Invoke(); break;
                    case ConsoleKey.F4: DeleteBook.Invoke(); break;
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
