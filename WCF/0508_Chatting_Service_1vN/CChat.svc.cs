using System;
using System.Collections.Generic;
using System.ServiceModel;

namespace _0508_Chatting_Service_1vN
{
    // 참고: "리팩터링" 메뉴에서 "이름 바꾸기" 명령을 사용하여 코드, svc 및 config 파일에서 클래스 이름 "Service1"을 변경할 수 있습니다.
    // 참고: 이 서비스를 테스트하기 위해 WCF 테스트 클라이언트를 시작하려면 솔루션 탐색기에서Service1.svc나 Service1.svc.cs를 선택하고 디버깅을 시작하십시오.
    //델리게이트 선언
    public delegate void Chat(string type, string nickname, string msg, DateTime date);
    public class CChat : IChat
	{
        //동기화 작업을 위해서 가상의 객체 생성
        private static Object syncObj = new Object();
        //채팅방에 있는 유저 이름 목록
        private static List<string> Chatter = new List<string>();
        //델리게이트 =========================================================
        // 개인용 델리게이트
        private Chat MyChat;
        //전체에게 보낼 정보를 담고 있는 델리게이트
        private static Chat List = null;
        //콜백(클라이언트에게)
        IChatCallback callback = null;

        public bool Join(string nickname, DateTime date)
        {
            MyChat = new Chat(UserHandler);
            lock(syncObj)
            {
                if(!Chatter.Contains(nickname))
                {
                    callback = OperationContext.Current.GetCallbackChannel<IChatCallback>();

                    BroadcastMessage("UserEnter", nickname, "", date);

                    List += MyChat;

                    return true;
                }
                return false;
            }
        }

        public void Say(string nickname, string msg, DateTime date)
        {
            BroadcastMessage("Receive", nickname, msg, date);
        }

        public void Leave(string nickname, DateTime date)
        {
            //메시지 수신에서 제외
            List -= MyChat;

            //모든 사람에게 전송
            string msg = string.Format(nickname + "이가 나갔습니다");
            BroadcastMessage("UserLeave", nickname, msg, date);

        }
        private void BroadcastMessage(string msgType, string nickname, string msg, DateTime date)
        {
            if (List != null)
            {
                //현재 이벤트들을 전달한다.
                foreach (Chat handler in List.GetInvocationList())
                {
                    handler.BeginInvoke(msgType, nickname, msg, date, new AsyncCallback(EndAsync), null);
                }
            }
        }
        private void UserHandler(string msgType, string nickname, string msg, DateTime date)
        {
            try
            {
                //클라이언트에게 보내기
                switch (msgType)
                {
                    case "Receive":
                        callback.Receive(nickname, msg, date);
                        break;
                    case "UserEnter":
                        callback.UserEnter(nickname, date);
                        break;
                    case "UserLeave":
                        callback.UserLeave(nickname, date);
                        break;
                }
            }
            catch//에러가 발생했을 경우
            {
                Leave(nickname, date);
            }
        }
        private void EndAsync(IAsyncResult ar)
        {
            Chat d = null;
            try
            {
                System.Runtime.Remoting.Messaging.AsyncResult asres = (System.Runtime.Remoting.Messaging.AsyncResult)ar;
                d = ((Chat)asres.AsyncDelegate);
                d.EndInvoke(ar);
            }
            catch
            {
                List -= d;
            }
        }

    }
}
