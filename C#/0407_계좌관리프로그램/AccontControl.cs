//AccountControl.cs
using _0407_계좌관리프로그램;
using System;
using System.Linq;
using System.Net;
using WoosongBit41.Data;
using WoosongBit41.File;
using WoosongBit41.Lib;

namespace _0402_계좌관리프로그램
{
    
    internal class AccountControl
    {
        private WbArray accounts = new WbArray();   //계좌리스트 저장
        private WbArray accountios = new WbArray(); //거래 내역 저장
        public WbArray Accounts { get { return accounts; } }
        public int Account_Count { get { return accounts.Arr.Count; } }
        public WbArray Accountios { get { return accountios; } }
        public int AccountIO_Count { get { return accountios.Arr.Count; } }
        public event LogDel LogEvent = null; //계좌 생성 시 발생하는 이벤트
        private LogManager logmanager = null; //로그 매니저
        #region 0. 싱글톤 패턴
        public static AccountControl Singleton { get; } = null;
        static AccountControl() { Singleton = new AccountControl(); }
        private AccountControl() 
        {
            //Temp();
        }
        #endregion

        #region 1. 임시 데이터 입력
        private void Temp()
        {
            accounts.Add(new Account(1000, "홍길동", 1000, 0));
        }
        #endregion

        #region 2. 기능 메서드
        public void AccountInsert(int number, string name, int balance, int account_type)
        {
            try
            {
                //Account acc = (Account)accounts.Arr.Find(account => ((Account)account).Number == number);
                //if (acc != null)
                //{
                //    throw new Exception("계좌번호 중복입니다.");
                //}
                //bool b = accounts.Arr.Contains(new Account(number, "", 0, 0));
                bool b = accounts.Arr.Any(account => ((Account)account).Number == number);
                if (b == true)
                {
                    throw new Exception("계좌번호 중복입니다.");
                }

                Account account;
                //계좌 저장
                if (account_type == 0)
                {
                    account = new Account(number, name, balance, account_type);

                }
                else if (account_type == 1)
                {
                    account = new ContriAccount(number, name, balance, account_type);
                }
                else if (account_type == 2)
                {
                    account = new FaithAccount(number, name, balance, account_type);
                }
                else
                {
                    throw new Exception("잘못된 계좌유형입니다.");
                }
                accounts.Add(account);
                //거래 내역 저장
                AccountIO accountio = new AccountIO(number, balance, 0, balance, account_type);
                accountios.Add(accountio);
                Console.WriteLine("계좌 저장 성공");
                Console.WriteLine("거래 내역 저장 성공");
            }
            catch (Exception)
            {
                throw;
            }
            LogEvent(this, new LogArgs(ELOGTYPE.Insert_Account, "계좌 생성"));
        }
        public void AccountSort(int flag)
        {
            if (flag == 1)
            {
                accounts.SortByName();
                Console.WriteLine("이름으로 정렬 성공");
            }
            else if (flag == 2)
            {
                accounts.SortByBalance();
                Console.WriteLine("잔액 정렬 성공");
            }
            else
            {
                Console.WriteLine("잘못된 선택입니다.");
            }
        }
        public void AccountIOPrintAll()
        {
            Console.WriteLine("저장개수 : {0}개", accountios.Arr.Count);
            for (int i = 0; i < accountios.Arr.Count; i++)
            {
                AccountIO accountio = (AccountIO)accountios[i];
                accountio.Print();
            }
        }
        public void AccountPrintAll()
        {
            Console.WriteLine("저장개수 : {0}개", accounts.Arr.Count);
            for (int i = 0; i < accounts.Arr.Count; i++)
            {
                Account account = (Account)accounts[i];
                account.Print();
            }
            LogEvent(this, new LogArgs(ELOGTYPE.Print_Account, "계좌 전체 출력"));
        }
        public void SelectNumber(int number)
        {
            try
            {
                Account account = NumberToAccount(number);
                account.Print();
                Console.WriteLine("--------------------------------------------");
                AccountIOPrint(number);
            }
            catch (Exception ex)
            {
                Console.WriteLine("[계좌 검색 실패] " + ex.Message);
            }

            LogEvent(this, new LogArgs(ELOGTYPE.Select_Account, "계좌 검색"));
        }
        public void AccountInput(int number, int money)
        {
            try
            {
                Account account = NumberToAccount(number);
                account.Input_Money(money);

                AccountIO accountio = new AccountIO(number, money, 0, account.Balance, account.Type);
                accountios.Add(accountio);
            }
            catch (Exception)
            {
                throw;
            }

            LogEvent(this, new LogArgs(ELOGTYPE.Inptut_Account, "계좌 입금"));
        }
        public void AccountOutput(int number, int money)
        {
            try
            {
                Account account = NumberToAccount(number);
                account.Output_Money(money);

                AccountIO accountio = new AccountIO(number, 0, money, account.Balance, account.Type);
                accountios.Add(accountio);

            }
            catch (Exception)
            {
                throw;
            }
            LogEvent(this, new LogArgs(ELOGTYPE.Output_Account, "계좌 출금"));
        }
        public void AccountDelete(int number)
        {
            try
            {
                Account account = NumberToAccount(number);

                accounts.Arr.Remove(account);
                AccountIODeleteAll(number);
            }
            catch (Exception)
            {
                throw;
            }

            LogEvent(this, new LogArgs(ELOGTYPE.Delete_Account, "계좌 삭제"));
        }
        public List<Account> SelectAllName(string name)
        {
            List<Account> accs;
            try
            {
                accs = accounts.Arr.FindAll(account => ((Account)account).Name == name).Cast<Account>().ToList();
            }
            catch (Exception)
            {
                throw;
            }

            LogEvent(this, new LogArgs(ELOGTYPE.Delete_Account, "동일 이름 계좌 검색"));
            return accs;
        }
        #endregion

