namespace _0407_델리게이트
{
    internal delegate void Del(int result); //델리게이트 선언
    internal class Sample
    {
        public Del DelFunc { get; set; } = null;//델리게이트 변수
        public int Add(int a, int b)
        {
            return a + b;
        }
        public void Sub(int a, int b)
        {
            int res = a - b;
            if (DelFunc == null)
            {
                Console.WriteLine("DelFunc is null");
                return;
            }
            else
            {
                //callback 호출
                DelFunc.Invoke(res);
                //DelFunc(res);
            }
        }
        public void Sub2(int a, int b)
        {
            int res = a - b - b;
            if (DelFunc == null)
            {
                Console.WriteLine("DelFunc is null");
                return;
            }
            else
            {
                //callback 호출
                DelFunc.Invoke(res);
                //DelFunc(res);
            }
        }

    }
    internal class Program
    {

        //callback 함수
        static void result(int result)
        {
            Console.WriteLine("CallBack : " + result);
        }
        static void Main(string[] args)
        {
            Sample s1 = new Sample();
            Console.WriteLine(s1.Add(1, 2));

            s1.DelFunc = new Del(result); //델리게이트에 메서드 등록
            //s1.DelFunc = result; //델리게이트에 메서드 등록
            s1.Sub(5, 3); //Sub 메서드 호출

        }
    }
}
