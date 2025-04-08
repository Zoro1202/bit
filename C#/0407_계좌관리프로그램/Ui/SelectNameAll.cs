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
    class SelectNameAll
    {
        public static void Invoke()
        {
            Console.WriteLine("\n[계좌 검색(이름)]\n");
            try
            {
                string name = WbLib.InputString("이름 입력");

                AccountControl con = AccountControl.Singleton;
                List<Account> accounts = con.SelectAllName(name);
                Print(accounts);
            }
            catch (Exception ex)
            {
                Console.WriteLine("[검색 실패] " + ex.Message);
            }
        }

        private static void Print(List<Account> accounts)
        {
            foreach (Account acc in accounts)
            {
                acc.Print();
            }
        }
    }
}
