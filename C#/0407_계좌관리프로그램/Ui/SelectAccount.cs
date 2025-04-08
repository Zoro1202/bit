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
    class SelectAccount
    {
        public static void Invoke()
        {
        Console.WriteLine("\n[계좌 검색]\n");
            try
            {

                int number = WbLib.InputInteger("계좌번호 입력");

                AccountControl con = AccountControl.Singleton;
                Account account = con.NumberToAccount(number);

                con.SelectNumber(number);
                account.Println();
                Console.WriteLine("--------------------------------------------");
                con.AccountIOPrint(number);
            }
            catch (Exception ex)
            {
                Console.WriteLine("[계좌 검색 실패] " + ex.Message);
            }
        }
    }
}
