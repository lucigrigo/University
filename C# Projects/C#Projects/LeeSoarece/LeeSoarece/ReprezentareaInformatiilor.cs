using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LeeSoarece
{
    public partial class ReprezentareaInformatiilor : Form
    {
        int n, m;
        int[,] A = new int[100, 100];
        public ReprezentareaInformatiilor()
        {
            InitializeComponent();

        }

        private void ReprezentareaInformatiilor_Load(object sender, EventArgs e)
        {
            Incarcare();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            n = Convert.ToInt32(textBox1.Text);
            m = Convert.ToInt32(textBox2.Text);
            for(int k=0;k<n;k++)
            {
                for(int j=0;j<m;j++)
                {
                    A[k,j]=richTextBox1.Text.
                }
            }
        }

        private void Incarcare()
        {

        }
    }
}
