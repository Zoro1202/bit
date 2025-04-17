using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace _0417_XML_Practice
{
    class AccountControl
    {
        List<Account> accounts = new List<Account>();

        #region 0. 싱글톤 패턴
        public static AccountControl Singleton { get; } = null;
        static AccountControl() { Singleton = new AccountControl(); }
        private AccountControl()
        {
        }
        #endregion
        public void InsertFiveAccounts() // 
        {
            Account account = new Account(100, "홍길동", 10000);
            accounts.Add(account);
            account = new Account(101, "홍길동분신1", 20000);
            accounts.Add(account);
            account = new Account(102, "홍길동분신2", 30000);
            accounts.Add(account);
            account = new Account(103, "홍길동분신3", 40000);
            accounts.Add(account);
            account = new Account(104, "홍길동분신4", 50000);
            accounts.Add(account);
            Console.WriteLine("임의의 5개 Account 저장...");
        }
        public void AccountPrintAll() //
        {
            foreach (Account account in accounts)
            {
                Console.WriteLine(account.ToString());
            }
        }
        #region Accounts to XML
        public void XMLWriter()
        {
            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;
            XmlWriter writer = XmlWriter.Create("Accounts.xml", settings);

            writer.WriteComment("XMLWriter 개체로 요소 쓰기기");
            writer.WriteStartElement("Accounts");

            foreach (Account acc in accounts)
            {
                writer.WriteStartElement("Account");
                writer.WriteStartElement("ID");
                writer.WriteValue(acc.Id);
                writer.WriteEndElement();

                writer.WriteStartElement("Name");
                writer.WriteName(acc.Name);
                writer.WriteEndElement();

                writer.WriteStartElement("Balance");
                writer.WriteValue(acc.Balance);
                writer.WriteEndElement();

                writer.WriteElementString("Date", acc.Date.ToString());
                writer.WriteEndElement();
            }
            writer.WriteEndElement();
            writer.Close();
        }

        #endregion

        #region XML to Console
        public void XMLReadToConsole()
        {
            Console.WriteLine("-------XML--------");
            XmlReaderSettings settings = new XmlReaderSettings();
            settings.IgnoreComments = true;
            XmlReader reader = XmlReader.Create("Accounts.xml", settings);
            WriteConsole(reader);
            reader.Close();
        }
        private void WriteConsole(XmlReader reader)
        {
            XmlWriter xwriter = XmlWriter.Create(Console.Out);
            xwriter.WriteNode(reader, false);
            xwriter.Close();
            Console.WriteLine();
        }

        #endregion

        #region XML to Accounts

        public List<Account> XMLReader()
        {
            List<Account> list = new List<Account>();
            XmlReader reader = XmlReader.Create("Accounts.xml");
            while (reader.Read())
            {
                if(reader.IsStartElement("Account"))
                {
                    reader.MoveToContent();
                    int id = int.Parse(reader.Value);

                }
            }
            return list;
        }

        #endregion

        #region 4. 시작과 종료 메서드
        public void Init()
        {
            accounts = XMLReader();
            //WbLib.Pause();
        }
        public void Exit()
        {
            //acc_db.Account_WriteXML();
        }
        #endregion
    }
}
