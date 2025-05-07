using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using _0507_Client.ServiceReference1;

namespace _0507_Client
{
    public partial class Form1: Form
    {
        BookClient client = new BookClient();
        public Form1()
        {
            InitializeComponent();
            ListUpdate();
        }

        public void ListUpdate()
        {
            Dictionary<string, string> bookList = client.GetBookList();

            listBox1.DataSource = bookList.ToList();
            listBox1.DisplayMember = "Value";


            //listBox1.Items.Clear();
        }

        //이미지 불러오기
        private void button1_Click(object sender, EventArgs e)
        {
            Stream readStream;

            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "그림파일 (*.bmp;*.jpg;*.gif;*.jpeg;*.png;*.tiff)|*.bmp;*.jpg;*.gif;*.jpeg;*.png;*.tiff)";
            dlg.RestoreDirectory = true;    // 현재 디렉토리를 저장해놓는다.
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                if ((readStream = dlg.OpenFile()) != null)
                {
                    byte[] bytePic;
                    BinaryReader picReader = new BinaryReader(readStream);
                    bytePic = picReader.ReadBytes(Convert.ToInt32(readStream.Length));

                    pictureBox1.Image = Image.FromStream(new MemoryStream(bytePic));

                    readStream.Close();
                }
            }
        }
        //저장
        private void button2_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image != null)
            {
                using (MemoryStream ms = new MemoryStream())
                {
                    pictureBox1.Image.Save(ms, pictureBox1.Image.RawFormat);
                    byte[] imageBytes = ms.ToArray();
                    client.AddBook(textBox1.Text, textBox2.Text, int.Parse(textBox3.Text), imageBytes);
                }
            }
            else
            {
                MessageBox.Show("이미지를 선택하세요.");
            }
            ListUpdate();
        }
        //검색
        private void button3_Click(object sender, EventArgs e)
        {
            int price = -1;
            byte[] image;
            client.GetBook1(textBox1.Text, textBox2.Text, out price, out image);
            if (price != -1)
            {
                textBox3.Text = price.ToString();
                pictureBox1.Image = Image.FromStream(new MemoryStream(image));
            }
            else
            {
                MessageBox.Show("책을 찾을 수 없습니다.");
            }
        }
        //수정
        private void button4_Click(object sender, EventArgs e)
        {
            Stream readStream;

            OpenFileDialog dlg = new OpenFileDialog();
            dlg.Filter = "그림파일 (*.bmp;*.jpg;*.gif;*.jpeg;*.png;*.tiff)|*.bmp;*.jpg;*.gif;*.jpeg;*.png;*.tiff)";
            dlg.RestoreDirectory = true;    // 현재 디렉토리를 저장해놓는다.
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                if ((readStream = dlg.OpenFile()) != null)
                {
                    byte[] bytePic;
                    BinaryReader picReader = new BinaryReader(readStream);
                    bytePic = picReader.ReadBytes(Convert.ToInt32(readStream.Length));
                    FileInfo fi = new FileInfo(dlg.FileName);

                    client.UpdateBook(textBox1.Text, textBox2.Text, int.Parse(textBox3.Text), bytePic);
                    
                    readStream.Close();
                }
            }
            button3_Click(sender, e);
            ListUpdate();
        }
        //삭제
        private void button5_Click(object sender, EventArgs e)
        {
            client.DeleteBook(textBox1.Text, textBox2.Text);
            textBox1.Text = "";
            textBox2.Text = "";
            textBox3.Text = "";
            pictureBox1.Image = null;
            ListUpdate();
        }
    }
}
