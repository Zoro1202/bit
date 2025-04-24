using System;
using System.Drawing;
using System.Windows.Forms;

namespace _0424_chat_client
{
    public partial class AddMemberForm: Form
    {
        #region 컨트롤 바인딩 Register ID, PW 
        public string RegisterID 
        {
            get { return textBox1.Text; } 
            set 
            {
                if (textBox1.InvokeRequired)
                    textBox1.Invoke(new MethodInvoker(delegate () { textBox1.Text = value; }));
                else textBox1.Text = value;
            } 
        }
        public string RegisterPW 
        {
            get { return textBox2.Text; }
            set 
            {
                if (textBox2.InvokeRequired)
                    textBox2.Invoke(new MethodInvoker(delegate () { textBox2.Text = value; }));
                else textBox2.Text = value;
            } 
        }
        public string RegisterName 
        {
            get { return textBox3.Text; } 
            set 
            {
                if (textBox3.InvokeRequired)
                    textBox3.Invoke(new MethodInvoker(delegate () { textBox3.Text = value; }));
                else textBox3.Text = value;
            } 
        }
        public Color RegisterColor
        {
            get { return Color.FromName(comboBox1.SelectedItem.ToString()); }
        }
        public DateTime RegisterDate
        {
            get { return dateTimePicker1.Value; }
        }
        #endregion
        public AddMemberForm()
        {
            InitializeComponent();
            InitCombo();
            MemberControl.Instance._AddMemberForm = this;
        }
        #region 콤보박스 초기화
        private void InitCombo()
        {
            Array arr = Enum.GetValues(typeof(KnownColor));
            foreach (KnownColor color in arr)
            {
                comboBox1.Items.Add(color);
            }
            comboBox1.SelectedIndex = 0;
        }
        #endregion

        #region 입력 정보 제공
        public void GetAddMemberData(out string id, out string pw, out string name, out Color color, out DateTime date)
        {
            id = textBox1.Text;
            pw = textBox2.Text;
            name = textBox3.Text;
            color = RegisterColor;
            date = RegisterDate;
        }
        #endregion

        #region 버튼
        private void button1_Click(object sender, EventArgs e)
        {
            if (RegisterID == string.Empty || RegisterPW == string.Empty || RegisterName == string.Empty)
            {
                MessageBox.Show("회원 정보를 입력하세요");
            }
            else
            {
                MemberControl.Instance.AddMember(RegisterID, RegisterPW, RegisterName, RegisterColor, RegisterDate);
            }
        }
        public void AddMember_Result(bool isvalid, string id, string name)
        {
            if(isvalid)
            {
                DialogResult = DialogResult.OK;
            }
                else
            {
                MessageBox.Show("회원가입 실패");
            }
        }
        #endregion
    }
}
