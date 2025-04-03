//계좌관리프로그램
using System;

namespace _0402_계좌관리프로그램
{
    internal class Program
    {
        static void Main(string[] args)
        {
            App app = App.Singleton;
            app.Init();
            app.Run();
            app.Exit();
        }
    }
}
