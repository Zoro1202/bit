//App.cs
using _0407_계좌관리프로그램;
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
                PrintAllAccount.Invoke();
                switch (WbLib.MenuPrint())
                {
                    case ConsoleKey.Escape: return; 
                    case ConsoleKey.F1: InsertAccount.Invoke();    break;
                    case ConsoleKey.F2: SelectAccount.Invoke();     break;
                    case ConsoleKey.F3: SelectNameAll.Invoke();    break;
                    case ConsoleKey.F4: InputAccount.Invoke();     break;
                    case ConsoleKey.F5: OutputAccount.Invoke();    break;
                    case ConsoleKey.F6: DeleteAccount.Invoke();    break;
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
