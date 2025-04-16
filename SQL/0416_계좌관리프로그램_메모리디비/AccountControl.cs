using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0416_계좌관리프로그램_메모리디비
{
    class AccountControl
    {

        AccountMemoryDB acc_db = new AccountMemoryDB();

        public AccountMemoryDB AccDB { get{ return acc_db; } }

        #region 0. 싱글톤 패턴
        public static AccountControl Singleton { get; } = null;
        static AccountControl() { Singleton = new AccountControl(); }
        private AccountControl()
        {
            //Temp();
        }
        #endregion

        #region 2. 기능 메서드
        public void AccountInsert()
        {
            try
            {
                Console.WriteLine("\n[계좌 저장]\n");

                string name = WbLib.InputString("이름 입력");
                int balance = WbLib.InputInteger("입금액 입력");

                int number = acc_db.Account_Insert(name, balance);
                Console.WriteLine("계좌 저장 성공");

                acc_db.AccountIO_Insert(number, balance, 0, balance);
                Console.WriteLine("거래 내역 저장 성공");
            }
            catch (Exception ex)
            {
                Console.WriteLine("[계좌 개설] " + ex.Message);
            }
        }
        public void AccountPrintAll()
        {
            List<Account> accounts = acc_db.SelectAllAccount();
            foreach (Account account in accounts)
            {
                Console.WriteLine(account.ToString());
            }
        }
        public void AccountIOPrintAll()
        {
            List<AccountIO> accios = acc_db.SelectAllAccountIO();
            foreach (AccountIO account in accios)
            {
                Console.WriteLine(account.ToString()); 
            }
        }
        public void SelectNumber()
        {
            try
            {
                Console.WriteLine("\n[계좌 검색]\n");

                int number = WbLib.InputInteger("계좌번호 입력");

                Account account = acc_db.SelectAccountNumber(number);

                Console.WriteLine("\n[계좌 검색 성공]");
                Console.WriteLine(account.ToString());
            }
            catch (Exception ex)
            {
                Console.WriteLine("[계좌 검색 실패] " + ex.Message);
            }
        }
        public void AccountInput()
        {
            try
            {
                Console.WriteLine("\n[계좌 입금]\n");

                int number = WbLib.InputInteger("계좌번호 입력");
                int money = WbLib.InputInteger("입금액 입력");

                int bal = acc_db.UpdateAccount_Input(number, money);
                Console.WriteLine("입금 성공");

                acc_db.AccountIO_Insert(number, 0, money, bal);
                Console.WriteLine("거래 내역 저장 성공");
            }
            catch (Exception ex)
            {
                Console.WriteLine("[입금 실패] " + ex.Message);
            }
        }
        public void AccountOutput()
        {
            try
            {
                Console.WriteLine("\n[계좌 출금]\n");

                int number = WbLib.InputInteger("계좌번호 입력");
                int money = WbLib.InputInteger("출금액 입력");

                int bal = acc_db.UpdateAccount_Output(number, money);
                Console.WriteLine("출금 성공");

                acc_db.AccountIO_Insert(number, 0, money, bal);
                Console.WriteLine("거래 내역 저장 성공");
            }
            catch (Exception ex)
            {
                Console.WriteLine("[출금 실패] " + ex.Message);
            }
        }
        public void AccountDelete()
        {
            try
            {
                Console.WriteLine("\n[계좌 삭제]\n");

                int number = WbLib.InputInteger("계좌번호 입력");

                acc_db.DeleteAccount(number);
                Console.WriteLine("계좌 삭제 성공");

                acc_db.DeleteAccountIO(number);
                Console.WriteLine("거래 내역 삭제 성공");
            }
            catch (Exception ex)
            {
                Console.WriteLine("[삭제 실패] " + ex.Message);
            }
        }
        #endregion

        #region 4. 시작과 종료 메서드
        public void Init()
        {
            try
            {
                acc_db.InitData();
            }
            catch (Exception ex)
            {
                Console.WriteLine("파일 로드 실패(최초 실행)..........");
                Console.WriteLine(ex.Message);
                
                acc_db.InitFirstData();
            }
            WbLib.Pause();
        }
        public void Exit()
        {
            acc_db.Account_WriteXML();
            acc_db.AccountIO_WriteXML();
            acc_db.Dataset_WriteXML();
        }
        #endregion
    }
}
