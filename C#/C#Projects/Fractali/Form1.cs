using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Fractali
{
    // Main function for the Fractal Project
    public partial class Form1 : Form
    {
        Color[] Culori = new Color[6] { Color.Red, Color.Green, Color.White, Color.Blue, Color.Yellow, Color.Ivory };
        Random R = new Random();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            button1.Location = new Point(20, 20);
            button2.Location = new Point(20, 70);
            button3.Location = new Point(20, 120);
            button4.Location = new Point(20, 170);
        }


        //  COVORUL LUI SIERBINSKI
        private void button1_Click(object sender, EventArgs e)
        {
            Graphics g = panel1.CreateGraphics();
            g.Clear(Color.Gainsboro);
            Covor(150, 150, 200, 0);
        }
        private void Covor(int x, int y, int l, int k)
        {
            if (l > 5)
            {
                System.Threading.Thread.Sleep(5);
                Rectangle r = new Rectangle(x, y, l, l);
                Graphics g = panel1.CreateGraphics();
                //   Pen p = new Pen(Culori[R.Next(0,5)], 2);
                Pen p = new Pen(Culori[k % 6], 2);
                g.DrawRectangle(p, r);
                Covor(x - l / 4, y - l / 4, l / 2, k + 1);
                Covor(x + l - l / 4, y - l / 4, l / 2, k + 1);
                Covor(x + l - l / 4, y + l - l / 4, l / 2, k + 1);
                Covor(x - l / 4, y + l - l / 4, l / 2, k + 1);
            }
        }


        // TRIUNGHIUL LUI SIERBINSKI
        private void button2_Click(object sender, EventArgs e)
        {
            Graphics g = panel1.CreateGraphics();
            g.Clear(Color.Gainsboro);
            Triunghi();
        }
        private void Triunghi()
        {
            Graphics g = panel1.CreateGraphics();
            float X = panel1.Width / 2f, Y = panel1.Height / 2f, L = 300;
            double H = L * Math.Sqrt(3f / 4);
            PointF A = new PointF(X - L / 2, Y + (float)H / 3);
            PointF B = new PointF(X + L / 2, A.Y);
            PointF C = new PointF(X, Y - 2 * (float)H / 3);
            Triangle t = new Triangle(A, B, C, Color.White);
            t.Draw(g);
            Sierpinski(t, 0);
        }
        private void Sierpinski(Triangle t, int nr)
        {
            float l = t.GetY().X - t.GetX().X;
            if (l > 10)
            {
                System.Threading.Thread.Sleep(50);
                Graphics g = panel1.CreateGraphics();
                PointF A = new PointF((t.GetY().X + t.GetX().X) / 2f, t.GetX().Y);
                PointF B = new PointF((t.GetZ().X + t.GetX().X) / 2f, (t.GetX().Y + t.GetZ().Y) / 2f);
                PointF C = new PointF((t.GetY().X + t.GetZ().X) / 2f, (t.GetY().Y + t.GetZ().Y) / 2f);
                Triangle T = new Triangle(A, B, C);
                T.Draw(g);
                Sierpinski(new Triangle(t.GetX(), A, B), nr + 1);
                Sierpinski(new Triangle(A, t.GetY(), C), nr + 1);
                Sierpinski(new Triangle(B, C, t.GetZ()), nr + 1);
            }
        }


        //  LINIA LUI KOCH
        private void button3_Click(object sender, EventArgs e)
        {
            Graphics g = panel1.CreateGraphics();
            g.Clear(Color.Gainsboro);
            Linie();
        }
        private void Linie()
        {
            int L = 450;
            PointF A = new PointF(panel1.Width / 2f - L / 2, panel1.Height / 2), B = new PointF(panel1.Width / 2f + L / 2, panel1.Height / 2);
            Graphics g = panel1.CreateGraphics();
            Pen p = new Pen(Color.White, 2);
            g.DrawLine(p, A, B);
            Koch1(A, B, 0);
        }
        private void Koch1(PointF A, PointF B, int nr)
        {
            if (nr <= 2)
            {
                float L = (float)Math.Sqrt(Math.Pow(A.X - B.X, 2) + Math.Pow(A.Y - B.Y, 2)), l = L / 3;
                PointF M = new PointF(A.X + l, A.Y), N = new PointF(B.X - l, B.Y);
                double H = l * Math.Sqrt(3 / 4f);
                Pen s = new Pen(Color.Gainsboro, 2);
                Graphics g = panel1.CreateGraphics();
                g.DrawLine(s, M, N);
                Pen p = new Pen(Color.White, 2);
                PointF P = new PointF((B.X + A.X) / 2f, M.Y - (float)H);
                g.DrawLine(p, M, P);
                g.DrawLine(p, P, N);
                Koch1(A, M, nr + 1);
               // TODO add angle to make sure new points are located properly
               // + add angles to all recursive calls to make sure strucure is 
               // ready to compute Snowflake Fractal
               // Koch1(M, P, nr + 1);
               // Koch1(P, N, nr + 1);
                Koch1(N, B, nr + 1);
            }
        }

        // FULGUL LUI KOCH
        private void button4_Click(object sender, EventArgs e)
        {
            Graphics g = panel1.CreateGraphics();
            g.Clear(Color.Gainsboro);
            Fulg();
        }
        private void Fulg()
        {
            // TODO implement koch fractal
        }
    }
}

