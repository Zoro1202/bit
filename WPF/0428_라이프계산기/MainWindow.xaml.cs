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

namespace _0428_라이프계산기
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            string[] str = label_cur.Content.ToString().Split(':');
            string life = str[1];
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            window2 wnd2 = new window2();
            wnd2.ShowDialog();
            MessageBox.Show("disp");
        }
    }
}
