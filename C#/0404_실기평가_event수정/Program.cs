namespace _0404_실기평가
{
    internal class Program
    {
        static void Main(string[] args)
        {
            App app = App.Instance;
            app.Init();
            app.Run();
            app.Exit();
        }
    }
}