using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.ServiceModel;
using System.ServiceModel.Channels;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using _0508_Chatting_Client_1vN.ServiceReference1;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace _0508_Chatting_Client_1vN
{
    public partial class Form1: Form, IChatCallback
    {
        string name;
        private IChat chat;
        ChatClient client;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            InstanceContext site = new InstanceContext(this);
            chat = new _0508_Chatting_Client_1vN.ServiceReference1.ChatClient(site);
            button2.Enabled = false;
        }

        // Join
        private void button1_Click(object sender, EventArgs e)
        {
            if ((string)button1.Text == "로그인")
            {
                this.Connect();
                string msgtemp = string.Format("{0}님이 로그인하셨습니다.", name);
                button2.Enabled = true;
            }
            else this.DisConnect();
        }
        // Say
        private void button2_Click(object sender, EventArgs e)
        {
            string msg = textBox2.Text;

            //string temp = string.Format("({1})[{0}] {2}", name, DateTime.Now, msg);
            //listBox1.Items.Add(temp);

            chat.Say(name, msg, DateTime.Now);
            textBox2.Clear();

        }

        private void Connect()
        {
            try
            {
                name = textBox1.Text;

                //서버 접속
                bool data = chat.Join(name, DateTime.Now);

                button1.Text = "로그아웃";
                string login = string.Format("{0}님이 로그인하셨습니다.", name);
                listBox1.Items.Add(login);
            }
            catch (Exception ex)
            {
                MessageBox.Show("접속 오류 :{0}", ex.Message);
            }
        }

        private void DisConnect()
        {
            try
            {
                chat.Leave(name, DateTime.Now);
                button1.Text = "로그인";

                string logout = string.Format("{0}님이 로그아웃하셨습니다.", name);
                listBox1.Items.Add(logout);
                button2.Enabled = false;
            }
            catch (Exception ex)
            {
                MessageBox.Show("나가기 오류 :{0}", ex.Message);
            }
        }

        public void UserEnter(string nickname, DateTime date)
        {
            string msgtemp = string.Format("({1}){0}님이 로그인하셨습니다.", date, nickname);
            listBox1.Items.Add(msgtemp);
        }

        public void Receive(string nickname, string msg, DateTime date)
        {
            string msgtemp = string.Format("({1})[{0}] {2}", nickname, date, msg);
            listBox1.Items.Add(msgtemp);
        }

        public void UserLeave(string nickname, DateTime date)
        {
            string msgtemp = string.Format("({1}){0}님이 로그아웃하셨습니다.", nickname, date);
            listBox1.Items.Add(msgtemp);
        }
    }
}
