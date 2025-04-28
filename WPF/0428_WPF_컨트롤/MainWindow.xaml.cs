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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace _0428_WPF_컨트롤
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        public void Btn_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("버튼 클릭!");
        }
        public void Checkbox_Checked(object sender, RoutedEventArgs e)
        {
            string msg = "";
            if ((bool)check1.IsChecked)
            {
                msg += "Checked 1 ";
            }
            if ((bool)check2.IsChecked)
            {
                msg += "Checked 2 ";
            }
            if ((bool)check3.IsChecked)
            {
                msg += "Checked 3 ";
            }
            if(!(bool)check1.IsChecked && !(bool)check2.IsChecked && !(bool)check3.IsChecked)
            {
                msg += "MainWindow";
            }
            Title = msg;
        }
        public void Slider_ValueChanged(object sender, RoutedEventArgs e)
        {
            pro1.Value = slider1.Value;
        }
    }
}
