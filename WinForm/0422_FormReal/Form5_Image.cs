using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Permissions;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _0422_FormReal
{
    public partial class Form5_Image: Form
    {
        private Image image = null;
        public Form5_Image()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Image imagefile = Image.FromFile("ocean.jpg");
            Graphics g = Graphics.FromImage(imagefile);

            g.DrawString("이미지에 글쓰기", new Font("돋움", 20), Brushes.Pink, 10, 10);

            g.Dispose();

            imagefile.Save("ocean.gif", System.Drawing.Imaging.ImageFormat.Gif);
            imagefile.Save("ocean.bmp", System.Drawing.Imaging.ImageFormat.Bmp);
            imagefile.Save("ocean.png", System.Drawing.Imaging.ImageFormat.Png);

            this.image = Image.FromFile("ocean.gif");
            this.Invalidate(this.ClientRectangle);
        }
        private void Form5_Image_Paint(object sender, PaintEventArgs e)
        {
            Graphics grfx = e.Graphics;
            if (image != null)
                grfx.DrawImage(image, 200, 0);
        }
    }
}
