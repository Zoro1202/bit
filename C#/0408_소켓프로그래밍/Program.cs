
using System.Net.Sockets;

namespace _0408_소켓프로그래밍
{
    internal class Program
    {
        private const string SERVER_IP = "220.90.180.111"; // 127.0.0.1 루프백 IP : 내 컴퓨터
        private const int SERVER_PORT = 7000;

        public static void LogMessage(Socket sock, string msg)
        {
            Console.WriteLine("[LOG]: " + msg);
        }
        public static void PacketMessage(Socket sock, string msg)
        {
            Console.WriteLine("[PACKET]: " + msg);
        }
        static void ServerTest2()
        {
            _0408_소켓프로그래밍3.MyServer3 server = new _0408_소켓프로그래밍3.MyServer3();
            if (server.Start(SERVER_PORT, LogMessage, PacketMessage) == false)
            {
                Console.WriteLine("서버 시작 실패");
                return;
            }
            Console.WriteLine("서버 시작...");

            Console.ReadLine(); // 서버가 종료될 때까지 대기

            server.Close();
            Console.WriteLine("서버 종료...");
        }

        //1v1 통신
        static void ServerTest()
        {
            MyServer1 server = new MyServer1();
            if (server.Start(SERVER_PORT) == false)
            {
                Console.WriteLine("서버 시작 실패");
                return;
            }
            Console.WriteLine("서버 시작...");

            Console.ReadLine(); // 서버가 종료될 때까지 대기

            server.Close();
            Console.WriteLine("서버 종료...");
        }
        //1v 다 통신
        static void ServerTest1()
        {
            _0408_소켓프로그래밍1.MyServer2 server = new _0408_소켓프로그래밍1.MyServer2();
            if (server.Start(SERVER_PORT) == false)
            {
                Console.WriteLine("서버 시작 실패");
                return;
            }
            Console.WriteLine("서버 시작...");

            Console.ReadLine(); // 서버가 종료될 때까지 대기

            server.Close();
            Console.WriteLine("서버 종료...");
        }
        static void ClientTest1()
        {
            MyClient1 client = new MyClient1();
            if (client.Start(SERVER_IP, SERVER_PORT) == false)
            {
                Console.WriteLine("서버 연결 실패");
                return;
            }
            Console.WriteLine("서버 연결 성공...");

            //전송 test
            while (true)
            {
                Console.Write(">> ");
                string msg = Console.ReadLine();
                if (msg == string.Empty)
                {
                    break;
                }
                client.SendData(msg);
            }

            client.Close();
            Console.WriteLine("클라이언트 종료...");
        }
        static void ClientTest()
        {
            MYClient.MyClient2 client = new MYClient.MyClient2();
            if (client.Start(SERVER_IP, SERVER_PORT, LogMessage, PacketMessage) == false)
            {
                Console.WriteLine("서버 연결 실패");
                return;
            }
            Console.WriteLine("서버 연결 성공...");

            //전송 test
            while (true)
            {
                Console.Write(">> ");
                string msg = Console.ReadLine();
                if (msg == string.Empty)
                {
                    break;
                }
                client.SendData(msg);
            }

            client.Close();
            Console.WriteLine("클라이언트 종료...");
        }
        static void Main(string[] args)
        {
            //ServerTest();
            ClientTest();
        }
    }
}
