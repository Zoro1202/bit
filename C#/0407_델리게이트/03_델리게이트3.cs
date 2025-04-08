using System;
using System.IdentityModel;

namespace _0407_델리게이트
{
    #region 게시자와 구독자가 모두 알고 있는 정보
    //1. Event Args
    internal class CalArgs : EventArgs
    {
        public int Num1 { get; private set; }
        public int Num2 { get; private set;}

        public char Oper { get; private set;}

        public int Result { get; private set;}

        public CalArgs(int num1, char oper, int num2, int res)
        {
            this.Num1 = num1;
            this.Oper = oper;
            this.Num2 = num2;
            this.Result = res;
        }
    }
    //2. Event delegate
    internal delegate void CalDel(object obj, CalArgs e);
    #endregion

    //3. 이벤트 게시자
    internal class Sample
    {
        //3.1. 이벤트 선언
        public event CalDel DelEvent = null;

        //3.2. 이벤트 발생 (게시)
        public void Add(int n1, int n2)
        {
            int result = n1 + n2;
            if (DelEvent != null)
            {
                DelEvent(this, new CalArgs(n1, '+', n2, result));
            }
        }
        public void Sub(int n1, int n2)
        {
            int result = n1 - n2;
            if (DelEvent != null)
            {
                DelEvent(this, new CalArgs(n1, '-', n2, result));
            }
        }
    }
    internal class Program
    {
        //이벤트를 수신할 핸들러 함수
        static void ResultHandler(object obj, CalArgs e)
        {
            Console.WriteLine("{0} {1} {2} = {3}", e.Num1, e.Oper, e.Num2, e.Result);
        }

        static void Main(string[] args)
        {
            Sample s1 = new Sample();
            s1.DelEvent += ResultHandler;
            s1.Add(10, 20);
        }
    }
}
