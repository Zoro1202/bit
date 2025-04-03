using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using WoosongBit41.Data;

namespace _0402_계좌관리프로그램
{
    /// <summary>
    /// 기부 계좌 : 이자율 -5% 고정
    /// </summary>
    class ContriAccount : Account
    {
        public int Contribution { get; private set; } // 기부금액    
        public ContriAccount(int _number, string _name, int _balance, int _type)
            : base(_number, _name, (int)(_balance * ((float)95 / 100)), _type)
        {
            Contribution = (int)(_balance * ((float)5 / 100));
        }
        public ContriAccount(int _number, string _name, int _balance, int _type, int _contri,DateTime _time)
            : base(_number, _name, (int)(_balance * ((float)95 / 100)), _type, _time)
        {
            Contribution = _contri;
        }

        public ContriAccount(int _number, string _name, int _balance,int _type, DateTime _time)
            : base(_number, _name, (int)(_balance * ((float)95 / 100)), _type, _time)
        {
            Contribution = (int)(_balance * ((float)5 / 100));
        }

        public override void Input_Money(int money)
        {
            if (money <= 0)
                throw new Exception("잘못된 금액");

            Balance = Balance + (int)(money * ((float)95 / 100));
            Contribution = Contribution + (int)(money * ((float)5 / 100));
        }
    }
}
