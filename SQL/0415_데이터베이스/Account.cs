﻿using Microsoft.SqlServer.Server;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0415_데이터베이스
{
    class Account
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public int Balance { get; set; }
        public DateTime Date { get; set; }
        public Account() { }
        public Account(int id, string name, int balance, DateTime date)
        {
            Id = id;
            Name = name;
            Balance = balance;
            Date = date;
        }
        public Account(int id, string name, int balance)
        {
            Id = id;
            Name = name;
            Balance = balance;
            Date = DateTime.Now;
        }

        public override string ToString()
        {
            return string.Format($"ID : {Id}\tNAME : {Name}\tBALANCE : {Balance}\tDATE : {Date}");
        }
    }
}
