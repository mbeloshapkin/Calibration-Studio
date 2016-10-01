using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Drawing; // For Rect class

namespace cStudio {

    enum Dir2 { // Simple 2d direction
        Left,Up,Right,Down
    }
         /// <summary>
         /// Minimum Bounding Rectangle (MBR)
         /// A point is belongs the MBR if it is inside or belongs to lower boundary.
         /// If a point belongs to upper boundary it is not belongs to MBR
         /// </summary>    
     internal class MBR: ICloneable {   // Minimum bounding rectangle

            #region Basic public properties
            public Pt Min { get { return new Pt(xmin, ymin); } set { xmin = value.x; ymin = value.y; } }
            public Pt Max { get { return new Pt(xmax, ymax); } set { xmax = value.x; ymax = value.y; } }   // Lowerleft and upperright
            public Pt TopLeft { get { return new Pt(xmin, ymax); } set { xmin = value.x; ymax = value.y; } }
            public Pt BottomRight { get { return new Pt(xmax, ymin); } set { xmax = value.x; ymin = value.y; } }
            public Pt Size { get { return new Pt(xmax - xmin, ymax - ymin); } }
            public double xmin;
            public double ymin;
            public double xmax;
            public double ymax;
            public double Width { get { return xmax - xmin; } }
            public double Height { get { return ymax - ymin; } }
            public Pt Center { get { return new Pt((xmin + xmax) / 2, (ymax + ymin) / 2); } }
            public double Area { get { return Width * Height; } }
            public bool IsFat { get { return Width > Height; } }
            public double LongSide { get { if (Width > Height) return Width; return Height; } }
            public double ShortSide { get { if (Width > Height) return Height; return Width; } }
            public bool Valid { get { return ymax >= ymin && xmax >= xmin; } }
            #endregion

            #region Construction

            public MBR() { }
            /// <summary>
            /// Create the 1 size MBR. A point is belonging to
            /// 1 MBR if x == xmin == xmax and y == ymin == ymax
            /// </summary>
            /// <param name="p">A point</param>
            public MBR(Pt p) {  // Empty MBR, but can contain a point
                xmin = xmax = p.x; ymin = ymax = p.y;
            }
            /// <summary>
            /// The points can be at any order
            /// </summary>
            /// <param name="p1"></param>
            /// <param name="p2"></param>
            public MBR(Pt p1, Pt p2) {
                if (p1.x < p2.x) { xmin = p1.x; xmax = p2.x; }
                else { xmin = p2.x; xmax = p1.x; }
                if (p1.y < p2.y) { ymin = p1.y; ymax = p2.y; }
                else { ymin = p2.y; ymax = p1.y; }
            }

            public MBR(double width, double height) {
                xmin = 0; ymin = 0; xmax = width; ymax = height;
            }

            public MBR(Pt ACenter, double width, double height) {
                double w2 = width / 2.0; double h2 = height / 2.0;
                xmin = ACenter.x - w2; xmax = ACenter.x + w2;
                ymin = ACenter.y - h2; ymax = ACenter.y + h2;
            }

            public MBR(MBR m) {
                xmin = m.xmin; xmax = m.xmax; ymin = m.ymin; ymax = m.ymax;
            }

            public MBR(MBR m, Transform t) {
                Min = t.Direct(m.Min);
                Max = t.Direct(m.Max);            
            }

            public MBR(IEnumerable<Pt> src) { // Build it from any point source
                bool first = true;
                foreach (Pt p in src) {
                    if (first) { Min = p; Max = p; first = false; }
                    else Update(p);
                }
            }

            public static MBR CreateViaCenter(Pt ACenter, Pt ACorner) {
                MBR ret = new MBR();
                double w2 = Math.Abs(ACenter.x - ACorner.x) / 2.0;
                double h2 = Math.Abs(ACenter.y - ACorner.y) / 2.0;
                if (ACorner.x > ACenter.x) {
                    ret.xmin = ACenter.x - w2; ret.xmax = ACorner.x;
                }
                else {
                    ret.xmin = ACorner.x; ret.xmax = ACenter.x + w2;
                }
                if (ACorner.y > ACenter.y) {
                    ret.ymin = ACenter.y - h2; ret.ymax = ACorner.y;
                }
                else {
                    ret.ymin = ACorner.y; ret.ymax = ACenter.y + h2;
                }
                return ret;
            }

            public static MBR CreateSquare(Pt ACenter, double ASize) {
                return new MBR(ACenter - ASize / 2.0, ACenter + ASize / 2.0);
            }

            public object Clone() { return new MBR(this); } // this constructor clones MBR
            #endregion

            #region Updating and moving
            public void Update(Pt p) {
                if (p.x < xmin) xmin = p.x;
                if (p.x > xmax) xmax = p.x;
                if (p.y < ymin) ymin = p.y;
                if (p.y > ymax) ymax = p.y;
            }

            public void Update(MBR m) {
                Update(m.Min); Update(m.Max);
            }
            /// <summary>
            /// Moves the MBR
            /// </summary>
            /// <param name="dx">A distance to move in x axis direction</param>
            /// <param name="dy">A distance to move in y axis direction</param>
            public void Move(double dx, double dy) {
                xmin += dx; xmax += dx;
                ymin += dy; ymax += dy;
            }

            public void Move(Pt p) {
                Min += p; Max += p;
            }

