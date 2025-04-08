using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0407_계좌관리프로그램
{
    internal enum ELOGTYPE
    {
        Insert_Account,
        Select_Account,
        Inptut_Account,
        Output_Account,
        Delete_Account,
        Print_Account
    }
    class LogArgs : EventArgs
    {
        public ELOGTYPE Type { get; private set; } // 계좌유형
        public string Msg { get; private set; } // 메시지
        public DateTime CTime { get; private set; } // 거래시간
        public LogArgs(ELOGTYPE type, string msg)
        {
            Type = type;
            Msg = msg;
            CTime = DateTime.Now;
        }
    }
    //delegate
    internal delegate void LogDel(object obj, LogArgs e);
}
