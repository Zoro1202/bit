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
    public partial class Form2_Color: Form
    {
        Button btn = null;
        public Form2_Color()
        {
            this.Text = "KnownColor";
            this.IsMdiContainer = true;

            Array arr = System.Enum.GetValues(typeof(KnownColor));
            Form2_Color_sub[] frm = new Form2_Color_sub[arr.Length];

            for (int i = 0; i < arr.Length; i++)
            {
                frm[i] = new Form2_Color_sub(arr.GetValue(i).ToString());
                frm[i].TextLabel = arr.GetValue(i).ToString();
                frm[i].BackColor = Color.FromName(arr.GetValue(i).ToString());
                frm[i].SetBounds(0, 0, 200, 50);
                frm[i].MdiParent = this;
                frm[i].Show();
            }
            btn = new Button();
            btn.Text = "정렬하기";
            btn.Click += new EventHandler(this.btn_Click);
            btn.SetBounds(0, 0, 100, 50);
            this.Controls.Add(btn);
        }
        public void btn_Click(object Sender, EventArgs e)
        {
            this.LayoutMdi(MdiLayout.TileVertical);
        }

    }
}
