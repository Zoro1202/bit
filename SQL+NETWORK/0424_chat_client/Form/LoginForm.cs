using System;
using System.Runtime.Remoting.Contexts;
using System.Windows.Forms;

namespace _0424_chat_client
{
    public partial class LoginForm: Form
    {
        private MemberControl memberControl = MemberControl.Instance;
        #region 컨트롤 바인딩 Login ID, PW 
        public string LoginID 
        { 
            get { return textBox1.Text; } 
            set 
            { 
                if (textBox1.InvokeRequired) 
                    textBox1.Invoke( new MethodInvoker(delegate () { textBox1.Text = value;}) );
                else textBox1.Text = value;
            } 
        }
        public string LoginPW 
        {
            get { return textBox2.Text; } 
            set {
                if (textBox2.InvokeRequired)
                    textBox2.Invoke(new MethodInvoker(delegate () { textBox2.Text = value; }));
                else textBox2.Text = value;
            } 
        }
        #endregion
        public LoginForm()
        {
            InitializeComponent();
            memberControl._LoginForm = this;
        }

        #region 로그인
        private void btn_main_login_Click(object sender, EventArgs e)
        {
            //컨트롤에 보내기 LoginID, PW -> return bool
            //if  else 폼을 띄우거나 말거나
            memberControl.Login(LoginID, LoginPW);
            
        }
        public void Login_Result(bool isvalid, string id, string name)
        {
            if (isvalid)
            {
                this.Invoke(new MethodInvoker( delegate (){ this.Hide(); }));
                ChatForm chatForm = new ChatForm();
                chatForm.ChatID = id; // 로그인 ID 정보 넘기긱긱기기ㅣ기ㅣ긱긱ㄱ
                chatForm.Name = name;
                chatForm.ShowDialog();
                this.Invoke(new MethodInvoker(delegate () { this.Show(); }));
            }
            else
            {
                MessageBox.Show("로그인 실패");
            }
        }
        #endregion

        #region 회원가입
        private void btn_main_register_Click(object sender, EventArgs e)
        {
            this.Hide();
            AddMemberForm addMemberForm = new AddMemberForm();
            if(addMemberForm.ShowDialog() == DialogResult.OK)
                MessageBox.Show("회원가입 성공");
            this.Show();
        }
        #endregion

        #region ini 파일 저장, 불러오기
        private void LoginForm_Load(object sender, EventArgs e)
        {
            try
            {
                string mip, cip, id, pw;
                int mport, cport;

                MyInfoFile.ReadMessage(out mip, out mport, out cip, out cport, out id, out pw);

                LoginID = id;
                LoginPW = pw;

                memberControl.Init(mip, mport);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                this.Close();
            }
        }


        private void LoginForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            MyInfoFile.WriteMessage(LoginID, LoginPW);
        }
        #endregion
    }
}
