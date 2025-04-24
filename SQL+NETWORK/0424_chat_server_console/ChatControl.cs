using _0424_chat_server_console.NetWorkServer;
using _0424_chat_server_console.ServerNet;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace _0424_chat_server_console
{
    class ChatControl
    {
        private const int SERVER_PORT = 8000; //서버 포트번호

        public static MyServer myServer = new MyServer(); //소켓 통신을 위한 객체
        public MyServer MyServer { get { return myServer; } }
        private MyDB db = new MyDB();

        public void SendMessage_CHAT(Socket sock, string msg)
        {
            string[] s = msg.Split('#');
            string id = s[0];
            string chat_msg = s[1];
            DateTime date = DateTime.Parse(s[2]);

            // 메시지 에코
            string packet = Packet.ChatSendmessageACK(true, id);
            string packet_brod = Packet.ChatSendmessageBROADCAST(id, chat_msg, date);

            //보낸  사람에겐 잘갔다고 해주기
            myServer.SendData(sock, packet);
            // 보낸 장본인 빼고 모두 브로드캐스트
            myServer.SendAllData(sock, packet_brod);
        }

        public void LogMessage(Socket sock, string msg)
        {
            //lock (locker)
            {
                Console.WriteLine("[LOG]: " + msg);
            }
            //Thread.Sleep(10);

        }

        public void PacketMessage(Socket sock, string msg)
        {
            //lock (locker)
            {

                Console.WriteLine("[PACKET]: " + msg);

                string[] sp = msg.Split('@');
                switch (int.Parse(sp[0]))
                {

                    case Packet.PACKET_CHAT_SENDMESSAGE: SendMessage_CHAT(sock, sp[1]); break;
                    default:
                        break;
                }
            }
            Thread.Sleep(10);
        }


        #region 0. 싱글톤 패턴
        public static ChatControl Singleton { get; } = null;
        static ChatControl() { Singleton = new ChatControl(); }
        private ChatControl()
        {
            //Temp();
        }
        #endregion

        #region 4. 시작과 종료 메서드
        public void Init()
        {
            try
            {
                myServer.Start(SERVER_PORT, LogMessage, PacketMessage);
                db.Connect();
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            WbLib.Pause();
        }
        public void Exit()
        {
            myServer.Close();
            db.Close();
        }
        #endregion
    }
}
