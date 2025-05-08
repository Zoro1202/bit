using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace _0507_WCF_PictureService
{
    class Program
    {
        static void Main(string[] args)
        {
            ServiceHost host = new ServiceHost(typeof(CPicture));

            // 서비스 호스트를 생성한다.
            host.Open(); // 서비스 호스트를 연다.
            Console.Write("아무 키나 눌러 종료....");
            Console.ReadKey(); // 키 입력을 대기한다.
            host.Close(); // 서비스 호스트를 닫는다.
        }
    }
}
