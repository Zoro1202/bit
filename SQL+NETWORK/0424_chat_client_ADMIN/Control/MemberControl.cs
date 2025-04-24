using System;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Http.Headers;
using System.Net.Sockets;

namespace _0424_chat_client
{
    internal class MemberControl
    {
        
        myDB db = new myDB();
        public MyClient client = null;
        public MainForm _MainForm { get; set; }
        #region 0. 싱글톤 패턴
        public static MemberControl Instance { get; } = null;
        static MemberControl() { Instance = new MemberControl(); }
        private MemberControl()
        {
        }
        #endregion

        public void LogMessage(Socket sock, string msg)
        {
            //lock (locker)
            {
                Console.WriteLine("[LOG]: " + msg);
            }
            //Thread.Sleep(10);
        }

        public void Newbie()
        {
            _MainForm.MainForm_Load(0, new EventArgs());
        }
        public void PacketMessage(Socket sock, string msg)
        {
            Console.WriteLine("[PACKET]: " + msg);

            string[] sp = msg.Split('@');
            switch (int.Parse(sp[0]))
            {
                case Packet.PACKET_SERVER_REGISTER_NEW: Newbie(); break;
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

        public void Init()
        {
            client = new MyClient();
            string mip, cip, id, pw;
            int mport, cport;

            MyInfoFile.ReadMessage(out mip, out mport, out cip, out cport, out id, out pw);
            if (client.Start(mip, mport, LogMessage, PacketMessage) == false)
            { 
                client.Dispose();
                client = null;
            }
        }

        public void Exit()
        {
            client.Close();
        }

        public DataTable GetMemberTable()
        {
            return db.GetMemberTable();
        }
        //Packet.NewbieMessage

    }
}
