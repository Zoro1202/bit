//Account.cs
using System;
using System.Collections;
using System.Diagnostics.Contracts;
using WoosongBit41.Lib;

namespace WoosongBit41.Data
{
    class Account : IComparable //, IEquatable<Account>
    {
        public enum ACCOUNTTYPE
        {
            ACCOUNT = 0, // 일반계좌
            FAITH,   // 기부계좌
            CONTRI   // 기부계좌
        }
        #region 0. 인터페이스 구현
        // IComparable 인터페이스 구현
        public int CompareTo(object? obj)
        {
            if (obj == null)
                return 1;
            Account account = (Account)obj;
            return Number.CompareTo(account.Number);
        }
        //public override bool Equals(object? obj)
        //{
        //    if (obj == null)
        //        return false;
        //    return Equals(obj as Account); // object를 Account로 안전하게 캐스팅해서 비교
        //}
        //public bool Equals(Account? other)
        //{
        //    if (other == null)
        //        return false;
        //    return this.Number == other.Number;
        //}
        // override
        public override string ToString()
        {
            return this.Name;
        }
        public override int GetHashCode()
        {
            return Number.GetHashCode();
        }
        #endregion

        #region 1. 맴버필드, 프로퍼티(속성)
        public int Number       { get; protected set; }
        public string Name      { get; protected set; }
        public int Balance      { get; protected set; }
        public DateTime Ctime   { get; protected set; }
        public int Type { get; protected set; } //계좌유형
        #endregion

        #region 2. 생성자
        public Account(int _number, string _name, int _balance, int _type)
        {
            Number  = _number;
            Name    = _name;
            Balance = _balance;
            Type = _type;
            Ctime   = DateTime.Now;
        }

        public Account(int _number, string _name, int _balance, int _type, DateTime _time)
        {
            Number  = _number;
            Name    = _name;
            Balance = _balance;
            Type = _type;
            Ctime   = _time;
        }
        #endregion

        #region 3. 기능 메서드
         public virtual void Input_Money(int money)
         {
             if (money <= 0)
                 throw new Exception("잘못된 금액");

             Balance = Balance + money;
         }
        public void Output_Money(int money)
        {
            if (money <= 0)
                throw new Exception("잘못된 금액");

            if (money > Balance)
                throw new 
                    Exception(string.Format("잔액부족-잔액:{0}원,요청금액:{1}원", Balance, money));

            Balance = Balance - money;
        }
        public void Print()
        {
            Console.Write(Number + "\t");
            Console.Write(Name + "\t");
            Console.Write(Balance + "원\t");
            Console.Write(Type == 0 ? "일반 계좌\t" : Type == 1 ? "기부 계좌\t" : "신용 계좌\t");
            Console.Write(WbLib.Get_Date(Ctime) + "\t");
            Console.Write(WbLib.Get_Time(Ctime) + "\t");
            Console.WriteLine();
        }
        public void Println()
        {
            Console.WriteLine("[번호] " + Number);
            Console.WriteLine("[이름] " + Name);
            Console.WriteLine("[잔액] " + Balance + "원");
            Console.WriteLine("[계좌유형] " + (Type == 0 ? "일반 계좌" : Type == 1 ? "기부 계좌" : "신용 계좌"));
            Console.WriteLine("[날짜] " + WbLib.Get_Date(Ctime));
            Console.WriteLine("[시간] " + WbLib.Get_Time(Ctime));
        }

        #endregion
    }

}
