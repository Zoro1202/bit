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
    class OutputAccount
    {
        public static void Invoke()
        {
            try
            {
                Console.WriteLine("\n[계좌 출금]\n");

                int number = WbLib.InputInteger("계좌번호 입력");
                int money = WbLib.InputInteger("출금액 입력");

                AccountControl con = AccountControl.Singleton;
                con.AccountOutput(number, money);

                Console.WriteLine("출금 성공");
                Console.WriteLine("거래내역 저장 성공");
            }
            catch (Exception ex)
            {
                Console.WriteLine("[출금 실패] " + ex.Message);
            }
        }
        
    }
}
