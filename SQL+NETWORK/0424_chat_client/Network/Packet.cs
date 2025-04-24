using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace _0424_chat_client
{
    internal static class Packet
    {
        //---------------------------------------------------------------------------------
        //LOGIN, LOGOUT, ETC
        public const int PACKET_MEMBER_LOGIN            = 1;  // insert account packet
        public const int PACKET_MEMBER_LOGIN_ACK        = 2;  // ack

        public const int PACKET_MEMBER_LOGOUT           = 3;  // select account packet
        public const int PACKET_MEMBER_LOGOUT_ACK       = 4;  // ack

        public const int PACKET_MEMBER_ADD              = 5;  // select account packet
        public const int PACKET_MEMBER_ADD_ACK          = 6;  // ack
        // CHATTING
        public const int PACKET_CHAT_SENDMESSAGE        = 7;  // input account packet
        public const int PACKET_CHAT_SENDMESSAGE_ACK    = 8;  // ack
        public const int PACKET_CHAT_SENDMESSAGE_BROADCAST  = 9;  // bradcasting your message
        public static string MemberLogin(string id, string pw)
        {
            string packet = PACKET_MEMBER_LOGIN + "@";
            packet += id + "#";
            packet += pw + "#";

            return packet;
        }
        public static string MemberLogout(string id)
        {
            string packet = PACKET_MEMBER_LOGOUT + "@";

            packet += id + "#";

            return packet;
        }
        public static string MemberAdd(string id, string pw, string name, Color color, DateTime date)
        {
            string packet = PACKET_MEMBER_ADD + "@";

            packet += id + "#";
            packet += pw + "#";
            packet += name + "#";
            packet += color.Name + "#";
            packet += date;

            return packet;
        }
        public static string ChatSendmessage(string id, string msg,DateTime date)
        {
            string packet = PACKET_CHAT_SENDMESSAGE + "@";

            packet += id + "#";
            packet += msg + "#";
            packet += date;

            return packet;
        }
    }
}
