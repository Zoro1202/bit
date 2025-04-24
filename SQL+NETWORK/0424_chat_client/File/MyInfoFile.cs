using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection.Emit;
using System.Security.Principal;
using System.Text;
using System.Threading.Tasks;

namespace _0424_chat_client
{
    internal static class MyInfoFile
    {
        private const string FILENAME = "chatclient.ini";

        //private const string MEMBER_SERVER_IP = "220.90.180.111";
        private const string MEMBER_SERVER_IP = "127.0.0.1";
        private const int MEMBER_SERVER_PORT = 9000;

        private const string CHAT_SERVER_IP = "127.0.0.1";
        private const int CHAT_SERVER_PORT = 8000;

        public static void WriteMessage(string id, string pw)
        {
            using (StreamWriter writer = new StreamWriter(FILENAME))
            {
                writer.WriteLine("회원서버아이피:" + MEMBER_SERVER_IP);
                writer.WriteLine("회원서버포트:" + MEMBER_SERVER_PORT);
                writer.WriteLine("채팅서버아이피:" + CHAT_SERVER_IP);
                writer.WriteLine("채팅서버포트:" + CHAT_SERVER_PORT);
                writer.WriteLine("회원아이디:" + id);
                writer.WriteLine("회원패스워드:" + pw);
            }
        }
        public static void ReadMessage(out string mip, out int mport, out string cip, out int cport, out string id, out string pw)
        {
            using (StreamReader reader = new StreamReader(FILENAME))
            {
                mip = reader.ReadLine().Split(':')[1];
                mport = int.Parse(reader.ReadLine().Split(':')[1]);
                cip = reader.ReadLine().Split(':')[1];
                cport = int.Parse(reader.ReadLine().Split(':')[1]);
                id = reader.ReadLine().Split(':')[1];
                pw = reader.ReadLine().Split(':')[1];
            }
        }

    }
}
