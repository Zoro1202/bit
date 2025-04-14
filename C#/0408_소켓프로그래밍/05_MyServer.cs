//MyServer1.cs
//다중접속 1대 다 통신(TCP/IP, 가변데이터 처리)
//Read (끊어 읽기)
//Send / Recv : head(고정 크기) + body(가변 크기) 보내기
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

//tcpip
//[socket -> bind -> listen]
//[accept]
//[recv, send]
//[closesocket]

namespace ServerNetWork 
{
    internal delegate void LogMessage(Socket sock, string message);
    internal delegate void PacketMessage(Socket sock, string message);
    class MyServer : IDisposable
    {
        private Socket server = null;
        private Thread acceptThread = null;
        //클라이언트 소켓을 저장하기 위한 리스트
        private List<Socket> clients = new List<Socket>();

        public LogMessage LogCallback { get; set; } = null;
        public PacketMessage PacketCallback { get; set; } = null;

        #region 1. Start 호출 시 acceptThread 스레드 생성
        //서버 소켓을 생성 & 클라이언트의 연결을 대기하는 스레드 생성
        public bool Start(int port, LogMessage log, PacketMessage packet)
        {
            try
            {
                LogCallback = log;
                PacketCallback = packet;
                //socket 생성, 소켓의 주소체계는 IPv4, 소켓의 타입은 TCP, 프로토콜은 TCP
                server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
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
                    LogCallback(client, string.Format("{0}주소, {1}포트 접속", ip.Address, ip.Port));
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
                    LogCallback(null, string.Format("[접속 오류]: " + e.Message));
                    continue;
                }
            }
        }
        #endregion

        #region 2. 소멸자 Dispose, Close 호출 시 소켓, 스레드 종료 (비관리 자원)
        ~MyServer()
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
                    byte[] data = null;
                    RecvData(sock, ref data);
                    //클라이언트에게 문자열 전송
                    string msg = Encoding.Default.GetString(data, 0, data.Length);
                    //SendData(sock, data);
                    SendAllData(sock, msg);
                }
                catch (Exception e)
                {
                    LogCallback(sock, string.Format("[통신 오류]: " + e.Message));
                    break;
                }
            }
            sock.Close();//클라이언트 소켓 닫기
            clients.Remove(sock); //클라이언트 소켓을 리스트에서 제거
        }
        #endregion
        #region 4. 데이터 송수신
        private void RecvData(Socket sock, ref byte[] data)
        {
            try
            {

                // 1. [헤더수신] : 가변 데이터의 크기
                byte[] head = new byte[4];
                //헤더 크기 4바이트
                int recv_data = 0;
                recv_data = sock.Receive(head, 0, head.Length, SocketFlags.None);
                //4바이트(int)로 변환해서 저장
                int size = 0;
                size = 0;       // 받을 크기
                size = BitConverter.ToInt32(head, 0);
                int total = 0;      // 받은 크기
                int left_data = 0;  // 남은 크기 (받을 크기)
                left_data = size;

                // 2. [데이터 수신] : 가변 데이터를 나눠서 수신
                data = new byte[size];

                // 총 받은 데이터 크기가 헤더에서 받은 크기와 같을 때까지 반복
                while (total < size)
                {
                    recv_data = sock.Receive(data, total, left_data, 0); // 소켓에서 데이터 수신
                    if (recv_data == 0) throw new Exception("상대방 소켓 종료"); // 클라이언트가 소켓을 닫음
                    total += recv_data;     // 총 받은 데이터 크기
                    left_data -= recv_data; // 남은 데이터 크기 - 받은 데이터 크기
                    PacketCallback(sock, string.Format($"받은 크기{total}byte / 남은 크기{left_data}byte : (recv {recv_data}byte)"));
                }
            }
            catch (Exception)
            {
                throw;
            }
        }
        public void SendAllData(Socket sock, string msg)
        {
            foreach (Socket client in clients)
            {
                if (client != sock) //자기 자신에게는 전송하지 않음
                {
                    SendData(client, msg);
                }
            }
        }
        private void SendData(Socket sock, string msg)
        {
            byte[] data = Encoding.Default.GetBytes(msg);
            try
            {
                int total = 0;
                int size = data.Length;
                int left_data = size;
                int send_data = 0;

                // 전송할 데이터의 크기 전달
                byte[] head = new byte[4];
                head = BitConverter.GetBytes(size);
                send_data = sock.Send(head);

                // 실제 데이터 전송
                while (total < size)
                {
                    send_data = sock.Send(data, total, left_data, SocketFlags.None);
                    if (send_data == 0) throw new Exception("상대방 소켓 종료");
                    total += send_data;
                    left_data -= send_data;
                    PacketCallback(sock, string.Format($"보낸 크기{total}byte / 남은 크기{left_data}byte : (send {send_data}byte)"));
                }
            }
            catch (Exception)
            {
                throw;
            }
        }

        #endregion
    }
}
