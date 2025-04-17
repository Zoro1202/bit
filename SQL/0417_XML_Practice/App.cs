using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0417_XML_Practice
{
    class App
    {
        private AccountControl acc_control = AccountControl.Singleton;

        #region 0. 싱글톤 패턴
        public static App Singleton { get; } = null;
        static App() { Singleton = new App(); }
        private App() { }
        #endregion

        public void Init()
        {
            acc_control.Init();
            WbLib.Logo();
        }

        public void Run()
        {
            while (true)
            {
                Console.Clear();
                Console.WriteLine("------------------------------------------------");
                switch (WbLib.MenuPrint())
                {
                    case ConsoleKey.Escape: return;
                    case ConsoleKey.F1: acc_control.InsertFiveAccounts(); break;
                    case ConsoleKey.F2: acc_control.AccountPrintAll(); break;
                    case ConsoleKey.F3: acc_control.XMLWriter(); break;
                    case ConsoleKey.F4: acc_control.XMLReadToConsole(); break;
                    default: Console.WriteLine("잘못 입력하셨습니다."); break;
                }
                WbLib.Pause();
            }
        }

        public void Exit()
        {
            acc_control.Exit();
            WbLib.Ending();
        }
    }
}
