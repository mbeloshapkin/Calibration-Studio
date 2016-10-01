using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Fairport.Map {
    public class SplineApprox {
        public CubicSpline[] Splines;
        public DataRange Range;

        // The data should be sorted by x
        public SplineApprox(Pt[] XSortedData) {
            // This just to simplyfy code
            Pt[] data = XSortedData;
            int count = data.Length;

            Range = new DataRange(data[0].x, data[count - 1].x);

            Splines = new CubicSpline[count - 1];

            double[] a = new double[count];
            for(int ct = 0; ct < count; ct++) a[ct] = data[ct].y;
            
            double[] h = new double[count-1]; double[] alpha = new double[count-1];

            for (int ct = 0; ct < count - 1; ct++) h[ct] = data[ct + 1].x - data[ct].x;
            for (int ct = 1; ct < count - 1; ct++)
                alpha[ct] = 3.0 * (a[ct + 1] - a[ct]) / h[ct] -
                    3.0 * (a[ct] - a[ct - 1]) / h[ct - 1];

            double[] l = new double[count]; double[] mu = new double[count]; double[] z = new double[count];
            double[] c = new double[count];

            l[0] = 1.0; mu[0] = 0.0; z[0] = 0.0;

            for (int ct = 1; ct < count - 1; ct++) {
                l[ct] = 2.0 * (data[ct + 1].x - data[ct - 1].x) - h[ct - 1] * mu[ct - 1];
                mu[ct] = h[ct] / l[ct];
                z[ct] = (alpha[ct] - h[ct - 1] * z[ct - 1]) / l[ct];
            }

            l[count - 1] = 1.0; z[count - 1] = 0.0; c[count - 1] = 0.0;

            for (int ct = count - 2; ct >= 0; ct--) {
                Splines[ct] = new CubicSpline();
                c[ct] = z[ct] - mu[ct] * c[ct + 1];                
                Splines[ct].b = (a[ct + 1] - a[ct]) / h[ct] -
                    h[ct] * (c[ct + 1] + 2.0 * c[ct]) / 3.0;
                Splines[ct].d = (c[ct+1] - c[ct])/(3.0 * h[ct]);
                Splines[ct].a = a[ct];
                Splines[ct].c = c[ct];
                Splines[ct].xj = data[ct].x;
            }
        }

        public double ValueOf(double x) {
            // 1. search for a spline
            CubicSpline cs = null;
            if (x <= Range.Min) cs = Splines[0];
            else {
                if (x >= Splines[Splines.Length - 1].xj) cs = Splines[Splines.Length - 1];
                else {
                    for (int ct = 1; ct < Splines.Length; ct++) {
                        if (x < Splines[ct].xj) {
                            cs = Splines[ct - 1]; break;
                        }
                    }
                }
            }
            return cs.ValueOf(x);
        }

    }
}
