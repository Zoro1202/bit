using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0417_XML
{
    class Program
    {
        static void Main(string[] args)
        {
            myXML xml = new myXML();
            xml.Sample("https://www.yna.co.kr/rss/news.xml");
        }
    }
}
