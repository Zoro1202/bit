using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _0422_FormReal
{
    public partial class Form3_Color: Form
    {

        public Form3_Color()
        {
            InitializeComponent();
            btn1.Click += new EventHandler(btn_Click);

            btn2.Click += new EventHandler(btn_Click);

        }
        protected override void OnPaint(PaintEventArgs pea)
        {
            Graphics grfx = pea.Graphics;
            SolidBrush br = new SolidBrush(this.ForeColor);
            Font font = new Font("돋음", 20);
            grfx.DrawString("글자색 변경", font, br, 10, 80);
        }

        protected void btn_Click(object sender, System.EventArgs e)
        {
            ColorDialog colorDlg = new ColorDialog();
            colorDlg.AllowFullOpen = false;
            colorDlg.ShowHelp = true;

            if ((Button)sender == btn1)  // 배경색 변경
            {
                colorDlg.Color = this.BackColor;
                if (colorDlg.ShowDialog() == DialogResult.OK)
                    this.BackColor = colorDlg.Color;
            }
            else if ((Button)sender == btn2) // 전경색 변경
            {
                colorDlg.Color = this.ForeColor;
                if (colorDlg.ShowDialog() == DialogResult.OK)
                    this.ForeColor = colorDlg.Color;
            }
        }

        private void btn3_Click(object sender, EventArgs e)
        {
            ColorDialog colorDlg = new ColorDialog();
            colorDlg.ShowHelp= true;

            if(colorDlg.ShowDialog()== DialogResult.OK)
            {
                using (Graphics g = pictureBox1.CreateGraphics())
                {
                    pictureBox1.BackColor = colorDlg.Color;
                    textBox1.Text = colorDlg.Color.Name;
                    textBox2.Text = string.Format("{0}", (uint)colorDlg.Color.ToArgb());
                    textBox3.Text = string.Format($"{colorDlg.Color.R}, {colorDlg.Color.G}, {colorDlg.Color.B}");
                }
            }
        }
    }
}
