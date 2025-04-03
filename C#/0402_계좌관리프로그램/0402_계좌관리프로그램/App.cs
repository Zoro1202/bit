//App.cs
using System;
using WoosongBit41.Data;
using WoosongBit41.Lib;

namespace _0402_계좌관리프로그램
{
    internal class App
    {
        private AccountControl acc_control = AccountControl.Singleton;

        #region 0. 싱글톤 패턴
        public static App Singleton { get; } = null;
        static App() { Singleton = new App(); }
        private App() {}
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
                acc_control.AccountPrintAll();
                acc_control.AccountIOPrintAll();
                switch (WbLib.MenuPrint())
                {
                    case ConsoleKey.Escape: return; 
                    case ConsoleKey.F1: acc_control.AccountInsert();    break;
                    case ConsoleKey.F2: acc_control.SelectNumber();     break;
                    case ConsoleKey.F3: acc_control.SelectNameAll();    break;
                    case ConsoleKey.F4: acc_control.AccountInput();     break;
                    case ConsoleKey.F5: acc_control.AccountOutput();    break;
                    case ConsoleKey.F6: acc_control.AccountDelete();    break;
                    case ConsoleKey.F7: acc_control.AccountSort(2);    break;
                    case ConsoleKey.F8: acc_control.AccountSort(1);    break;
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
