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
    public partial class Form4_Print: Form
    {
        public Form4_Print()
        {
            InitializeComponent();

            listBox1.Items.Add("사과");
            listBox1.Items.Add("포도");
            listBox1.Items.Add("참외");
        }

        private void listBox1_DrawItem(object sender, DrawItemEventArgs e)
        {
            Graphics g = e.Graphics;
            Brush brush = Brushes.Black;

            switch (e.Index)
            {
                case 0: brush = Brushes.Black; break;
                case 1: brush = Brushes.Violet; break;
                case 2: brush = Brushes.Red; break;
                case 3: brush = Brushes.Green; break;
                case 4: brush = Brushes.Coral; break;
                case 5: brush = Brushes.Magenta; break;
            }
            g.DrawString(listBox1.Items[e.Index].ToString(),
                e.Font, brush, e.Bounds, StringFormat.GenericDefault);

        }
    }
}