        #region 3. 내부에서 사용되는 메서드
        public int NumberToIdx(int number)
        {
            return accounts.Arr.FindIndex(account => ((Account)account).Number == number);
            for (int i = 0; i < accounts.Arr.Count; i++)
            {
                Account account = (Account)accounts[i];
                if (account.Number == number)
                    return i;
            }
            throw new Exception("없는 계좌번호 입니다.");
        }
        public Account NumberToAccount(int number)
        {
            Account ret = (Account)accounts.Arr.Find(account => ((Account)account).Number == number);
            if (ret == null)
            {
                throw new Exception("없는 계좌번호 입니다.");
            }
            else
            {
                return ret;
            }
        }
        public void AccountIOPrint(int number)
        {
            //List<AccountIO> temp = accountios.Arr.FindAll(x => ((AccountIO)x).Number == number);
            for (int i = 0; i < accountios.Arr.Count; i++)
            {
                AccountIO accountio = (AccountIO)accountios[i];
                if (accountio.Number == number)
                    accountio.Print();
            }
        }
        public void AccountIODeleteAll(int number)
        {
            for (int i = accountios.Arr.Count -1; i >= 0 ; i--)
            {
                AccountIO accountio = (AccountIO)accountios[i];
                if (accountio.Number == number)
                {
                    accountios.Remove(i);
                }
            }
        }
        #endregion

        #region 4. 시작과 종료 메서드
        public void Init()
        {
            try
            {
                logmanager = new LogManager(); // 생성자에서 만들지 못하는 이유 : AccountControl 객체가 생성되기 전에 LogManager 생성자에서 AccountControl 객체를 사용하기 때문
                WbFile.Read_Accounts(accounts);
                WbFile.Read_Accountios(accountios);
                Console.WriteLine("파일 로드 성공.................");
            }
            catch (Exception ex)
            {
                Console.WriteLine("파일 로드 실패(최초 실행)..........");
                Console.WriteLine(ex.Message);
            }
            WbLib.Pause();
        }
        public void Exit()
        {
            WbFile.Write_Accounts(accounts);
            WbFile.Write_Accountios(accountios);

            logmanager.Dispose(); // 소멸자 호출
        }
        #endregion
    }
}