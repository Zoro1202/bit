using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _0423_키보드로움직이는타원
{
    /** <<타원>>
    * 좌표, 색상, 크기 
    * POINT
    * Color
    * int
    **/
    public class Shape
    {
        public Point Shape_point {  get; set; }
        public Color Shape_color { get; set; }
        public int Shape_color_index { get; set; }
        public int Shape_size { get; set; }
        public Shape(Point shape_point, Color shape_color, int shape_index, int shape_size)
        {
            Shape_point = shape_point;
            Shape_color = shape_color;
            Shape_color_index = shape_index;
            Shape_size = shape_size;
        }
        public override string ToString()
        {
            return string.Format($"{Shape_point}, {Shape_color}, {Shape_color_index}, {Shape_size}");
        }
    }
}
