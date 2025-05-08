using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _0507_PictureClient
{
    public partial class Form1: Form
    {
        // PictureService 객체를 하나 생성
        PictureService.Service1 pic = new PictureService.Service1();

        public Form1()
        {
            // 이미지 파일의 목록을 가져오는 메소드를 호출해서 문자열 배열에 저장한다.
            string[] strPicList = pic.GetPictureList();
            listBox1.DataSource = strPicList;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
            Close();
        }

        private void listBox1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            DialogResult = DialogResult.OK;
            Close();
        }
        public string SelectedPic
        {
            get
            {
                return listBox1.SelectedItem.ToString();
            }
        }
    }
}
