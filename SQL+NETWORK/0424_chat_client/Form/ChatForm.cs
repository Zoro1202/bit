using System;
using System.Windows.Forms;

namespace _0424_chat_client
{
    public partial class ChatForm: Form
    {
        private MemberControl memberControl = MemberControl.Instance;
        private ChatControl chatControl = ChatControl.Instance;
        public string ChatID { get; set; }
        #region 컨트롤 바인딩
        public string SendText
        { 
            get { return textBox2.Text; }
            set 
            {
                if (textBox2.InvokeRequired)
                    textBox2.Invoke(new MethodInvoker(delegate () { textBox2.Text = value; }));
                else textBox2.Text = value;
            }
        } // textBox2
        #endregion

        public ChatForm()
        {
            InitializeComponent();
            memberControl._ChatForm = this;
            chatControl._ChatForm = this;
        }

        #region 로그아웃
        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        private void ChatForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            memberControl.Logout(ChatID);
            chatControl.Exit();
        }
        public void Logout_Result(bool isvalid, string id)
        {
            if (isvalid)
            {
                MessageBox.Show("로그아웃 성공!");
            }
            else
            {
                MessageBox.Show("로그아웃 실패...");
            }
        }
        public void Recv_Message(string id, string msg, DateTime date)
        {
            this.Invoke(new MethodInvoker(delegate () { this.TextAppend(id, msg, date); }));
        }
        #endregion
        #region 메시지 전송
        private void button2_Click(object sender, EventArgs e)
        {
            chatControl.SendMessage(ChatID, SendText, DateTime.Now);
            //DB에 전송

            TextAppend(ChatID, SendText, DateTime.Now);
            SendText = "";
        }

        private void textBox2_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                button2_Click(sender, e);
            }
        }
        #endregion

        #region 텍스트박스 다중 라인 출력
        public void TextAppend(string id, string text, DateTime date)
        {
            string msg = string.Format($"[{id}] {text} ({date.ToShortTimeString()})");
            textBox1.AppendText(msg+"\r\n");
        }
        #endregion

        private void ChatForm_Load(object sender, EventArgs e)
        {
            string mip, cip, id, pw;
            int mport, cport;
            MyInfoFile.ReadMessage(out mip, out mport, out cip, out cport, out id, out pw);
            chatControl.Init(cip, cport);
        }
    }
}
