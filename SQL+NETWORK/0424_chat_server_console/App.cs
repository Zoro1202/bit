//app.cs
namespace _0424_chat_server_console
{
    internal class App
    {
        #region 0. 싱글톤 패턴
        public static App Singleton { get; } = null;
        static App() { Singleton = new App(); }
        private App() { }
        #endregion

        public void Init()
        {
            MemberControl.Singleton.Init();
            ChatControl.Singleton.Init();
            WbLib.Logo();
        }

        public void Exit()
        {
            MemberControl.Singleton.Exit();
            ChatControl.Singleton.Exit();
            WbLib.Ending();
        }
    }
}
