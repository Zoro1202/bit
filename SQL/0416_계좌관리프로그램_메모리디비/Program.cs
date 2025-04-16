using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0416_계좌관리프로그램_메모리디비
{
    class Program
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
