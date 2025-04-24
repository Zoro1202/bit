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
        public const int PACKET_MEMBER_LOGIN            = 1;  // insert account packet
        public const int PACKET_MEMBER_LOGIN_ACK        = 2;  // ack

        public const int PACKET_MEMBER_LOGOUT           = 3;  // select account packet
        public const int PACKET_MEMBER_LOGOUT_ACK       = 4;  // ack

        public const int PACKET_MEMBER_ADD              = 5;  // select account packet
        public const int PACKET_MEMBER_ADD_ACK          = 6;  // ack

        public const int PACKET_CHAT_SENDMESSAGE        = 7;  // input account packet
        public const int PACKET_CHAT_SENDMESSAGE_ACK    = 8;  // ack

        public const int PACKET_SERVER_REGISTER_NEW = 909;

        public static string NewbieMessage()
        {
            string packet = PACKET_SERVER_REGISTER_NEW + "@";
            return packet;
        }
    }
}
