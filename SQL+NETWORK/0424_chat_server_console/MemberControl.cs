using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Security.Principal;
using System.Threading;
using _0424_chat_server_console.ServerNet;
using _0424_chat_server_console.NetWorkServer;
using System.Drawing;
using System.Runtime.Remoting.Contexts;

namespace _0424_chat_server_console
{
    internal class MemberControl
    {
        //private const string SERVER_IP = "127.0.0.1"; //서버 IP주소 (루프백)
        private const int SERVER_PORT = 9000; //서버 포트번호

        public static MyServer myServer = new MyServer(); //소켓 통신을 위한 객체
        private MyDB db = new MyDB();

        public void MemberLogin(Socket sock, string msg)
        {
            string[] s = msg.Split('#');
            string id = s[0];
            string pw = s[1];

            //DB...
            string name = "DB에서 획득";

            // 로그인 처리
            //DB에 있는지 확인 t / f
            string[] info = db.Login_Member(id, pw);
            string packet = string.Empty;
            //ACK
            if (db.Login_Member_UPDATE(1, info[0]) && info != null)
                packet = Packet.MemberLoginACK(true, info[0], info[1]);
            else
                packet = Packet.MemberLoginACK(false, id, name);

            myServer.SendData(sock, packet);
            myServer.SendAllData(sock, Packet.TEST());
            ChatControl.Singleton.MyServer.SendAllData_me(sock, Packet.ChatSendmessageBROADCAST("["+id+"]", "님이 입장했습니다!", DateTime.Now));
        }
        public void MemberLogout(Socket sock, string msg)
        {
            string[] s = msg.Split('#');
            string id = s[0];
            //로그아웃 처리
            string packet = string.Empty;
            if (db.Login_Member_UPDATE(0, id))
                packet = Packet.MemberLogoutACK(true, id);

            //ACK
            myServer.SendData(sock, packet);
            myServer.SendAllData(sock, Packet.TEST());
            ChatControl.Singleton.MyServer.SendAllData_me(sock, Packet.ChatSendmessageBROADCAST("[" + id + "]", "님이 퇴장했습니다!", DateTime.Now));
        }
        public void MemberAdd(Socket sock, string msg)
        {
            string[] s = msg.Split('#');
            string id = s[0];
            string pw = s[1];
            string name = s[2];
            Color color = Color.FromName(s[3]);
            DateTime date = DateTime.Parse(s[4]);
            //ACK
            string packet = string.Empty;
            if (db.Register_Member(id, pw, name, color, date))
                packet = Packet.MemberAddACK(true, id, name);
            else
                packet = Packet.MemberAddACK(false, id, name);
            myServer.SendData(sock, packet);
            myServer.SendAllData(sock, Packet.TEST());
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

                    case Packet.PACKET_MEMBER_LOGIN: MemberLogin(sock, sp[1]); break;
                    case Packet.PACKET_MEMBER_LOGOUT: MemberLogout(sock, sp[1]); break;
                    case Packet.PACKET_MEMBER_ADD: MemberAdd(sock, sp[1]); break;
                    //case Packet.PACKET_OUTPUT_ACCOUNT: AccountOutput(sock, sp[1]); break;
                    //case Packet.PACKET_DELETE_ACCOUNT: AccountDelete(sock, sp[1]); break;
                    //case Packet.PACKET_SELECTALL_ACCOUNT: AccountSelectAll(sock, sp[1]); break;
                    //case Packet.PACKET_TRANSFER_ACCOUNT: AccountTransfer(sock, sp[1]); break;
                    default:
                        break;
                }
            }
            Thread.Sleep(10);
        }


        #region 0. 싱글톤 패턴
        public static MemberControl Singleton { get; } = null;
        static MemberControl() { Singleton = new MemberControl(); }
        private MemberControl()
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
