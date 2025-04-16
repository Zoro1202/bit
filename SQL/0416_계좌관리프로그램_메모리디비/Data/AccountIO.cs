using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0416_계좌관리프로그램_메모리디비
{
    class AccountIO
    {
        #region 1. 맴버필드, 프로퍼티(속성)
        public int KeyID { get; private set; }
        public int Number { get; private set; }
        public int Input { get; private set; }
        public int Output { get; private set; }
        public int Balance { get; private set; }
        public DateTime CTime { get; private set; }
        #endregion

        #region 2. 생성자
        public AccountIO(int _keyID, int _number, int _input, int _output, int _balance)
        {
            KeyID = _keyID;
            Number = _number;
            Input = _input;
            Output = _output;
            Balance = _balance;
            CTime = DateTime.Now;
        }
        public AccountIO(int _keyID, int _number, int _input, int _output, int _balance, DateTime _ctime)
        {
            KeyID = _keyID;
            Number = _number;
            Input = _input;
            Output = _output;
            Balance = _balance;
            CTime = _ctime;
        }
        #endregion

        #region 3. 기능 메서드
        public void Print()
        {
            Console.Write("{0,5} {1,10}원 {2,10}원 {3,10}원", Number, Input, Output, Balance);
            Console.Write("\t{0} {1}", WbLib.Get_Date(CTime), WbLib.Get_Time(CTime));
            Console.WriteLine();
        }
        public override string ToString()
        {
            return string.Format("{0}.계좌번호 {1} | {2} | 잔액 {3} | 날자 {4}"
                , KeyID
                , Number
                , Input > 0 ? "입금" + Input: Output > 0 ? "출금" + Output : "계좌 개설"
                , Balance
                , CTime.ToString()
            );
        }
        #endregion
    }
}
