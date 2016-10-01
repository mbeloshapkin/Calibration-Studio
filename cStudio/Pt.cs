using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Drawing; // for point size and so on only

namespace cStudio {

    // strictly limited to latitude/longitude values. Do not use for critical calculations, it's slow. Use Pt class instead.
    class GeoPt {
        private double _Lat, _Lng; // In Radians
        public double rLat { get { return _Lat; } set { _Lat = Normalize(value); } }
        public double rLng { get { return _Lng; } set { _Lng = Normalize(value); } }
        public double Lat { get { return _Lat * 180.0 / Math.PI; } set { _Lat = Normalize(value * Math.PI / 180.0); } }
        public double Lng { get { return _Lng * 180.0 / Math.PI; } set { _Lng = Normalize(value * Math.PI / 180.0); } }

        public GeoPt(double ALng, double ALat) {
            Lat = ALat; Lng = ALng;
        }

        private double Normalize(double val) {
            if (val <= Math.PI && val > -Math.PI) return val;
            int n = (int)Math.Floor(0.5 * val / Math.PI);
            double ret = val - 2 * n * Math.PI;
            if (ret > Math.PI) ret -= 2 * Math.PI;
            if (ret <= -Math.PI) ret += 2 * Math.PI;
            return ret;
        }

        public override string ToString() {
            return Lng.ToString() + ";" + Lat.ToString();
        }
        
    }

    public class Pt : IComparable, IEquatable<Pt> {
        public double x,y;  // in geographic systems - degrees by default. In non geographic can be any
        public virtual double Norm { get { return Math.Sqrt(x * x + y * y); } }
        public Pt() { }
        public Pt(double ax, double ay) { x = ax; y = ay; }
        public Pt(Point p) { x = p.X; y = p.Y; }
        public Pt(string text) {
            int comma = text.IndexOf(',');
            string tag;
            if (comma > 0) {
                tag = text.Substring(0, comma);
                tag.Trim();
                x = Convert.ToDouble(tag);
            }
            int start = comma + 1;
            comma = text.IndexOf(',', start);
            if (comma < 0) comma = text.IndexOf(' ', start);
            if (comma < 0) comma = text.Length;
            if (comma > start) {
                tag = text.Substring(start, comma - start);                      
                tag.Trim();
                y = Convert.ToDouble(tag);
            }
        }

        // x and y in radians for geodetic calculations
        public double rLng { // Longitude in radians
            get { return x * Math.PI / 180.0; }
            set { x = value * 180.0 / Math.PI; }
        }
        public double rLat {
            get { return y * Math.PI / 180.0; }
            set { y = value * 180.0 / Math.PI; }
        }
        
        public int CompareTo(object p1) {
            if ((p1 as Pt).x == x && (p1 as Pt).y == y) return 0;
            else if ((p1 as Pt).x + (p1 as Pt).y > x + y) return 1;
            return -1;
        }

        public Pt Clone() { Pt r = new Pt(); r.x = x; r.y = y; return r; }

        public bool Equals(Pt p) { 
            return p.x == x && p.y == y; 
        }

        public override string ToString() { // remember many formats are using space to separate pairs of coordinates...
            return x.ToString() + "," + y.ToString();
        }

