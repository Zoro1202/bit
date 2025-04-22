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
    public partial class Form2_Color_sub: Form
    {
        string strText = null;
        public Form2_Color_sub(string str)
        {
            this.Text = str;
            SetStyle(ControlStyles.SupportsTransparentBackColor, true);
        }

        public string TextLabel
        {
            set
            {
                this.strText = value;
            }
        }
        protected override void OnPaint(PaintEventArgs pea)
        {
            Graphics grfx = pea.Graphics;
            SolidBrush br = new SolidBrush(Color.Black);
            grfx.DrawString(this.strText, this.Font, br, 10, 7);
        }
    }
}
