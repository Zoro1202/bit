using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace _0408_소켓프로그래밍
{
    class MyClient1 : IDisposable
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
            byte[] buffer = new byte[1024];
            while (true)
            {
                try
                {
                    int ret = RecvData(buffer);
                    if (ret == 0)
                    {
                        throw new Exception("상대방이 소켓 닫음");
                    }
                    string msg = Encoding.Default.GetString(buffer, 0, ret);
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
        ~MyClient1()
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
            byte[] buffer = Encoding.Default.GetBytes(msg);
            int ret = socket.Send(buffer, buffer.Length, SocketFlags.None);
            Console.WriteLine("전송 바이트 수: " + ret);
        }
        private int RecvData(byte[] buffer)
        {
            //buffer = new byte[1024];
            int ret = socket.Receive(buffer);
            if (ret == 0)
            {
                return ret;
            }
            return ret;
        }
        #endregion
    }
}
