using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _0422_윈폼키보드이벤트
{
    public partial class Form1: Form
    {
        private string strdata = "";
        public Form1()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            using (Graphics g = e.Graphics)
            {
                g.DrawString(strdata,new Font("궁서체", 20, FontStyle.Bold), Brushes.Black, 20, 30);
            }
        }

        protected override void OnKeyDown(KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Back)
            {
                if (strdata.Length > 0)
                {
                    strdata = strdata.Remove(strdata.Length - 1);
                }
                Invalidate();
            }
            else if (e.KeyCode == Keys.Enter)
            {
                strdata += "\r\n";
                Invalidate();
            }
            else if (e.KeyCode == Keys.Space)
            {
                strdata += " ";
                Invalidate();
            }
            else if (e.KeyCode >= Keys.D0 && e.KeyCode <= Keys.D9)
            {
                strdata += (e.KeyValue - 48);
                Invalidate();
            }
            else if (e.KeyCode >= Keys.NumPad0 && e.KeyCode <= Keys.NumPad9)
            {
                strdata += (e.KeyValue - 96);
                Invalidate();
            }
            else if (e.KeyCode == Keys.F10 && e.Control)
            {
                MessageBox.Show("프로그램을 종료합니다.");
                this.Close();
            }
            else
            {
                strdata += e.KeyCode;
                Invalidate();
            }
        }
    }
}
