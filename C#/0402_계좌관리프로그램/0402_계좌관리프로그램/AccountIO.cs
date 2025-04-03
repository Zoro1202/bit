//AccountIO.cs
using System;
using WoosongBit41.Lib;

namespace WoosongBit41.Data
{
    internal class AccountIO
    {
        #region 1. 맴버필드, 프로퍼티(속성)
        public int Number { get; private set; }// 계좌번호
        public int Input { get; private set; }// 입금액
        public int Output { get; private set; }// 출금액
        public int Balance { get; private set; }// 잔액
        public DateTime CTime { get; private set; } // 거래시간
        public int Type { get; private set; } //계좌 유형
        #endregion

        #region 2. 생성자
        public AccountIO(int _number, int _input, int _output, int _balance, int _type)
        {
            Number  = _number;
            Input   = _input;
            Output  = _output;
            Balance = _balance;
            Type = _type;
            CTime   = DateTime.Now;
        }
        public AccountIO(int _number, int _input, int _output, int _balance, int _type, DateTime _ctime)
        {
            Number  = _number;
            Input   = _input;
            Output  = _output;
            Balance = _balance;
            Type = _type;
            CTime   = _ctime;
        }
        #endregion

        #region 3. 기능 메서드
        public void Print()
        {
            Console.Write("{0,5} {1,10}원 {2,10}원 {3,10}원 {4}", Number, Input, Output, Balance, Type  == 0 ? "일반 계좌": Type == 1? "기부 계좌": "신용 계좌");
            Console.Write("\t{0} {1}", WbLib.Get_Date(CTime), WbLib.Get_Time(CTime));
            Console.WriteLine();
        }
        #endregion
    }
}
