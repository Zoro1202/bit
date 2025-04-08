using _0402_계좌관리프로그램;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using WoosongBit41.Data;

namespace _0407_계좌관리프로그램
{
    class LogManager : IDisposable
    {
        #region 생성자 & 소멸자
        StreamWriter writer = null;
        
        public LogManager()
        {
            AccountControl con = AccountControl.Singleton;
            con.LogEvent += TotalAccount; // 전체 계좌 조회
            writer = new StreamWriter("logfile.txt", true); //로그 파일 생성
            //파일 생성
        }
        ~LogManager() 
        {
            Dispose();
        }

        public void Dispose()
        {
            // Dispose
            writer.Dispose();
            GC.SuppressFinalize(this);
        }
        #endregion

        #region 이벤트를 수신할 핸들러 함수

        public void InsertAccount(object obj, LogArgs e)
        {
            string msg = string.Format("[{0}] {1} ({2} {3})", e.Type, e.Msg, e.CTime.ToShortDateString(), e.CTime.ToLongTimeString());
            writer.WriteLine(msg);
        }
        public void SelectAccount(object obj, LogArgs e)
        {
            string msg = string.Format("[{0}] {1} ({2} {3})", e.Type, e.Msg, e.CTime.ToShortDateString(), e.CTime.ToLongTimeString());
            writer.WriteLine(msg);
        }
        public void InputAccount(object obj, LogArgs e)
        {
            string msg = string.Format("[{0}] {1} ({2} {3})", e.Type, e.Msg, e.CTime.ToShortDateString(), e.CTime.ToLongTimeString());
            writer.WriteLine(msg);
        }
        public void OutputAccount(object obj, LogArgs e)
        {
            string msg = string.Format("[{0}] {1} ({2} {3})", e.Type, e.Msg, e.CTime.ToShortDateString(), e.CTime.ToLongTimeString());
            writer.WriteLine(msg);
        }
        public void DeleteAccount(object obj, LogArgs e)
        {
            string msg = string.Format("[{0}] {1} ({2} {3})", e.Type, e.Msg, e.CTime.ToShortDateString(), e.CTime.ToLongTimeString());
            writer.WriteLine(msg);
        }
        public void TotalAccount(object obj, LogArgs e)
        {
            string msg = string.Format("[{0}] {1} ({2} {3})", e.Type, e.Msg, e.CTime.ToShortDateString(), e.CTime.ToLongTimeString());
            writer.WriteLine(msg);
        }
        #endregion
    }
}
