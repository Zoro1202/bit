using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0404_실기평가
{
    class LogManager
    {

        #region 생성자 & 소멸자
        StreamWriter writer = null;

        public LogManager()
        {
            BookControl book = BookControl.Instance;
            book.LogEvent += TotalLog; // 전체 계좌 조회
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

        public void TotalLog(object obj, LogArgs e)
        {
            string msg = string.Format("[{0}] {1} ({2} {3})", e.LogType, e.Message, e.CurTime.ToShortDateString(), e.CurTime.ToLongTimeString());
            writer.WriteLine(msg);
        }
        #endregion
    }
}
