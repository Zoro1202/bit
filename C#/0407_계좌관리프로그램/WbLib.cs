//WbLib.cs
using System;

namespace WoosongBit41.Lib
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
            Console.WriteLine(" 2025-04-07");
            Console.WriteLine(" lsy");
            Console.WriteLine("*************************************************************************");
            Pause();
        }

        public static ConsoleKey MenuPrint()
        {
            Console.WriteLine("*************************************************************************");
            Console.WriteLine("[ESC] 프로그램 종료");
            Console.WriteLine("[F1] 계좌 저장");
            Console.WriteLine("[F2] 계좌 검색(계좌번호,Uniq)");
            Console.WriteLine("[F3] 계좌 검색(이름, all)");
            Console.WriteLine("[F4] 계좌 수정(입금)");
            Console.WriteLine("[F5] 계좌 수정(출금)");
            Console.WriteLine("[F6] 계좌 삭제");
            Console.WriteLine("[F7] 계좌 정렬(돈)");
            Console.WriteLine("[F8] 계좌 정렬(이름)");
            Console.WriteLine("*************************************************************************");
            return Console.ReadKey().Key;        
        }

        public static int InputAccountType()
        {
            Console.WriteLine("*************************************************************************");
            Console.WriteLine("[F1] 일반 계좌");
            Console.WriteLine("[F2] 기부 계좌");
            Console.WriteLine("[F3] 신용 계좌");
            Console.WriteLine("*************************************************************************");
            switch (Console.ReadKey().Key)
            {
                case ConsoleKey.F1:
                    return 0; // 일반 계좌
                case ConsoleKey.F2:
                    return 1; // 기부 계좌
                case ConsoleKey.F3:
                    return 2; // 신용 계좌
                default:
                    Console.WriteLine("잘못된 계좌 유형입니다.");
                    return -1;
            }
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
            int result;
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
