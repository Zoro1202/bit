//MyServer.cs
using System;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading;
using System.Collections.Generic;

namespace _0424_chat_server_console.ServerNet
{
    internal delegate void LogMessage(Socket sock, string message);
    internal delegate void PacketMessage(Socket sock, string message);

    internal class MyServer : IDisposable
    {
        private Socket server = null;
        private Thread work_thread = null;

        private List<Socket> clients = new List<Socket>();

        public LogMessage LogCallBack { get; set; } = null;
        public PacketMessage PacketCallBack { get; set; } = null;

        #region 1. Start 호출 시 AcceptThread 동작
        public bool Start(int port, LogMessage log, PacketMessage packet)
        {
            try
            {
                LogCallBack = log;
                PacketCallBack = packet;

                server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                server.Bind(new IPEndPoint(IPAddress.Any, port));
                server.Listen(20);

                work_thread = new Thread(AcceptThread);
                work_thread.IsBackground = true;
                work_thread.Start();

                return true;
            }
            catch (Exception ex)
            {
                LogCallBack(null, string.Format("[Start 오류] " + ex.Message));
                return false;
            }
        }
        private void AcceptThread()
        {
            while (true)
            {
                try
                {
                    Socket socket = server.Accept();

                    //LocalEndPoint , RemoteEndPoint
                    IPEndPoint ip = (IPEndPoint)socket.RemoteEndPoint;
                    LogCallBack(socket, string.Format("[클라이언트 접속] {0}:{1}", ip.Address, ip.Port));
                    clients.Add(socket);

                    Thread tr = new Thread(WorkThead);
                    tr.IsBackground = true;
                    tr.Start(socket);
                }
                catch (Exception ex)
                {
                    LogCallBack(null, string.Format("[접속 오류] " + ex.Message));
                }
            }
        }
        #endregion

        #region 2. Dispose 나 Close 호출 시 소켓 및 스레드 종료
        ~MyServer()
        {
            Dispose();
        }
        public void Dispose()
        {
            Close();
            GC.SuppressFinalize(this);
        }

        public void Close()
        {
            work_thread.Abort();
            server.Close();
            LogCallBack(server, string.Format("[서버 종료] "));
        }
        #endregion

        #region 3. 클라이언트 접속 시 통신 스레드
        private void WorkThead(object obj)
        {
            Socket sock = (Socket)obj;

            while (true)
            {
                try
                {
                    //1. 수신
                    byte[] data = null;
                    RecvData(sock, ref data);

                    //2. 데이터 출력
                    string msg = Encoding.Default.GetString(data, 0, data.Length);
                    PacketCallBack(sock, msg);
                }
                catch (Exception e)
                {
                    LogCallBack(sock, string.Format($"[수신오류] {e.Message}"));
                    break;
                }
            }

            IPEndPoint ip = (IPEndPoint)sock.RemoteEndPoint;
            Console.WriteLine("[클라이언트 종료] {0}:{1}", ip.Address, ip.Port);

            sock.Close();           //****
            clients.Remove(sock);   //****
        }
        #endregion

        #region 4. 데이터 송 수신 
        private void RecvData(Socket socket, ref byte[] data)
        {
            try
            {
                //1. [헤더 수신] 가변 데이터 크기
                byte[] head = new byte[4];
                int recv_data = socket.Receive(head, 0, head.Length, SocketFlags.None);
                int size = BitConverter.ToInt32(head, 0);   //받을 크기                 

                //2. [데이터 수신] 가변 데이터를 size의 크기만큼 수신
                int total = 0;        //받은 크기
                int left_data = size;     //남은 크기
                data = new byte[size];
                while (total < size)
                {
                    recv_data = socket.Receive(data, total, left_data, 0);
                    if (recv_data == 0) throw new Exception("상대방 소켓 종료");
                    total += recv_data;
                    left_data -= recv_data;
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        public void SendData(Socket socket, string msg)
        {
            byte[] data = Encoding.Default.GetBytes(msg);
            SendData(socket, data);
        }
        public void SendAllData(Socket sock, string msg)
        {
            byte[] data = Encoding.Default.GetBytes(msg);
            foreach (Socket s in clients)
            {
                if (s != sock)         //본인에게 전달하지 않을 때 사용
                    SendData(s, data);
            }
        }
        public void SendAllData_me(Socket sock, string msg)
        {
            byte[] data = Encoding.Default.GetBytes(msg);
            foreach (Socket s in clients)
            {
                //if (s != sock)         //본인에게 전달하지 않을 때 사용
                    SendData(s, data);
            }
        }
        private void SendData(Socket sock, byte[] data)
        {
            try
            {
                //1. [헤더 수신] 가변 데이터 크기
                byte[] head = new byte[4];
                int size = data.Length;
                head = BitConverter.GetBytes(size);
                int send_data = sock.Send(head);

                //2. [데이터 송신] 가변 데이터를 size의 크기만큼 송신
                int total = 0;
                int left_data = size;
                while (total < size)
                {
                    send_data = sock.Send(data, total, left_data, SocketFlags.None);
                    total += send_data;
                    left_data -= send_data;
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        #endregion 
    }
}