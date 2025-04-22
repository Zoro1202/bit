using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Configuration;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _0422_FormReal
{
    public partial class Form1: Form
    {
        private TextBox my_textbox = new TextBox();
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            MessageBox.Show("Load!");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string str = textBox1.Text;
            label1.Text = str;
        }

        private void enter(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                string str = textBox1.Text;
                label1.Text = str;
            }
        }
    }
}
