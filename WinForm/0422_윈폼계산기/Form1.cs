using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics.Eventing.Reader;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _0422_윈폼계산기
{
    public partial class Form1 : Form
    {
        Button[] btn = new Button[16];
        Label lbl_display;
        int iResult;
        int option = 0;
        int iButtonSize = 50;
        public Form1()
        {
            InitializeComponent();
            int i = 0;
            this.Text = "계산기";
            lbl_display = new Label();
            lbl_display.Text = "0";
            lbl_display.BackColor = Color.Yellow;
            lbl_display.TextAlign = ContentAlignment.MiddleLeft;
            lbl_display.SetBounds(50, 10, 200, 20);
            this.Controls.Add(lbl_display);
            for (i = 0; i < 10; i++)
            {
                btn[i] = new Button();
                btn[i].Text = i.ToString();
                btn[i].SetBounds(iButtonSize + (i % 3 * iButtonSize), iButtonSize + (i / 3 * iButtonSize), iButtonSize, iButtonSize);
                this.Controls.Add(btn[i]);
            }

            string[] str = { "+", "-", "*", "/" };
            for (i = 0; i < 4; i++)
            {
                btn[i + 10] = new Button() { Text = str[i] };
                btn[i + 10].SetBounds(4 * iButtonSize, iButtonSize + (i % 3 * iButtonSize),
                    iButtonSize, iButtonSize);
                this.Controls.Add(btn[i + 10]);
            }
            btn[14] = new Button() { Text = "CLR" };
            btn[14].SetBounds(2 * iButtonSize, 4 * iButtonSize, iButtonSize, iButtonSize);
            this.Controls.Add(btn[14]);

            btn[15] = new Button() { Text = "ANS" };
            btn[15].SetBounds(3 * iButtonSize, 4 * iButtonSize, iButtonSize, iButtonSize);
            this.Controls.Add(btn[15]);

            for (i = 0; i < 16; i++)
            {
                btn[i].Click += new EventHandler(Calculator_Click);
            }
        }
        private void Calculator_Click(object sender, EventArgs e)
        {
            Button obj = (Button)sender;
            if (obj.Text == "+")
            {
                iResult = Int32.Parse(lbl_display.Text);
                option = 1;
                obj.ForeColor = Color.Red;
                lbl_display.Text = "";
            }
            else if (obj.Text == "-")
            {
                iResult = Int32.Parse(lbl_display.Text);
                option = 2;
                obj.ForeColor = Color.Red;
                lbl_display.Text = "";
            }
            else if (obj.Text == "*")
            {
                iResult = Int32.Parse(lbl_display.Text);
                option = 3;
                obj.ForeColor = Color.Red;
                lbl_display.Text = "";
            }
            else if (obj.Text == "/")
            {
                iResult = Int32.Parse(lbl_display.Text);
                option = 4;
                obj.ForeColor = Color.Red;
                lbl_display.Text = "";
            }
            else if (obj.Text == "CLR")
            {
                btn[9 + option].ForeColor = Color.Black;
                iResult = 0;
                lbl_display.Text = "";
            }
            else if (obj.Text == "ANS")
            {
                if (option == 1)
                {
                    iResult = iResult + Int32.Parse(lbl_display.Text);
                    btn[10].ForeColor = Color.Black;
                }
                else if (option == 2)
                {
                    iResult = iResult - Int32.Parse(lbl_display.Text);
                    btn[11].ForeColor = Color.Black;
                }
                else if (option == 3)
                {
                    iResult = iResult * Int32.Parse(lbl_display.Text);
                    btn[12].ForeColor = Color.Black;
                }
                else if (option == 4)
                {
                    iResult = iResult / Int32.Parse(lbl_display.Text);
                    btn[13].ForeColor = Color.Black;
                }
                this.lbl_display.Text = iResult.ToString();
            }
            else
            {
                this.lbl_display.Text += obj.Text;
            }
        }
        
    }
}
