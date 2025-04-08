using _0402_계좌관리프로그램;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WoosongBit41.Lib;

namespace _0407_계좌관리프로그램
{
    class DeleteAccount
    {
        public static void Invoke()
        {
            Console.WriteLine("\n[계좌 삭제]\n");
            try
            {
                int number = WbLib.InputInteger("계좌번호 입력");

                AccountControl con = AccountControl.Singleton;

                //int idx = con.NumberToIdx(number);

                con.AccountDelete(number);

                Console.WriteLine("계좌 삭제 성공");
                Console.WriteLine("거래내역 삭제 성공");
            }
            catch (Exception ex)
            {
                Console.WriteLine("[삭제 실패] " + ex.Message);
            }

        }
    }
}
