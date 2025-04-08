//MyServer1.cs
//다중접속 1대 다 통신(TCP/IP)
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

//tcpip
//[socket -> bind -> listen]
//[accept]
//[recv, send]
//[closesocket]

namespace _0408_소켓프로그래밍1
{
    class MyServer2 : IDisposable
    {
        private Socket server = null;
        private Thread acceptThread = null;
        //클라이언트 소켓을 저장하기 위한 리스트
        private List<Socket> clients = new List<Socket>();

        #region 1. Start 호출 시 acceptThread 스레드 생성
        //서버 소켓을 생성 & 클라이언트의 연결을 대기하는 스레드 생성
        public bool Start(int port)
        {
            try
            {
                //socket 생성, 소켓의 주소체계는 IPv4, 소켓의 타입은 TCP, 프로토콜은 TCP
                server = new Socket(AddressFamily.InterNetwork,
                                                      SocketType.Stream, ProtocolType.Tcp);
                //서버 소켓에 ip주소와 포트번호를 바인딩하기 위한 IPEndPoint 객체 생성
                IPEndPoint ipep = new IPEndPoint(IPAddress.Any, port);
                //서버 소켓에 ip주소와 포트번호를 바인딩
                server.Bind(ipep);
                //서버 소켓을 리스닝 상태로 전환, 20개의 클라이언트 연결을 대기
                server.Listen(20);

                //서버 소켓을 통해 클라이언트의 연결을 대기하는 스레드 생성
                acceptThread = new Thread(AcceptThread);
                //스레드를 시작
                acceptThread.Start();
                //스레드가 시작되면 acceptThread 메서드가 실행됨
                //acceptThread 메서드는 클라이언트의 연결을 대기하고, 연결이 되면 클라이언트와 연결된 소켓을 통해 클라이언트에게 문자열을 전송함
                //acceptThread 메서드는 무한루프를 돌면서 클라이언트의 연결을 대기함
                //acceptThread 메서드는 클라이언트의 연결이 되면 클라이언트와 연결된 소켓을 통해 클라이언트에게 문자열을 전송함
                //acceptThread.Join();
                return true;
            }
            catch (Exception e)
            {
                //기타 예외 발생시 예외 메시지 출력
                Console.WriteLine("[소켓 생성 오류]: " + e.Message);
                return false;
            }
        }
        //클라이언트 연결을 위한 스레드 메서드
        private void AcceptThread()
        {
            while (true)
            {
                try
                {
                    //client 소켓을 생성, accept 메서드를 통해 클라이언트의 연결을 대기
                    Socket client = server.Accept();
                    //클라이언트와 연결된 소켓을 통해 클라이언트의 ip주소와 포트번호를 가져옴
                    IPEndPoint ip = (IPEndPoint)client.RemoteEndPoint;
                    Console.WriteLine("{0}주소, {1}포트 접속", ip.Address, ip.Port);

                    //클라이언트 소켓을 리스트에 추가
                    clients.Add(client);

                    //클라이언트와 연결된 소켓을 통해 클라이언트에게 문자열 전송
                    Thread tr = new Thread(new ParameterizedThreadStart(WorkThread));
                    tr.IsBackground = true; //스레드를 백그라운드 스레드로 설정
                    tr.Start(client); //스레드 시작
                }
                catch (Exception e)
                {
                    //기타 예외 발생시 예외 메시지 출력
                    Console.WriteLine("[접속 오류]: " + e.Message);
                    continue;
                }
            }
        }
        #endregion

        #region 2. 소멸자 Dispose, Close 호출 시 소켓, 스레드 종료 (비관리 자원)
        ~MyServer2()
        {
            Dispose(); //서버 소켓 닫기
        }
        public void Dispose()
        {
            Close(); //서버 소켓 닫기
            GC.SuppressFinalize(this); //소멸자 호출 방지
        }

        public void Close()
        {
            acceptThread.Abort(); //acceptThread 스레드 종료
            server.Close(); //서버 소켓 닫기
        }
        #endregion

        #region 3. 소켓 통신
        private void WorkThread(object obj)
        {
            Socket sock = (Socket)obj;
            while (true)
            {
                try
                {
                    byte[] buffer = new byte[1024];
                    int ret = RecvData(sock, buffer);
                    if (ret == 0)
                    {
                        throw new Exception("클라이언트가 소켓 닫음");
                    }
                    //클라이언트에게 문자열 전송
                    //SendData(sock, buffer, ret);
                    SendAllData(sock, buffer, ret);
                }
                catch (Exception e)
                {
                    Console.WriteLine("[통신 오류]: " + e.Message);
                    break;
                }
            }
            sock.Close();//클라이언트 소켓 닫기
            clients.Remove(sock); //클라이언트 소켓을 리스트에서 제거
        }
        #endregion
        #region 4. 데이터 송수신
        private int RecvData(Socket sock, byte[] buffer)
        {
            //buffer = new byte[1024];
            int ret = sock.Receive(buffer);
            if (ret == 0)
            {
                return ret;
            }
            string msg = Encoding.Default.GetString(buffer, 0, ret);
            Console.WriteLine($"[수신]: {msg}");

            return ret;
        }
        public void SendData(Socket sock, byte[] buffer, int size)
        {
            int ret = sock.Send(buffer, size, SocketFlags.None);
            if (ret == 0)
            {
                throw new Exception("클라이언트가 소켓 닫음");
            }
            Console.WriteLine("전송 바이트 수: " + ret);
        }
        public void SendAllData(Socket sock, byte[] buffer, int size)
        {
            foreach (Socket client in clients)
            {
                if (client != sock) //자기 자신에게는 전송하지 않음
                {
                    SendData(client, buffer, size);
                }
            }
        }
        #endregion
    }
}