            /// <summary>
            /// Clip this by m
            /// </summary>
            /// <param name="m"></param>
            /// <returns>null or clipped MBR</returns>
            public MBR Clip(MBR m) {
                if (Contains(m)) return m;
                if (m.Contains(this)) return this;
                if (m.xmin >= xmax || m.ymin >= ymax || m.ymax <= ymin || m.xmax <= xmin) return null;
                MBR ret = new MBR(Min, Max);
                if (m.xmin > ret.xmin) ret.xmin = m.xmin;
                if (m.ymin > ret.ymin) ret.ymin = m.ymin;
                if (m.xmax < ret.xmax) ret.xmax = m.xmax;
                if (m.ymax < ret.ymax) ret.ymax = m.ymax;
                return ret;
            }

            #endregion

            #region Spatial relations
            public bool IsInside(Pt p) {
                return p.x >= xmin && p.x < xmax && p.y >= ymin && p.y < ymax;
            }
            
            public bool Contains(MBR m) {
                return IsInside(m.Min) && IsInside(m.Max);
            }

            public double MaxDistance(Pt p) { // The length of the longest beam started in p and ended inside the mbr
                double d1 = p.DistanceTo(Min);
                double d2 = p.DistanceTo(new Pt(xmin, ymax));
                double d3 = p.DistanceTo(Max);
                double d4 = p.DistanceTo(new Pt(xmax, ymin));
                if (d2 > d1) d1 = d2;
                if (d3 > d1) d1 = d3;
                if (d4 > d1) d1 = d4;
                return d1;
            }

            /// <summary>
            /// Get the intersection of two MBRs. Note m1.Intersect(m2) equals m2.Intersect(m1).
            /// </summary>
            /// <param name="m">The second MBR</param>
            /// <returns>The intresection if any, othervise null</returns>
            public MBR Intersect(MBR m) {                
                MBR r = new MBR();
                r.ymin = Math.Max(m.ymin, ymin);
                r.xmin = Math.Max(m.xmin, xmin);
                r.ymax = Math.Min(m.ymax, ymax);
                r.xmax = Math.Min(m.xmax, xmax);
                if (r.Valid) return r;
                return null;                
            }

            #endregion

            #region Mapping
            /// <summary>
            /// A Great Feature.
            /// Creates bidirectional transform which maps
            /// the content of the MBR into another MBR.
            /// This function is designed to map isotropic the content of the mbr to target space.
            /// It's usable for drawing.
            /// </summary>
            /// <param name="m">Target MBR.</param>
            /// <param name="AGap">The blank space, 0 if no need</param>
            /// <returns>The trasform to MBR m. This transform keeps the Width/Height ratio of the source. 
            /// If the target MBR is of different Width/Height ratio the transform will center the source MBR
            /// in the target one horisontally or vertically.</returns>
            public Transform MapTo(MBR m, double AGap) {
                Pt shift; double scale; double gap; 
                MBR gapmbr = new MBR(m.Min, m.Max);
                if (Width / m.Width > Height / m.Height) { // Map with width scale. HD TV.
                    gap = m.Width * AGap;
                    gapmbr.xmin += gap; gapmbr.xmax -= gap;
                    scale = gapmbr.Width / Width;
                    gapmbr.ymin = (m.Height - Height * scale) / 2.0 + m.ymin; 
                }
                else {
                    gap = m.Height * AGap;
                    gapmbr.ymin += gap; gapmbr.ymax -= gap;
                    scale = gapmbr.Height / Height;
                    gapmbr.xmin = (m.Width - Width * scale) / 2.0 + m.xmin;
                }
                shift = gapmbr.Min - Min * scale;
                return new TrSS(shift, scale);
            }

            public Transform MapTo(MBR m) { return MapTo(m, 0.0); }

            /// <summary>
            /// Create the transform for coordinate translation from this MBR to MBR m.
            /// In cntrast to MapTo function the return transform can be anisotrpic, if source and target MBRs
            /// are of different Width/Height ratio. All the vertexes of the source MBR will coincedent
            /// exactly with vertexes of target MBR after the transformation.
            /// </summary>
            /// <param name="m">Target MBR</param>
            /// <returns>The transform</returns>
            public Transform FitTo(MBR m) {
                TrSS ret = new TrSS();
                ret.Scale.x = m.Width / Width;
                ret.Scale.y = m.Height / Height;
                ret.Shift = (m.Min - Min) * ret.Scale;
                return ret;
            }

            /// <summary>
            /// The FlipVertical is designed to provide the compatibility between right cartesian 
            /// coordinate systems and windows screen and bitmap coordinate systems where the Y axis
            /// is of inverse direction.
            /// </summary>
            /// <param name="t">The transform from right cartesian to right cartesian coordinate system</param>
            /// <returns>The flipped vertically relatively to MBR transform</returns>
            //!!!!!!!! the implementation is moved into TrSS class
            //public Transform FlipVertical(TrSS t) {
            //    TrSS ret = new TrSS(t.Shift, t.Scale);                
            //    ret.FlipVertical(this);
            //    return ret;
            //}
            #endregion

            #region Overloads
            public override string ToString() {
                return Min.ToString() + "," + Max.ToString();
            }
            #endregion

            #region Compatibility
            public static implicit operator Rectangle(MBR mbr) {
                return new Rectangle((int)mbr.Min.x, (int)mbr.Min.y, (int)mbr.Width, (int)mbr.Height);
            }
            #endregion

            #region Operators

         public static MBR operator *(MBR m, double x) { return new MBR(m.Min * x, m.Max * x); }
         public static MBR operator *(MBR m, Pt p) { return new MBR(m.Min * p, m.Max * p); }
         public static MBR operator +(MBR m, Pt p) { return new MBR(m.Min + p, m.Max + p); }
         public static MBR operator -(MBR m, Pt p) { return new MBR(m.Min - p, m.Max - p); }
         public static MBR operator /(MBR m, double x) { return new MBR(m.Min / x, m.Max / x); }

            #endregion Operators

        }    
}
