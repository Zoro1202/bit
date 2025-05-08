using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace _0507_도서관리_WCFService
{
    class Program
    {
        static void Main(string[] args)
        {
            ServiceHost host = new ServiceHost(typeof(BookWCFService));
            host.Open();
            Console.WriteLine("Press Any key to stop the service");
            Console.ReadKey();
            host.Close();
        }
    }
}
