using System;
using System.Drawing;
using System.Linq;
using System.Net.Http.Headers;
using System.Net.Sockets;

namespace _0424_chat_client
{
    internal class MemberControl
    {
        private MyClient myClient = new MyClient(); // 소켓 통신을 위한 객체
        public LoginForm _LoginForm { get; set; }
        public AddMemberForm _AddMemberForm { get; set; }
        public ChatForm _ChatForm { get; set; }
        #region 0. 싱글톤 패턴
        public static MemberControl Instance { get; } = null;
        static MemberControl() { Instance = new MemberControl(); }
        private MemberControl()
        {
        }
        #endregion

        #region 기능 로그인, 로그아웃, 회원가입
        public bool Login(string id, string password)
        {
            string packet = Packet.MemberLogin(id, password);
            myClient.SendData(packet);
            return true;
        }
        public bool Logout(string id) 
        {
            string packet = Packet.MemberLogout(id);
            myClient.SendData(packet);
            return true;
        }
        public bool AddMember(string id, string pw, string name, Color color , DateTime date)
        {
            string packet = Packet.MemberAdd(id, pw, name, color, date);
            myClient.SendData(packet);
            return true;    
        }
        #endregion

        #region ACK 로그인 로그아웃 회원가입
        public void Login_ACK(string msg)
        {
            string[] s = msg.Split('#');
            bool b = bool.Parse(s[0]);
            string id = s[1];
            string name = s[2];
            _LoginForm.Login_Result(b, id, name);
        }
        public void Logout_ACK(string msg)
        {
            string[] s = msg.Split('#');
            bool b = bool.Parse(s[0]);
            string id = s[1];
            _ChatForm.Logout_Result(b, id);
        }
        public void AddMember_ACK(string msg)
        {
            string[] s = msg.Split('#');
            bool b = bool.Parse(s[0]);
            string id = s[1];
            string name = s[2];
            _AddMemberForm.AddMember_Result(b, id, name);
            //Color color = Color.(s[3]);
            //DateTime date s[4];
        }
        #endregion
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
                case Packet.PACKET_MEMBER_LOGIN_ACK:    Login_ACK(sp[1]); break;
                case Packet.PACKET_MEMBER_LOGOUT_ACK:   Logout_ACK(sp[1]); break;
                case Packet.PACKET_MEMBER_ADD_ACK:      AddMember_ACK(sp[1]); break;
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
        public void Init(string ip, int port)
        {
            if (myClient.Start(ip, port, LogMessage, PacketMessage) == false)
                throw new Exception("회원관리 서버 연결 오류");
        }
        public void Exit()
        {
            myClient.Close();
        }
        #endregion

    }
}
