using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;

namespace cStudio {
    class MathLine {
        private const double Pi2 = Math.PI / 2.0;
        private double _A, _B, _C; // Ax + By + C = 0;
        public double A { get { return _A; } }
        public double B { get { return _B; } }
        public double C { get { return _C; } }
        // x*cos(w) + y*sin(w) - P = 0; w = Alpha + Pi2;
        public double Alpha { get { return Math.Acos(_A) - Pi2; } }
        public double P { get { return -_C; } }

        public bool IsValid { get { return A != 0 || B != 0; } }
        public bool IsVertical { get { return _B == 0.0; } }
        public bool IsHorizontal { get { return _A == 0; } }

        public MathLine(Pt p, double Alpha) {
            Create(p, Alpha);
        }

        public MathLine(Pt p1, Pt p2) {            
            Create(p1, p2);
        }

        public double Y(double x) {
            if (_B == 0.0) {
                throw new Exception("MathLine: Unable to calculate Y(x) because B = 0"); 
            }
            return -(_A * x + _C) / _B;
        }

        public double X(double y) {
            if (_A == 0.0) return double.NaN;
            return -(_B * y + _C) / _A;
        }

        public double DistanceTo(Pt p) {
            //double SqAB = Math.Sqrt(A * A + B * B);
            double d = _A * p.x + _B * p.y + _C;   // The lines are always normalized
            if (_C < 0) return Math.Abs(d);
            else return -Math.Abs(d);
        }

        public bool IsParallel(MathLine l) {
            return _A == l._A; // B will be also equal l.B because the line is always normalized
        }

        public bool IsPerpendicular(MathLine l) {
            return _A * l._A + _B * l._B == 0;
        }

        public Pt Intersect(MathLine l) { // returns null if the lines are parallel
            if (IsParallel(l)) return null;
            double ab = _A * l._B - l._A * _B;
            Pt ret = new Pt();
            ret.x = (_B * l._C - l._B * _C) / ab;
            ret.y = (_C * l._A - l._C * _A) / ab;
            return ret;
        }

        private void Create(Pt p, double Alpha) {
            _A = Math.Cos(Alpha + Pi2);  // It always creates the normalized line equations
            _B = Math.Sin(Alpha + Pi2);
            _C = -(_A * p.x + _B * p.y);
        }

        private void Create(Pt p0, Pt p1) {
            if (p0.x != p1.x) {
                _A = 1.0 / (p1.x - p0.x);
                if (p0.y != p1.y) {
                    _B = -1.0 / (p1.y - p0.y);
                    _C = p0.y / (p1.y - p0.y) - p0.x / (p1.x - p0.x);
                    Normalize();
                } else {
                    _A = 0;
                    _B = 1;
                    _C = -p0.y;
                }
            } else {
                if (p0.y != p1.y) {
                    _A = 1;
                    _B = 0;
                    _C = -p0.x;
                } else { // points are coincedenting
                    throw new Exception("MathLine: attempt to create MathLine using 2 coincedenting points");
                }
            }
        }

        private void Normalize() { // The line should be always normalized
            double sq = Math.Sqrt(_A * _A + _B * _B);
            if (_C > 0) sq = -sq;
            _A /= sq; _B /= sq; _C /= sq;
        }

        public override string ToString() {
            return (Alpha * 180.0 / Math.PI).ToString() + ',' + P.ToString();
        }

        #region XML        

        public void Create(XmlNode ARoot) {                        
            _A = Convert.ToDouble(ARoot.Attributes["A"]);
            _B = Convert.ToDouble(ARoot.Attributes["B"]);
            _C = Convert.ToDouble(ARoot.Attributes["C"]);            
        }

        public void AddTo(XmlNode ARoot) {
            XmlDocument xdoc = ARoot.OwnerDocument;
            XmlNode xn = xdoc.CreateNode("element","MathLine","");
            XmlAttribute xa = xdoc.CreateAttribute("A");
            xa.Value = _A.ToString("E18");
            xn.Attributes.Append(xa);
            xa = xdoc.CreateAttribute("B");
            xa.Value = _B.ToString("E18");
            xn.Attributes.Append(xa);
            xa = xdoc.CreateAttribute("C");
            xa.Value = _C.ToString("E18");
            xn.Attributes.Append(xa);
            ARoot.AppendChild(xn);
        }
        #endregion
    }
}
