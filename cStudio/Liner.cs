using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;

namespace cStudio {
    // The uiiversal linearizer of any empirical 2d data
    // It's searching for a Ax + By + C = 0 for any set of values, if number of values > 1
    static class Liner {
        private const double Pi2 = Math.PI / 2;
        private const double Eps = 0.001; // It's enough for empirical data, it nether have more precision        
        private static double _SQD;                
        private static Pt Center;                        
        public static double StdDeviation{ get{return _SQD;} }        
        
        public static MathLine CreateLine(IEnumerable<Pt> Src) {
            ArrayList pts = new ArrayList();
            MBR mbr = null;
            foreach (Pt p in Src) {
                if (mbr == null) mbr = new MBR(p);
                else mbr.Update(p);
                pts.Add(p);
            }
            
            if (pts.Count < 2) return null;

            if (pts.Count == 2) { // Direct solution
                Pt p0 = pts[0] as Pt; Pt p1 = pts[1] as Pt;
                _SQD = 0;
                if (p0 == p1) {
                    throw(new Exception("Coincendenting calibration poionts found"));
                }                
                return new MathLine(p0, p1);                
            }
            // Calculate the center of the garvity
            Pt sum = new Pt(0,0);            
            foreach (Pt p in pts) sum += p;                            
            
            Center = sum / (double)pts.Count; 
            // OK, have at least 1 point; Let Alpha = 0, y = b;
            
            double deda;
            double da, prec, step;
            MathLine l0,l1;
            if (mbr.IsFat) { // The line seems horisontal;
                l0 = new MathLine(Center, 0);
                step = 0.3 * mbr.Height / mbr.Width; 
                prec = Eps * mbr.Height / mbr.Width;
            }
            else { // The line seems to be vertical;
                l0 = new MathLine(Center,Pi2);
                step = 0.3 * mbr.Width / mbr.Height;
                prec = Eps * mbr.Width / mbr.Height;
            }

            double oldde = Calc_dEdA(Src,l0,prec);

            for(deda = oldde; deda != 0.0;){
                if (oldde * deda < 0) step *= 1 - 0.615; // different signs! Fibbonacchi!
                if (deda > 0) da = -step;
                else da = step;                
                l1 = new MathLine(Center, l0.Alpha + da);
                oldde = deda;
                deda = Calc_dEdA(Src,l1,prec);
                l0 = l1;
            }

            _SQD = CalcSQD(l0, Src);                        

            return l0;
        }
                
        private static double CalcSQD(MathLine l, IEnumerable<Pt> src) {             
            double sum = 0, e;
            int ct = 0;
            foreach (Pt p in src) {
                e = l.DistanceTo(p);
                sum += e * e;
                ct++;
            }
            return Math.Sqrt(sum / (double)ct);
        }

        private static double Calc_dEdA(IEnumerable<Pt> src, MathLine l, double prec) { // return zero means the solution is found 
            double a0 = l.Alpha;
            double a1 = a0 + prec;
            double a2 = a0 - prec;
            MathLine l1 = new MathLine(Center, a1);
            MathLine l2 = new MathLine(Center, a2);
            double sd0 = CalcSQD(l,src);
            double sd1 = CalcSQD(l1,src);
            double sd2 = CalcSQD(l2,src);
            if (sd1 >= sd0 && sd2 >= sd0) return 0.0; // No effect on the Eps range
            if (sd1 < sd2) { // sd1 is better
                return (sd1 - sd0) / prec;
            }
            else {
                return (sd2 - sd0) / -prec;
            }
        }
                
    }
        
}
