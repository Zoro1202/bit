using System;
using System.Runtime.Remoting.Contexts;
using System.Windows.Forms;

namespace _0424_chat_client
{
    public partial class MainForm: Form
    {
        public MainForm()
        {
            InitializeComponent();
            MemberControl.Instance._MainForm = this;
        }

        public void MainForm_Load(object sender, EventArgs e)
        {
            if (this.InvokeRequired)
                this.Invoke(new MethodInvoker( delegate () {this.button1_Click(sender, e); }));
            else
                button1_Click(sender, e);
            
        }

        private void LoginForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            MemberControl.Instance.Exit();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            dataGridView1.DataSource = MemberControl.Instance.GetMemberTable();
            if(MemberControl.Instance.client == null)
                MemberControl.Instance.Init();
        }
    }
}
