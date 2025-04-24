//Packet.cs
using System;
using System.Drawing;

namespace _0424_chat_server_console.NetWorkServer
{
    // [Serializable]
    internal static class Packet
    {
        public const int PACKET_MEMBER_LOGIN = 1;  // insert account packet
        public const int PACKET_MEMBER_LOGIN_ACK = 2;  // ack

        public const int PACKET_MEMBER_LOGOUT = 3;  // select account packet
        public const int PACKET_MEMBER_LOGOUT_ACK = 4;  // ack

        public const int PACKET_MEMBER_ADD = 5;  // select account packet
        public const int PACKET_MEMBER_ADD_ACK = 6;  // ack

        public const int PACKET_CHAT_SENDMESSAGE = 7;  // input account packet
        public const int PACKET_CHAT_SENDMESSAGE_ACK = 8;  // ack
        public const int PACKET_CHAT_SENDMESSAGE_BROADCAST = 9;

        public const int ADMIN_TEST = 909;
        public static string MemberLoginACK(bool isvalid, string id, string name)
        {
            string packet = PACKET_MEMBER_LOGIN_ACK + "@";
            packet += isvalid + "#";
            packet += id + "#";
            packet += name;

            return packet;
        }
        public static string MemberLogoutACK(bool isvalid, string id)
        {
            string packet = PACKET_MEMBER_LOGOUT_ACK + "@";

            packet += isvalid + "#";
            packet += id;

            return packet;
        }
        public static string MemberAddACK(bool isvalid, string id, string name)
        {
            string packet = PACKET_MEMBER_ADD_ACK + "@";

            packet += isvalid + "#";
            packet += id + "#";
            packet += name + "#";

            return packet;
        }
        public static string ChatSendmessageACK(bool isvalid, string id)
        {
            string packet = PACKET_CHAT_SENDMESSAGE_ACK + "@";

            packet += isvalid + "#";
            packet += id;

            return packet;
        }
        public static string ChatSendmessageBROADCAST(string id, string msg, DateTime date)
        {
            string packet = PACKET_CHAT_SENDMESSAGE_BROADCAST + "@";
            packet += id + "#";
            packet += msg + "#";
            packet += date;

            return packet;
        }
        public static string TEST()
        {
            string packet = ADMIN_TEST + "@";
            return packet;
        }
    }
}
