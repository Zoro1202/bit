using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace _0508_Chatting_Service_1v1
{
    [ServiceContract(SessionMode = SessionMode.Required, CallbackContract = typeof(IChatCallback))]
    public interface IChat
    {

        [OperationContract(IsOneWay = false, IsInitiating = true, IsTerminating = false)]
        bool Join(string nickname, DateTime date);

        [OperationContract(IsOneWay = true, IsInitiating = true, IsTerminating = false)]
        void Say(string nickname, string msg, DateTime date);

        [OperationContract(IsOneWay = true, IsInitiating = true, IsTerminating = false)]
        void Leave(string nickname, DateTime date);
    }

    public interface IChatCallback
    {
        [OperationContract(IsOneWay = true)]
        void UserEnter(string nickname, DateTime date);
        [OperationContract(IsOneWay = true)]
        void Receive(string nickname, string msg, DateTime date);
        [OperationContract(IsOneWay = true)]
        void UserLeave(string nickname, DateTime date);
    }
}
