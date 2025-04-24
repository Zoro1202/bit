using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0424_chat_server_console
{
    class Program
    {
        static void Main(string[] args)
        {
            App app = App.Singleton;
            app.Init();
            Console.WriteLine("아무거나 입력 시 서버 꺼짐 수구");
            Console.ReadLine();
            app.Exit();
        }
    }
}
