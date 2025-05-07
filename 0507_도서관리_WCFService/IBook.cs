using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace _0507_도서관리_WCFService
{
    [ServiceContract]
    interface IBook
    {
        [OperationContract]
        void AddBook(string title, string author, int price, byte[] image);
        [OperationContract]
        void UpdateBook(string title, string author, int price, byte[] image);
        [OperationContract]
        bool DeleteBook(string title, string author);
        [OperationContract]
        void GetBook1(string title, string author, out int price, out byte[] image);
        [OperationContract]
        Dictionary<string, string> GetBookList();
    }
}
