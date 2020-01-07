using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace Reginele
{
    public partial class Form1 : Form
    {
        static int n;
        static int[] ST = new int[100];
        float l, L;
        Thread t;

        public Form1()
        {
            InitializeComponent();
        }

        bool Valid(int k)
        {
            for (int i = 1; i < k; i++)
            {
                if (ST[i] == ST[k] || Math.Abs(k - i) == Math.Abs(ST[k] - ST[i]))
                {
                    return false;
                }
            }
            return true;
        }

        void Back()
        {
            int k = 1;
            ST[k] = 0;
            while (k > 0)
            {
                if (ST[k] < n)
                {
                    ST[k]++;
                    if (ST[k] > 1)
                    {
                        DesenareRegina(k, ST[k] - 1, panel1.BackColor,10);
                    }
                    DesenareRegina(k, ST[k], Color.Blue,10);
                    if (Valid(k))
                    {
                        if (k == n)
                        {
                            //Afisare(k);
                            for (int i = 1; i <= n;i++)
                            {
                                DesenareRegina(i, ST[i], Color.Red,0);
                            }
                                System.Threading.Thread.Sleep(10000);
                                //Afisare(k);
                            for (int i = 1; i <= n; i++)
                            {
                                DesenareRegina(i, ST[i], Color.Blue,0);
                            }
                        }
                        else
                        {
                            ST[++k] = 0;
                        }
                    }
                }
                else
                {
                    if (ST[k] > 1)
                    {
                        DesenareRegina(k, ST[k], panel1.BackColor,10);
                    }
                    k--;
                }
            }
        }

        private void DesenareRegina(int linie,int coloana,Color culoare,int timer)
        {
            Pen p = new Pen(culoare, 2f);
            Graphics g = panel1.CreateGraphics();
            g.DrawEllipse(p, L * (coloana - 1) + 2 , l * (linie - 1)+2 , L-4 , l-4 );
            Thread.Sleep(timer);
        }
        
        private void DesenareTabla()
        {
            Rectangle r = new Rectangle(0, 0, panel1.Width, panel1.Height);
            Pen p = new Pen(Color.Black, 2f);
            Graphics g = panel1.CreateGraphics();
            g.DrawRectangle(p, r);
            l = (float)panel1.Height / n;
            L = (float)panel1.Width / n;
            for(int i=1;i<n;i++)
            {
                g.DrawLine(p, i * L, 0, i * L, panel1.Height);
                g.DrawLine(p, 0, i * l, panel1.Width, i * l);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text.Length > 0)
            {
                n = Convert.ToInt32(textBox1.Text);
                Graphics g = panel1.CreateGraphics();
                g.Clear(panel1.BackColor);
                DesenareTabla();
                t = new Thread(new ThreadStart(Back));
                t.Start();
              //  Back();
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            t.Abort();
        }
    }
}