        public double DistanceTo(Pt p) { return Math.Sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y)); }
        
        #region operators
        public static Pt operator +(Pt p, double inc) { return new Pt(p.x + inc, p.y + inc); }
        public static Pt operator +(Pt p, Pt inc) { return new Pt(p.x + inc.x, p.y + inc.y); }
        public static Pt operator -(Pt p, double dec) { return new Pt(p.x - dec, p.y - dec); }
        public static Pt operator -(Pt p, Pt dec) { return new Pt(p.x - dec.x, p.y - dec.y); }
        public static Pt operator -(Pt p) { return new Pt(-p.x, -p.y); }
        public static Pt operator *(Pt p, double val) { return new Pt(p.x * val, p.y * val); }
        public static Pt operator *(double val, Pt p) { return new Pt(p.x * val, p.y * val); }
        public static Pt operator /(Pt p, double val) { return new Pt(p.x / val, p.y / val); }
        public static Pt operator *(Pt p, Pt val) { return new Pt(p.x * val.x, p.y * val.y); }
        public static Pt operator /(Pt p, Pt val) { return new Pt(p.x / val.x, p.y / val.y); }
        //public static bool operator ==(Pt p1, Pt p2) { return p1.x == p2.x && p1.y == p2.y; }
        //public static bool operator !=(Pt p1, Pt p2) { return p1.x != p2.x || p1.y != p2.y; }
        // The unary operators like *= C# overrides automatically!
        public static implicit operator Pt(Size s) { return new Pt((double)s.Width, (double)s.Height); }
        public static implicit operator Pt(Point p) { return new Pt((double)p.X, (double)p.Y); }
        public static explicit operator Point(Pt p) { return new Point((int)p.x, (int)p.y); }
        public static explicit operator PointF(Pt p) { return new PointF((float)p.x, (float)p.y); } 
        #endregion

    }

    interface IValue {
        double X{get; set;}
        double Y{get; set;}
        double Value{get; set;}  // x and y are the coordinates and z is the value. z can be a 3d coordiate as well
    }

    public class Pt3 : Pt, IValue {
        public double z; // in meters by default 
        public double X { get { return x; } set { x = value; } }
        public double Y { get { return y; } set { y = value; } }
        public double Value { get { return z; } set { z = value; } }
        public override double Norm { get { return Math.Sqrt(x * x + y * y + z * z); } }

        public Pt3() { }

        public Pt3(double Ax, double Ay, double Az) {
            x = Ax; y = Ay; z = Az;
        }

        public Pt3(Pt p) {
            x = p.x; y = p.y; z = 0;
        }
        public Pt3(Pt p, double val) {
            x = p.x; y = p.y; z = val;
        }
        
        public new int CompareTo(object p1) {
            if (p1 is Pt) {
                if ((p1 as Pt).x == x && (p1 as Pt).y == y) return 0;
                else if ((p1 as Pt).x + (p1 as Pt).y > x + y) return 1;
                return -1;
            }
            if ((p1 as Pt3).x == x && (p1 as Pt3).y == y && (p1 as Pt3).z == z) return 0;
            else if ((p1 as Pt3).x + (p1 as Pt3).y + (p1 as Pt3).z > x + y + z) return 1;
            return -1;
        }

        public new Pt3 Clone() { return new Pt3(x, y, z); }

        public override string ToString() {
            return base.ToString() + "," + z.ToString();
        }

        #region operators
        public static Pt3 operator +(Pt3 p, double inc) { return new Pt3(p.x + inc, p.y + inc, p.z + inc); }
        public static Pt3 operator +(Pt3 p, Pt3 inc) { return new Pt3(p.x + inc.x, p.y + inc.y, p.z + inc.z); }
        public static Pt3 operator -(Pt3 p, double dec) { return new Pt3(p.x - dec, p.y - dec, p.z - dec); }
        public static Pt3 operator -(Pt3 p, Pt3 dec) { return new Pt3(p.x - dec.x, p.y - dec.y, p.z - dec.z); }
        public static Pt3 operator -(Pt3 p) { return new Pt3(-p.x, -p.y, -p.z); }
        public static Pt3 operator *(Pt3 p, double val) { return new Pt3(p.x * val, p.y * val, p.z * val); }
        public static Pt3 operator *(double val,Pt3 p) { return new Pt3(p.x * val, p.y * val, p.z * val); }
        public static Pt3 operator /(Pt3 p, double val) { return new Pt3(p.x / val, p.y / val, p.z / val); }
        public static Pt3 operator *(Pt3 p, Pt3 val) { return new Pt3(p.x * val.x, p.y * val.y, p.z * val.z); }
        public static Pt3 operator /(Pt3 p, Pt3 val) { return new Pt3(p.x / val.x, p.y / val.y, p.z / val.z); }

        public static Pt3 operator +(Pt3 p, Pt inc) { return new Pt3(p.x + inc.x, p.y + inc.y, p.z); }
        public static Pt3 operator -(Pt3 p, Pt dec) { return new Pt3(p.x - dec.x, p.y - dec.y, p.z); }
        public static Pt3 operator *(Pt3 p, Pt val) { return new Pt3(p.x * val.x, p.y * val.y, p.z); }
        public static Pt3 operator /(Pt3 p, Pt val) { return new Pt3(p.x / val.x, p.y / val.y, p.z); }

        // The unary operators like *= C# overrides automatically!
        #endregion

    }
          
}
