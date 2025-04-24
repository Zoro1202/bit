using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0424_chat_client
{
    class Member
    {
        public string _ID { get; set; }
        public string _PW { get; set; }
        public string _Name { get; set; }
        public Color _Color { get; set; }
        public DateTime _Date { get; set; }
        public Member(string iD, string pW, string name, Color color, DateTime date)
        {
            _ID = iD;
            _PW = pW;
            _Name = name;
            _Color = color;
            _Date = date;
        }

        public override string ToString()
        {
            return string.Format($"{_ID}, {_Name}, {_Color}, {_Date.ToShortDateString()}");
        }
    }
}
