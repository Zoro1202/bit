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
    class PrintAllAccount
    {
        public static void Invoke()
        {
            Console.WriteLine("\n[전체 계좌 출력]\n");
            try
            {
                AccountControl con = AccountControl.Singleton;
                PrintAll(con.Accounts, con.Account_Count); // 전체 계좌 출력
                PrintAll_IO(con.Accountios, con.AccountIO_Count); // 전체 거래 내역 출력
            }
            catch (Exception ex)
            {
                Console.WriteLine("[전체 계좌 출력 실패] " + ex.Message);
            }
        }
        /// <summary>
        /// 전체 계좌 출력
        /// </summary>
        /// <param name="accounts"></param>
        /// <param name="count"></param>
        private static void PrintAll(WbArray accounts, int count)
        {
            Console.WriteLine("계좌번호\t이름\t잔액");
            Console.WriteLine("--------------------------------------------");
            for (int i = 0; i < count; i++)
            {
                Account acc = (Account)accounts.Arr[i];
                acc.Print();
            }
        }
        /// <summary>
        /// 거래 내역 출력
        /// </summary>
        /// <param name="accountios"></param>
        /// <param name="count"></param>
        private static void PrintAll_IO(WbArray accountios, int count)
        {
            Console.WriteLine("계좌번호\t이름\t잔액");
            Console.WriteLine("--------------------------------------------");
            for (int i = 0; i < count; i++)
            {
                AccountIO acc = (AccountIO)accountios.Arr[i];
                acc.Print();
            }
            Console.WriteLine("--------------------------------------------");
        }
    }
}
