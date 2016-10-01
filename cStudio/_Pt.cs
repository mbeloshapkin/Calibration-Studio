using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace cStudio {
    class Pt: IEquatable<Pt> {
        public double x, y;

        #region Construction

        public Pt() { }

        public Pt(double ax, double ay) {
            x = ax; y = ay;
        }

        public Pt(Point p) {
            x = p.X; y = p.Y;
        }
        #endregion

        public double Norm() {
            return Math.Sqrt(x * x + y * y);
        }

        public double Distance(Pt p) {
            return (this - p).Norm();
        }

        public override string ToString() {
            return x.ToString() + "," + y.ToString();
        }

        public bool Equals(Pt p) {
            return x == p.x && y == p.y;
        }

        public Pt Clone() { Pt r = new Pt(); r.x = x; r.y = y; return r; }

        #region Operators
        public static bool operator ==(Pt p1, Pt p2){ return p1.x == p2.x && p1.y == p2.y; }
        public static bool operator !=(Pt p1, Pt p2) { return p1.x != p2.x || p1.y != p2.y; }
        public static Pt operator +(Pt p1, Pt p2) { return new Pt(p1.x + p2.x, p1.y + p2.y); }
        public static Pt operator -(Pt p1, Pt p2) { return new Pt(p1.x - p2.x, p1.y - p2.y); }
        public static Pt operator *(Pt p1, Pt p2) { return new Pt(p1.x * p2.x, p1.y * p2.y); }
        public static Pt operator /(Pt p1, Pt p2) { return new Pt(p1.x / p2.x, p1.y / p2.y); }
        public static Pt operator -(Pt p) { return new Pt(-p.x, -p.y); }

        public static Pt operator +(Pt p, double z) { return new Pt(p.x + z, p.y + z); }
        public static Pt operator -(Pt p, double z) { return new Pt(p.x - z, p.y - z); }
        public static Pt operator *(Pt p, double z) { return new Pt(p.x * z, p.y * z); }
        public static Pt operator /(Pt p, double z) { return new Pt(p.x / z, p.y / z); }
        #endregion

    }
}
