using System;
using System.Drawing;
using System.Windows.Forms;

namespace _0422_윈폼마우스이벤트
{
    public partial class Form1: Form
    {
        private Bitmap m_OriginalBmp;
        private bool m_breadBmp = false;
        private Rectangle m_region;
        private Bitmap m_SmallBmp;
        private bool m_bMouseDown = false;
        private int m_Ratio;
        public Form1()
        {
            InitializeComponent();
            this.m_Ratio = 10;
            m_OriginalPannel.Paint += m_OriginalPannel_Paint;
            m_SmallPannel.Paint += m_SmallPannel_Paint;
        }
        private void menuItem_FileOpen_Click(object sender, EventArgs e)
        {
            OpenFileDialog fd = new OpenFileDialog();
            fd.InitialDirectory = "C:\\";
            fd.Filter = "Image Files | *.JPG;*.GIF;*.PNG;*.BMP;*.*";
            if(fd.ShowDialog() == DialogResult.OK)
            {
                this.m_OriginalBmp = new Bitmap(fd.FileName);
                this.m_breadBmp = true;
                float ratio = (float)(1.0 + this.m_Ratio * .25f);
                m_region = new Rectangle(0, 0, (int)(m_SmallPannel.Width / ratio), (int)(m_SmallPannel.Height / ratio));
                this.m_OriginalPannel.Size = new System.Drawing.Size(m_OriginalBmp.Width, m_OriginalBmp.Height);
                this.m_OriginalPannel.Invalidate();
            }
        }
        private void m_OriginalPannel_Paint(object sender, PaintEventArgs e)
        {
            if (this.m_breadBmp)
            {
                using (Graphics g = e.Graphics)
                {
                    g.FillRectangle(Brushes.White, this.m_OriginalPannel.ClientRectangle);
                    Rectangle rect = new Rectangle(0,0,(int)(this.m_OriginalBmp.Width), (int)(this.m_OriginalBmp.Height));
                    g.DrawImage(this.m_OriginalBmp, rect);
                    using (Pen pen = new Pen(Brushes.Gold, 3))
                    {
                        pen.DashStyle = System.Drawing.Drawing2D.DashStyle.Dash;
                        g.DrawRectangle(pen, m_region);
                    }
                }
            }
        }
        private void m_SmallPannel_Paint(object sender, PaintEventArgs e)
        {
            if (this.m_breadBmp)
            {
                using (Graphics g = e.Graphics)
                {
                    g.FillRectangle(Brushes.White, this.m_SmallPannel.ClientRectangle);
                    g.DrawImage(this.m_SmallBmp, 0, 0);
                }
            }
        }
        private void m_OriginalPannel_MouseMove(object sender, MouseEventArgs e)
        {
            if (this.m_bMouseDown)
            {
                m_region.X = e.X;
                m_region.Y = e.Y;

                this.m_SmallBmp?.Dispose();

                this.m_SmallBmp = new Bitmap(this.m_SmallPannel.Width, this.m_SmallPannel.Height);
                using(Graphics gi = Graphics.FromImage(this.m_SmallBmp))
                {
                    gi.DrawImage(this.m_OriginalBmp, this.m_SmallPannel.ClientRectangle,
                        this.m_region, GraphicsUnit.Pixel);
                }
                this.m_OriginalPannel.Invalidate();
                this.m_SmallPannel.Invalidate();
            }
        }
        private void m_OriginalPannel_MouseDown(object sender, MouseEventArgs e)
        {
            this.m_bMouseDown = true;
        }
        private void m_OriginalPannel_MouseUp(object sender, MouseEventArgs e)
        {
            this.m_bMouseDown = false;
        }
        private void btn_Minus_Click(object sender, EventArgs e)
        {
            if (this.m_Ratio > -3)
            {
                this.m_Ratio--;
                this.ResizeSmallImage();
            }
        }
        private void btn_Plus_Click(object sender, EventArgs e)
        {
            if (this.m_Ratio < 3)
            {
                this.m_Ratio++;
                this.ResizeSmallImage();
            }
        }
        private void ResizeSmallImage()
        {
            float ratio = (float)(1.0 + this.m_Ratio * .25f);
            int w = (int)(this.m_SmallPannel.Width * ratio);
            int h = (int)(this.m_SmallPannel.Height * ratio);

            Rectangle rect = new Rectangle(0, 0, w, h);

            Bitmap tempBit = new Bitmap(w, h);

            using (Graphics g = Graphics.FromImage(tempBit))
            {
                g.DrawImage(this.m_SmallBmp, rect);

                this.m_SmallBmp.Dispose();
                this.m_SmallBmp = new Bitmap(w, h);
                this.m_SmallBmp = tempBit.Clone(rect, tempBit.PixelFormat);
            }
            tempBit.Dispose();
            this.m_SmallPannel.Invalidate();
        }
    }
}
