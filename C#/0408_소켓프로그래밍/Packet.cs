using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ServerNetWork
{
    // [Serializable]
    internal static class Packet
    {
        public const int PACKET_SHORTMESSAGE = 1;   // send short message
        public const int PACKET_SHORTMESSAGE_S = 2; // success
        public const int PACKET_SHORTMESSAGE_F = 3; // fail
        #region client -> server
        public static string shortMessage(string name, string msg, DateTime msgtime)
        {
            string packet = PACKET_SHORTMESSAGE + "@";
            packet += name + "#";
            packet += msg + "#";
            packet += msgtime;
            return packet;
        }
        #endregion
        #region server -> client
        public static string shortMessageAck(bool b, string name, string msg, DateTime msgtime)
        {
            string packet = string.Empty;
            if (b)
                packet += PACKET_SHORTMESSAGE_S + "@";
            else
                packet += PACKET_SHORTMESSAGE_F + "@";
            packet += name + "#";
            packet += msg + "#";
            packet += msgtime;
            return packet;
        }
        #endregion
    }
}
