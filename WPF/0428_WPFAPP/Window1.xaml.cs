using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace _0428_WPFAPP
{
    /// <summary>
    /// Window1.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class Window1 : Window
    {
        Polyline polyline = new Polyline();
        public Window1()
        {
            InitializeComponent();
            canvas1.Children.Add(polyline);
            Canvas.SetZIndex(polyline, 99);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            double x = Canvas.GetLeft(rect);
            double y = Canvas.GetTop(rect);
            if (sender == up_btn)
            {
                Canvas.SetTop(rect, y -= 10);
            }
            else if (sender == down_btn)
            {
                Canvas.SetTop(rect, y += 10);
            }
            else if (sender == left_btn)
            {
                Canvas.SetLeft(rect, x -= 10);
            }
            else if (sender == right_btn)
            {
                Canvas.SetLeft(rect, x += 10);
            }    
        }

        static int z_idx = 98;
        private void canvas1_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Rectangle r = new Rectangle();
            polyline.Stroke = Brushes.Red;
            r.StrokeThickness = 2;
            r.Width = 50;
            r.Height = 50;
            r.Fill = Brushes.Aqua;
            r.Stroke = Brushes.Black;
            
            polyline.Points.Add(e.GetPosition(canvas1));
            Canvas.SetLeft(r, e.GetPosition(canvas1).X-r.Width/2);
            Canvas.SetTop(r, e.GetPosition(canvas1).Y);

            Canvas.SetZIndex(r, z_idx--);

            canvas1.Children.Add(r);
        }
    }
}
