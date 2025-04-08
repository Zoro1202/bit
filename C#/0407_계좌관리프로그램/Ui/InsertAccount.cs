using _0402_계좌관리프로그램;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WoosongBit41.Lib;

namespace _0407_계좌관리프로그램
{
    internal class InsertAccount
    {
        public static void Invoke()
        {
            Console.WriteLine("\n[계좌 저장]\n");
            int number = WbLib.InputInteger("계좌번호 입력"); // 계좌번호
            string name = WbLib.InputString("이름 입력");   // 계좌주 이름
            int balance = WbLib.InputInteger("입금액 입력"); // 초기 잔액
            int account_type = WbLib.InputAccountType(); // 계좌유형
            try
            {
                AccountControl con = AccountControl.Singleton;
                con.AccountInsert(number, name, balance, account_type);
            }
            catch(Exception e)
            {
                Console.WriteLine("계좌 생성 실패 : " + e.Message);
            }
        }
    }
}
