using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics.Eventing.Reader;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0423_키보드로움직이는타원
{
    internal class ShapeControl
    {

        MyDB db = new MyDB();
        private List<Shape> shapes = new List<Shape>();
        private Shape _shape = null;
        public Shape _Shape { get { return _shape; } }
        public List<Shape> Shapes { get { return shapes; } }
        #region 0. 싱글톤 패턴
        public static ShapeControl Instance { get; } = null;
        static ShapeControl() { Instance = new ShapeControl(); }
        private ShapeControl()
        {
            Init();
        }
        #endregion
        #region 도형 생성 & 삭제
        public void Create_Shape(Point point, Color color, int idx, int size)
        {
            if (_shape != null)
                throw new Exception("이미 도형이 생성되어 있습니다.");
            Shape temp = new Shape(point, color, idx, size);
            if (temp == null) throw new Exception("도형 생성에 실패했습니다.");
            _shape = temp;
        }
        public void Delete_Shape()
        {
            if(_shape == null) throw new Exception("생성된 도형이 없습니다.");
            _shape = null; // 가비지로 만들어버리기
        }
        #endregion
        #region 도형 색상 변경
        public void SetColor_Shape(Color color, int idx)
        {
            if (_shape == null) throw new Exception("도형이 생성되지 않았습니다.");
            _shape.Shape_color = color;
            _shape.Shape_color_index = idx;
        }
        #endregion
        #region 도형 위치 변경
        public void SetPoint_Shape(MainForm form, int x, int y)
        {
            int xx = _shape.Shape_point.X;
            int yy = _shape.Shape_point.Y;
            Size size = form.ClientSize;
            if (xx + x < 0 || xx + x > size.Width - _shape.Shape_size)
                return;
            else if (yy + y < 0 || yy + y > size.Height - _shape.Shape_size)
                return;
            else
                _shape.Shape_point = new Point(xx + x, yy + y);
            //이때 도형 정보를 리스트에 저장
            shapes.Add(new Shape(_shape.Shape_point, _shape.Shape_color, _shape.Shape_color_index, _shape.Shape_size));
            //DB에 저장하려면? list_id로 저장

        }
        #endregion

        public void Insert_Shapes()
        {
            //DB에 도형 정보 저장
            
        }
        //
        #region Init, Exit
        public void Init()
        {
            db.Connect();
        }

        public void Exit()
        {
            db.Close();
        }
        #endregion
    }
}
