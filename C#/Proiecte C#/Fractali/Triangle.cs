using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Fractali
{
    class Triangle
    {
        private PointF X, Y, Z;
        private Color K=Color.White;
        public Triangle(PointF A, PointF B, PointF C)
        {
            X = A;
            Y = B;
            Z = C;
        }
        public Triangle(PointF A, PointF B, PointF C,Color c)
        {
            X = A;
            Y = B;
            Z = C;
            K = c;
        }
        public void Draw(Graphics g)
        {
            Pen p = new Pen(K, 2);
            g.DrawLine(p, X, Y);
            g.DrawLine(p, X, Z);
            g.DrawLine(p, Y, Z);
        }
        public PointF GetX()
        {
            return X;
        }
        public PointF GetY()
        {
            return Y;
        }
        public PointF GetZ()
        {
            return Z;
        }

    }
}
