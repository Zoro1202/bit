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

        #region 0. 싱글톤 패턴
        public static ChatControl Instance { get; } = null;
        static ChatControl() { Instance = new ChatControl(); }
        private ChatControl()
        {
        }
        #endregion
        public void SendMessage(string id, string msg, DateTime date)
        {

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
                //case Packet.PACKET_INSERT_ACCOUNT_ACK: AccountInsert_Ack(sp[1]); break;
                //case Packet.PACKET_SELECT_ACCOUNT_ACK: AccountSelect_Ack(sp[1]); break;
                //case Packet.PACKET_SELECTALL_ACCOUNT_ACK: AccountSelectAll_Ack(sp[1]); break;
                //case Packet.PACKET_TRANSFER_ACCOUNT_ACK: AccountTransfer_Ack(sp[1]); break;
                //case Packet.PACKET_DELETE_ACCOUNT_ACK: AccountDelete_Ack(sp[1]); break;
                //case Packet.PACKET_INPUT_ACCOUNT_ACK: AccountInput_Ack(sp[1]); break;
                //case Packet.PACKET_OUTPUT_ACCOUNT_ACK: AccountOutput_Ack(sp[1]); break;
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
