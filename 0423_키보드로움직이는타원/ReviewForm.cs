using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _0423_키보드로움직이는타원
{
    public partial class ReviewForm: Form
    {
        public MainForm MainForm { get; set; } = null;
        public List<Shape> ShapeList { get; set; } = null;
        private Shape _shape;
        public ReviewForm(MainForm main_form)
        {
            InitializeComponent();
            MainForm = main_form;
        }

        #region 시작, 종료
        private void ReviewForm_Load(object sender, EventArgs e)
        {
            trackBar1.Maximum = ShapeList.Count - 1;
        }
        private void ReviewForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            MainForm.ReviewFormClose();
        }
        #endregion
        //시작 및 도형 출력
        private void btn_start_review_Click(object sender, EventArgs e)
        {
            for(int i = 0; i < ShapeList.Count; i ++)
            {
                _shape = ShapeList[i];
                trackBar1.Value = i;
                Invalidate();
                this.Update();
                Thread.Sleep(100);
            }
        }
        private void ReviewForm_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            if (_shape != null)
            {
                g.FillEllipse(new SolidBrush(_shape.Shape_color), _shape.Shape_point.X, _shape.Shape_point.Y, _shape.Shape_size, _shape.Shape_size);
            }
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            _shape = ShapeList[trackBar1.Value];
            Invalidate();
            this.Update();
        }
    }
}
