using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _0423_키보드로움직이는타원
{
    public partial class ColorForm: Form
    {
        public ColorForm()
        {
            InitializeComponent();
            InitCombo();
        }

        public string ColorName { get { return txt_color_colormodal.Text; } set { txt_color_colormodal.Text = value; } }
        public int ColorIdx { get { return cb_color_colormodal.SelectedIndex; } set { cb_color_colormodal.SelectedIndex = value; } }
        private void InitCombo()
        {
            Array arr = Enum.GetValues(typeof(KnownColor));
            foreach (KnownColor color in arr)
            {
                cb_color_colormodal.Items.Add(color);
            }
        }

        private void btn_colormodal_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            int idx = cb_color_colormodal.Items.Cast<KnownColor>().ToList().FindIndex(txt_color_colormodal=>ColorName == txt_color_colormodal.ToString());
            if (idx > -1) { cb_color_colormodal.SelectedIndex = idx; }
            Close();
        }

        private void cb_color_colormodal_SelectedIndexChanged(object sender, EventArgs e)
        {
            ColorName = cb_color_colormodal.SelectedItem.ToString();
        }
    }
}
