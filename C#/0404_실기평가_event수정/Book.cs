using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace _0404_실기평가
{
    class Book : IComparable
    {
        private string title;
        private int price;
        private string author;
        public string Title
        {
            get { return title; }
        }
        public int Price
        {
            get { return price; }
        }
        public string Author
        {
            get { return author; }
        }
        public Book(string title, int price, string author)
        {
            this.title = title;
            this.price = price;
            this.author = author;
        }
        public void UpdatePrice(int newPrice)
        {
            if(newPrice < 0)
            {
                throw new ArgumentException("가격은 0보다 커야 합니다.");
            }
            else
            {
                this.price = newPrice;
            }
        }
        public int CompareTo(object? obj)
        {
            return this.title.CompareTo(((Book)obj).title);
        }
    }
}
