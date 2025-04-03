//WbFile.cs
using System;
using WoosongBit41.Lib;
using WoosongBit41.Data;
using System.IO;
using _0402_계좌관리프로그램;
using Microsoft.Win32;

namespace WoosongBit41.File
{
    internal static class WbFile
    {
        private const string ACCOUNTS_FILENAME = "accounts.txt";
        private const string ACCOUNTSCONTRI_FILENAME = "accounts_Contri.txt";
        private const string ACCOUNTSFAITH_FILENAME = "accounts_Faith.txt";
        private const string ACCOUNTIOS_FILENAME    = "accountios.txt";

        //text모드(데이터 기반)
        public static void Write_Accounts(WbArray accounts)
        {
            StreamWriter writer = new StreamWriter(ACCOUNTS_FILENAME);
            StreamWriter contri_writer = new StreamWriter(ACCOUNTSCONTRI_FILENAME);
            StreamWriter faith_writer = new StreamWriter(ACCOUNTSFAITH_FILENAME);

            int contri_count = 0;
            int faith_count = 0;
            int normal_count = 0;

            for (int i = 0; i < accounts.Arr.Count; i++)
            {
                Account account = (Account)accounts[i];
                if (account.Type == 0) {
                    string temp = string.Empty;
                    temp += account.Number + "@";
                    temp += account.Name + "@";
                    temp += account.Balance + "@";
                    temp += account.Type + "@";
                    temp += account.Ctime;
                    writer.WriteLine(temp);
                    normal_count++;
                } 
                else if (account.Type == 1)
                {
                    string temp = string.Empty;
                    temp += account.Number + "@";
                    temp += account.Name + "@";
                    temp += account.Balance + "@";
                    temp += account.Type + "@";
                    temp += ((ContriAccount)account).Contribution + "@";
                    temp += account.Ctime;
                    contri_writer.WriteLine(temp);
                    contri_count++;
                }
                else if (account.Type == 2)
                {
                    string temp = string.Empty;
                    temp += account.Number + "@";
                    temp += account.Name + "@";
                    temp += account.Balance + "@";
                    temp += account.Type + "@";
                    temp += account.Ctime;
                    faith_writer.WriteLine(temp);
                    faith_count++;
                }
            }
            writer.WriteLine(":END: "+normal_count);
            contri_writer.WriteLine(":END: " + contri_count);
            faith_writer.WriteLine(":END: " + faith_count);
            writer.Dispose();
            contri_writer.Dispose();
            faith_writer.Dispose();
        }
        public static void Write_Accountios(WbArray accountios)
        {
            StreamWriter writer = new StreamWriter(ACCOUNTIOS_FILENAME);
            writer.WriteLine(accountios.Arr.Count);
            for (int i = 0; i < accountios.Arr.Count; i++)
            {
                AccountIO accountio = (AccountIO)accountios[i];
                string temp = string.Empty;
                temp += accountio.Number    + "@";
                temp += accountio.Input     + "@";
                temp += accountio.Output    + "@";
                temp += accountio.Balance   + "@";
                temp += accountio.Type + "@";
                temp += accountio.CTime;
                writer.WriteLine(temp);
            }
            writer.Dispose();
        }
        public static void Read_Accounts(WbArray accounts)
        {
            StreamReader reader = new StreamReader(ACCOUNTS_FILENAME);
            StreamReader contri_reader = new StreamReader(ACCOUNTSCONTRI_FILENAME);
            StreamReader faith_reader = new StreamReader(ACCOUNTSFAITH_FILENAME);
            int i = 0;
            while (true)
            {
                string temp     = reader.ReadLine();  //번호@이름@잔액@날짜
                if (temp.StartsWith(":END:"))
                {
                    break;
                }
                string[] sp     = temp.Split('@');
                int number      = int.Parse(sp[0]);
                string name     = sp[1];
                int balance     = int.Parse(sp[2]);
                int type = 0;
                DateTime ctime = DateTime.Parse(sp[4]);
                accounts.Add(new Account(number, name, balance, type, ctime));
            }
            reader.Dispose();
            while (true)
            {
                string temp = contri_reader.ReadLine();  //번호@이름@잔액@날짜
                if (temp.StartsWith(":END:"))
                    break;
                string[] sp = temp.Split('@');
                int number = int.Parse(sp[0]);
                string name = sp[1];
                int balance = int.Parse(sp[2]);
                int type = 1;
                int contri = int.Parse(sp[4]);
                DateTime ctime = DateTime.Parse(sp[5]);
                accounts.Add(new ContriAccount(number, name, balance, type, contri, ctime));
            }
            contri_reader.Dispose();
            while (true)
            {
                string temp = faith_reader.ReadLine();  //번호@이름@잔액@날짜
                if (temp.StartsWith(":END:"))
                    break;
                string[] sp = temp.Split('@');
                int number = int.Parse(sp[0]);
                string name = sp[1];
                int balance = int.Parse(sp[2]);
                int type = 2;
                DateTime ctime = DateTime.Parse(sp[4]);
                accounts.Add(new FaithAccount(number, name, balance, type, ctime));
            }
            faith_reader.Dispose();
        }
        public static void Read_Accountios(WbArray accountios)
        {
            StreamReader reader = new StreamReader(ACCOUNTIOS_FILENAME);
            int size = int.Parse(reader.ReadLine());
            for (int i = 0; i < size; i++)
            {
                string temp = reader.ReadLine();  //번호@이름@잔액@날짜
                string[] sp = temp.Split('@');
                int number      = int.Parse(sp[0]);
                int input       = int.Parse(sp[1]);
                int output      = int.Parse(sp[2]);
                int balance     = int.Parse(sp[3]);
                int type = int.Parse(sp[4]);
                DateTime ctime  = DateTime.Parse(sp[5]);

                accountios.Add(new AccountIO(number, input, output, balance, type, ctime));
            }
            reader.Dispose();
        }
    }
}
