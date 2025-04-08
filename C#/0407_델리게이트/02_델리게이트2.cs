using Microsoft.IdentityModel.Threading;
//a뭔가 문제있음
namespace _0407_델리게이트
{
    internal delegate int DelFunc(string msg, int a, int b); //델리게이트 선언
    internal class Sample
    {
        /// <summary>
        /// 동기 방식
        /// </summary>
        public void Example1()
        {
            int res1 = Sum("첫번째 호출", 0, 100);
            int res2 = Sum("두번째 호출", 0, 200);
            int res3 = Sum("세번째 호출", 0, 300);

            Console.WriteLine($"res1 = {res1}, res2 = {res2}, res3 = {res3}");
        }
        //비동기 방식 -> 대리자 사용
        public void Example2 ()
        {
            DelFunc f1 = new DelFunc(Sum); //델리게이트에 메서드 등록
            DelFunc f2 = new DelFunc(Sum); //델리게이트에 메서드 등록
            DelFunc f3 = new DelFunc(Sum); //델리게이트에 메서드 등록

            f1.BeginInvoke("f1: 첫번째 호출", 0, 100, EndSum, "f1");
            f2.BeginInvoke("f2: 두번째 호출", 0, 100, EndSum, "f2");
            f3.BeginInvoke("f3: 세번째 호출", 0, 100, EndSum, "f3");
        }
        public void EndSum(IAsyncResult iar)
        {
            string str = (string)iar.AsyncState; // begin invoke에서 전달한 매개변수 (마지막 인자)
            Console.WriteLine($"EndSum : {str}");
            //AsyncResult ar = iar as AsyncResult;
            //DelFunc f = ar.AsyncDelegate as DelFunc; //델리게이트
            //Console.WriteLine($"EndSum : {a}"); //EndInvoke 호출/**/

        }
        public int Sum(string msg, int a, int b) // 연산 함수
        {
            int sum = 0;
            for(;a <= b; a++)
            {
                sum += a;
                Console.WriteLine($"msg = {msg}, {a} => {sum}");
                Thread.Sleep(100);
            }
            return sum;
        }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            Sample s1 = new Sample();
            //s1.Example1();//동기 방식
            s1.Example2();//비동기 방식
        }
    }
}
