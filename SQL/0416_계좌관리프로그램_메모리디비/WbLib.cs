using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0416_계좌관리프로그램_메모리디비
{
    internal static class WbLib
    {
        #region 1. 로고, 메뉴, 종료출력 메시지
        public static void Pause()
        {
            Console.Write("\n\n엔터키를 누르세요..........");
            Console.ReadKey(true);
        }

        public static void Logo()
        {
            Console.Clear();
            Console.WriteLine("*************************************************************************");
            Console.WriteLine(" 2025년 2학기 우송비트고급41기");
            Console.WriteLine(" C#언어");
            Console.WriteLine(" 계좌 관리 프로그램");
            Console.WriteLine(" 2025-04-02");
            Console.WriteLine(" ccm");
            Console.WriteLine("*************************************************************************");
            Pause();
        }

        public static ConsoleKey MenuPrint()
        {
            Console.WriteLine("*************************************************************************");
            Console.WriteLine("[ESC] 프로그램 종료");
            Console.WriteLine("[F1] 계좌 저장");
            Console.WriteLine("[F2] 계좌 검색(계좌번호,Uniq)");
            Console.WriteLine("[F3] 계좌 수정(입금)");
            Console.WriteLine("[F4] 계좌 수정(출금)");
            Console.WriteLine("[F5] 계좌 삭제");
            Console.WriteLine("*************************************************************************");
            return Console.ReadKey().Key;
        }

        public static void Ending()
        {
            Console.Clear();
            Console.WriteLine("*************************************************************************");
            Console.WriteLine(" 프로그램을 종료합니다.");
            Console.WriteLine("*************************************************************************");
            Pause();
        }
        #endregion

        #region 2. 입력 
        public static int InputInteger(string msg)
        {
            Console.Write(msg + " : ");
            return int.Parse(Console.ReadLine());
        }

        public static float InputFloat(string msg)
        {
            Console.Write(msg + " : ");
            return float.Parse(Console.ReadLine());
        }

        public static char InputChar(string msg)
        {
            Console.Write(msg + " : ");
            return char.Parse(Console.ReadLine());
        }

        public static string InputString(string msg)
        {
            Console.Write(msg + " : ");
            return Console.ReadLine();
        }
        #endregion

        #region 3. 날짜와 시간을 문자열로 반환
        public static string Get_Date(DateTime time)
        {
            return string.Format("{0}-{1}-{2}", time.Year, time.Month, time.Day);
        }
        public static string Get_Time(DateTime time)
        {
            return string.Format("{0}:{1}:{2}", time.Hour, time.Minute, time.Second);
        }
        #endregion
    }
}
