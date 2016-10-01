using System;
using System.Collections.Generic;
using System.Text;

namespace cStudio {
    abstract class Transform: IEquatable<Transform>, ICloneable {
        public delegate Pt Convert(Pt p);
        public abstract Pt Direct(Pt p);
        public abstract Pt Inverse(Pt p);
        public abstract Pt3 Direct(Pt3 p);
        public abstract Pt3 Inverse(Pt3 p);

        public MBR Direct(MBR m) { 
            MBR ret = new MBR(m, this);
            // In the common case MBR can be rotated by this, so:
            ret.Update(Direct(m.TopLeft));
            ret.Update(Direct(m.BottomRight));
            return ret;
        }
        public MBR Inverse(MBR m) { 
            MBR ret = new MBR(Inverse(m.Min), Inverse(m.Max));
            ret.Update(Inverse(m.TopLeft));
            ret.Update(Inverse(m.BottomRight));
            return ret;
        }

        //public Convert Direct(Transform.Convert func) { return Direct(func); }
        //public Convert Inverse(Transform.Convert func) { return Inverse(func); }
        public abstract bool Equals(Transform t);
        public abstract object Clone();
        //protected Pt DirectFunc(Pt p

    }
    /// <summary>
    ///  Shift & Scale transform;
    /// </summary>
    class TrSS: Transform, IEquatable<TrSS> {
        public Pt Shift;
        public Pt Scale;

        // Zero (One to One transform)
        public TrSS() { Shift = new Pt(0, 0); Scale = new Pt(1.0, 1.0); }
        public TrSS(Pt shift, double scale) { Shift = shift.Clone(); Scale = new Pt(scale, scale); }
        public TrSS(Pt shift, Pt scale) { Shift = shift.Clone(); Scale = scale.Clone(); } // Anizotropic one! Usualy converts degrees to meters and back.
        public TrSS(TrSS t) { Shift = t.Shift.Clone(); Scale = t.Scale.Clone(); }

        public override Pt Direct(Pt p) {  // Attention! Alternative definition is possible:
            return p * Scale + Shift;    // (p + Shift) * Scale. Do not confuse! It's not the same!
        }

        public override Pt Inverse(Pt p) {
            return (p - Shift) / Scale;
        }

        public override Pt3 Direct(Pt3 p) {  // Attention! Alternative definition is possible:
            return p * Scale + Shift;    // (p + Shift) * Scale. Do not confuse! It's not the same!
        }

        public override Pt3 Inverse(Pt3 p) {
            return (p - Shift) / Scale;
        }
        /// <summary>
        /// Flips transform vertically relatively the given MBR. Quite usable to transform the mouse position 
        /// to map directly and so on. Enjoy :)
        /// </summary>
        /// <param name="mbr"></param>
        /// <returns></returns>
        public void FlipVertical(MBR mbr) {
            FlipVertical(mbr.Height);   // So simple, but solves so many problems :)            
        }

        public void FlipVertical(double AHeight){
            Scale.y = -Scale.y;
            Shift.y = AHeight - Shift.y;
        }

        public void FlipVertical(int AHeight) {
            Scale.y = -Scale.y;   
            Shift.y = AHeight - Shift.y;         
        }

        // returns t2(t1(p))
        public static TrSS operator +(TrSS t1, TrSS t2) {
            TrSS r = new TrSS();
            r.Scale = t1.Scale * t2.Scale;
            r.Shift = t2.Direct(t1.Shift);
            return r;
        }

        bool IEquatable<TrSS>.Equals(TrSS t){
            return Shift == t.Shift && Scale == t.Scale;
        }

        public override bool Equals(Transform t){
            return t is TrSS && Equals(t as TrSS);
        }

        public override object Clone() {
            return new TrSS(this); // this constructor clones it.
        }

        public override string ToString() {
            return "TrSS, Shift = " + Shift.ToString() + ", Scale = " + Scale.ToString();
        }

    }
}
