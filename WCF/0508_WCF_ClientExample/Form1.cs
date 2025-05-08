using _0508_WCF_ClientExample.ServiceReference1;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.ServiceModel;
using System.ServiceModel.Dispatcher;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _0508_WCF_ClientExample
{
    public partial class Form1: Form, ICalCallback
    {
        private CalClient client;
        public Form1()
        {
            InitializeComponent();
            client = new CalClient(new InstanceContext(this));
        }

        public void Result([MessageParameter(Name = "result")] float result1)
        {
            MessageBox.Show(result1.ToString());
        }

        private void button1_Click(object sender, EventArgs e)
        {
            client.Add(1, 2);
        }
    }
}
