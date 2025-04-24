using _0424_chat_client;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace _0424_chat_client
{
    internal class ChatControl
    {
        private MyClient myClient = new MyClient(); // 소켓 통신을 위한 객체
        public ChatForm _ChatForm { get; set; }



        #region 0. 싱글톤 패턴
        public static ChatControl Instance { get; } = null;
        static ChatControl() { Instance = new ChatControl(); }
        private ChatControl()
        {
        }
        #endregion
        public void SendMessage(string id, string msg, DateTime date)
        {
            string packet = Packet.ChatSendmessage(id, msg, date);
            myClient.SendData(packet);
        }

        public void SendMessage_ACK(string msg)
        {
            string[] s = msg.Split('#');
            bool isvalid = bool.Parse(s[0]);
            string id = s[1];
        }

        public void BroadMessage(string msg)
        {
            string[] s = msg.Split('#');
            string id = s[0];
            string chat_msg = s[1];
            DateTime date = DateTime.Parse(s[2]);
            _ChatForm.Recv_Message(id, chat_msg, date);
        }

        #region CallBack Message
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
            Console.WriteLine("[PACKET]: " + msg);

            string[] sp = msg.Split('@');
            switch (int.Parse(sp[0]))
            {
                case Packet.PACKET_CHAT_SENDMESSAGE_ACK: SendMessage_ACK(sp[1]); break;
                case Packet.PACKET_CHAT_SENDMESSAGE_BROADCAST: BroadMessage(sp[1]); break;
                default:
                    break;
            }
        }
        #endregion

        #region init & exit
        public bool Init(string ip, int port)
        {
            return myClient.Start(ip, port, LogMessage, PacketMessage);
        }
        public void Exit()
        {
            myClient.Close();
        }
        #endregion

    }
}
