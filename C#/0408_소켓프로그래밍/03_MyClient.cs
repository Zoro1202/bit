using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace _0408_소켓프로그래밍2
{
    class MyClient2 : IDisposable
    {
        private Socket socket = null;
        private Thread workThread = null;
        #region 1. Start 호출 시 소켓 생성 & 서버 연결 요청
        public bool Start(string ip, int port)
        {
            try
            {
                //소켓 생성
                socket = new Socket(AddressFamily.InterNetwork,
                                     SocketType.Stream, ProtocolType.Tcp);
                //서버에 연결
                socket.Connect(new IPEndPoint(IPAddress.Parse(ip), port));

                Thread tr = new Thread(WorkThread);
                tr.IsBackground = true; //스레드를 백그라운드 스레드로 설정
                tr.Start();

                return true;

            }
            catch (Exception e)
            {
                Console.WriteLine("[소켓 생성 오류]: " + e.Message);
                return false;
            }
        }
        //recv 전용 스레드
        private void WorkThread()
        {
            byte[] buffer = null;
            while (true)
            {
                try
                {
                    RecvData(ref buffer);
                    string msg = Encoding.Default.GetString(buffer, 0, buffer.Length);
                    Console.WriteLine($"[수신]: {msg}");
                }
                catch (Exception e)
                {
                    Console.WriteLine("[통신 오류]: " + e.Message);
                    break;
                }
            }
        }

        #endregion

        #region 2. 소멸자
        ~MyClient2()
        {
            Dispose();
        }
        public void Close()
        {
            socket.Close();
        }

        public void Dispose()
        {
            Close();
            GC.SuppressFinalize(this);
        }
        #endregion

        #region 3. 데이터 송수신
        public void SendData(string msg)
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
                send_data = socket.Send(head);

                // 실제 데이터 전송
                while (total < size)
                {
                    send_data = socket.Send(data, total, left_data, SocketFlags.None);
                    if (send_data == 0) throw new Exception("상대방 소켓 종료");
                    total += send_data;
                    left_data -= send_data;
                }
                Console.WriteLine("전송 바이트 수: " + total);
            }
            catch (Exception)
            {
                throw;
            }
        }
        private void RecvData(ref byte[] data)
        {
            try
            {
                // 1. [헤더수신] : 가변 데이터의 크기
                byte[] head = new byte[4];
                //헤더 크기 4바이트
                int recv_data = 0;
                recv_data = socket.Receive(head, 0, head.Length, SocketFlags.None);
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
                    recv_data = socket.Receive(data, total, left_data, 0); // 소켓에서 데이터 수신
                    if (recv_data == 0) throw new Exception("상대방 소켓 종료"); // 클라이언트가 소켓을 닫음
                    total += recv_data;     // 총 받은 데이터 크기
                    left_data -= recv_data; // 남은 데이터 크기 - 받은 데이터 크기
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
