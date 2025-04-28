using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
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

namespace _0428_라이프계산기
{
    /// <summary>
    /// window2.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class window2 : Window
    {
        public int life = 0;
        public window2()
        {
            InitializeComponent();
            text1.Focus();
        }
        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            
            DialogResult = false;
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            try 
            {
                life = int.Parse(text1.Text);
            }
            catch 
            { 
                MessageBox.Show("숫자만 입력하세여!", "ERROR", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Escape)
            {
                Button_Click_1(sender, e);
            }
            else if (e.Key == Key.Return)
            {
                Button_Click(sender, e);
            }
        }
    }
}
