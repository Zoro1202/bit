using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _0423_키보드로움직이는타원
{
    public partial class MainForm: Form
    {
        ReviewForm review_form = null;

        private ShapeControl shape_instance = ShapeControl.Instance;
        public MainForm()
        {
            InitializeComponent();
            InitCombo();
            TEST_InitShapeInfo();
            KeyPreview = true;
        }
        private void TEST_InitShapeInfo()
        {
            txt_xpos_shape.Text = "300";
            txt_ypos_shape.Text = "100";
            txt_size_shape.Text = "50";
        }
        private void InitCombo()
        {
            Array arr  = Enum.GetValues(typeof(KnownColor));
            foreach (KnownColor color in arr)
            {
                cb_color_shape.Items.Add(color);
            }
            cb_color_shape.SelectedIndex = 0;
        }

        private void btn_create_shape_Click(object sender, EventArgs e)
        {
            //데이터 획득
            int x = int.Parse(txt_xpos_shape.Text);
            int y = int.Parse(txt_ypos_shape.Text);
            Color color = Color.FromName(cb_color_shape.SelectedItem.ToString());
            int idx = cb_color_shape.SelectedIndex;
            int size = int.Parse(txt_size_shape.Text);
            //컨트롤에 요청
            try
            {
                shape_instance.Create_Shape(new Point(x, y), color, idx, size);
                Invalidate();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "error",MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);

            Graphics g = e.Graphics;
            Shape s = shape_instance._Shape;
            if (s != null)
            {
                g.FillEllipse(new SolidBrush(s.Shape_color), s.Shape_point.X, s.Shape_point.Y, s.Shape_size, s.Shape_size);
            }
        }

        private void btn_delete_shape_Click(object sender, EventArgs e)
        {
            try
            {
                shape_instance.Delete_Shape();
                Invalidate();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
        #region 마우스 이벤트, 컨텍스트 메뉴
        private void MainForm_MouseClick(object sender, MouseEventArgs e)
        {
            //마우스 우클릭 시 컨텍스트 메뉴를 띄우고 싶음
            if (e.Button == MouseButtons.Right)
            {
                int x = e.X + this.Left;
                int y = e.Y + this.Top;

                this.contextMenuStrip1.Show(x, y);
            }
        }
        private void colorCToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //컨텍스트 메뉴 클릭 시 모달을 띄우고 싶음
            ColorForm form = new ColorForm();
            form.ColorName = shape_instance._Shape?.Shape_color.Name ?? "-";
            form.ColorIdx = shape_instance._Shape?.Shape_color_index ?? -1;
            if(form.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    shape_instance.SetColor_Shape(Color.FromName(form.ColorName), form.ColorIdx);
                    //shape_instance._Shape.Shape_color = Color.FromName(form.ColorName);
                    //shape_instance._Shape.Shape_index = form.ColorIdx;

                    cb_color_shape.SelectedIndex = form.ColorIdx;
                    Invalidate();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }
        #endregion

        #region 키보드 이벤트
        protected override void OnKeyDown(KeyEventArgs e)
        {
            base.OnKeyDown(e);

            switch(e.KeyCode)
            {
                case Keys.Up:
                    shape_instance.SetPoint_Shape(this,0, -5);
                    break;
                case Keys.Left:
                    shape_instance.SetPoint_Shape(this, -5, 0);
                    break;
                case Keys.Down:
                    shape_instance.SetPoint_Shape(this, 0, +5);
                    break;
                case Keys.Right:
                    shape_instance.SetPoint_Shape(this, +5, 0);
                    break;
            }
            Invalidate();
        }
        #endregion
        //다시보기 - 모달리스
        private void btn_review_shape_Click(object sender, EventArgs e)
        {
            if (review_form != null)
                review_form.Focus();
            else
            {
                review_form = new ReviewForm(this);
                review_form.Size = this.Size;
                review_form.ShapeList = shape_instance.Shapes;
                review_form.Show();
            }
        }
        public void ReviewFormClose()
        {
            review_form = null;
        }

        private void btn_saveDB_main_Click(object sender, EventArgs e)
        {
            //컨트롤에서 DB로 LIST 저장하는 어쩌고 요청
            
        }

        private void btn_loadShape_main_Click(object sender, EventArgs e)
        {
            //컨트롤에서 DB에서 LIST 가져오는 어쩌고 요청

        }
    }
}
