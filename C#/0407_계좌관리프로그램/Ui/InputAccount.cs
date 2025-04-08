using _0402_계좌관리프로그램;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WoosongBit41.Data;
using WoosongBit41.Lib;

namespace _0407_계좌관리프로그램
{
    class InputAccount
    {
        public static void Invoke()
        {
            Console.WriteLine("\n[계좌 입금]\n");
            try
            {
                int number = WbLib.InputInteger("계좌번호 입력");
                int money = WbLib.InputInteger("입금액 입력");

                AccountControl con = AccountControl.Singleton;

                con.AccountInput(number, money); // 계좌번호로 계좌 찾기

                Console.WriteLine("입금 성공");
                Console.WriteLine("거래내역 저장 성공");
            }
            catch(Exception ex)
            {
                Console.WriteLine("[계좌 입금 실패] " + ex.Message);
            }
        }
    }
}
