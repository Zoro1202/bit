using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0404_실기평가
{
    public enum ELOGTYPE
    { 
        INPUT,
        SELECT,
        UPDATE,
        DELETE,
        SORT
    }
    class LogArgs
    {
        public ELOGTYPE LogType { get; private set; }
        public string Message { get; private set; }
        public DateTime CurTime { get; private set; }
        public LogArgs(ELOGTYPE logtype, string msg)
        {
            LogType = logtype;
            Message = msg;
            CurTime = DateTime.Now;
        }
    }
    internal delegate void LogDele (object obj, LogArgs e);
}
