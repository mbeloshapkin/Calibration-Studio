using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using DotNetMatrix;
namespace Fairport.Map {
    public static class PolyMan {
        /// <summary>
        /// It's proven to be impossible, but polyman is potent.
        /// Search for closest inverse polinom at the range ARange
        /// </summary>
        /// <param name="APolynom"></param>
        /// <param name="ARange"></param>
        /// <returns></returns>
        public static Polynom Invert(Polynom APolynom, DataRange ARange) {
            Polynom r = new Polynom(APolynom.ElemCount);
            for (int ct = 0; ct < r.ElemCount; ct++) r.Elems[ct].Exponent = APolynom.Elems[ct].Exponent;

            Pt[] grid = new Pt[r.ElemCount * 3 + 1];
            double grdstep = ARange.Size / (double)(grid.Length - 1);

            for (int ct = 0; ct < grid.Length; ct++) {
                Pt mark = new Pt();
                mark.y = ARange.Min + (double)ct * grdstep;
                mark.x = APolynom.ValueOf(mark.y);
                grid[ct] = mark;
            }
            
            GeneralMatrix M = new GeneralMatrix(grid.Length,r.ElemCount);
            GeneralMatrix V = new GeneralMatrix(grid.Length, 1);

            double sqd0, sqd1, prize0 = -1, prize1 = 0;
            int itercount = 1000; Polynom best = r.Clone();

            while (itercount > 0) {

                sqd0 = 0;

                for (int ct = 0; ct < grid.Length; ct++) {
                    double err = grid[ct].y - r.ValueOf(grid[ct].x);
                    V.Array[ct][0] = err; sqd0 += err * err;                    
                    for (int ctf = 0; ctf < r.ElemCount; ctf++) {
                        M.Array[ct][ctf] = Math.Pow(grid[ct].x, r.Elems[ctf - 1].Exponent);
                    }
                }

                GeneralMatrix A = M.Solve(V);

                // applay correction
                for (int ctf = 0; ctf < r.ElemCount; ctf++) {
                    r[ctf] += A.Array[ctf][0];
                }
                // Calc prize
                sqd1 = 0;
                for (int ct = 0; ct < grid.Length; ct++) {
                    double err = grid[ct].y - r.ValueOf(grid[ct].x);
                    sqd1 += err * err;
                }

                if (prize0 < 0) prize0 = sqd1 - sqd0;  // First iteration
                else {
                    prize0 = prize1; prize1 = sqd1 - sqd0;
                }

                if (prize1 <= 0) break; // No more improvements

                best = r.Clone();
                itercount--;
            }

            return best;
        }

        public static Polynom Approximate(Pt[] AData, Polynom ATemplate) {

            GeneralMatrix M = new GeneralMatrix(AData.Length, ATemplate.ElemCount);
            GeneralMatrix V = new GeneralMatrix(AData.Length, 1);

            Polynom r = ATemplate.Clone(); r.DropFactors();

            double sqd0, sqd1, prize0 = -1, prize1 = 0;
            int itercount = 1000; Polynom best = r.Clone();

            while (itercount > 0) {

                sqd0 = 0;

                for (int ct = 0; ct < AData.Length; ct++) {
                    double err = AData[ct].y - r.ValueOf(AData[ct].x);
                    V.Array[ct][0] = err; sqd0 += err * err;
                    for (int ctf = 0; ctf < r.ElemCount; ctf++) {
                        M.Array[ct][ctf] = Math.Pow(AData[ct].x, r.Elems[ctf].Exponent);
                    }
                }

                GeneralMatrix A = M.Solve(V);

                // applay correction
                for (int ctf = 0; ctf < r.ElemCount; ctf++) {
                    r[ctf] += A.Array[ctf][0];
                }
                // Calc prize
                sqd1 = 0;
                for (int ct = 0; ct < AData.Length; ct++) {
                    double err = AData[ct].y - r.ValueOf(AData[ct].x);
                    sqd1 += err * err;
                }

                if (prize0 < 0) { prize0 = sqd0 - sqd1; prize1 = prize0; }  // First iteration
                else {
                    prize0 = prize1; prize1 = sqd0 - sqd1;
                }

                if (prize1 <= 0) break; // No more improvements

                best = r.Clone();
                itercount--;
            }

            return best;
        }
    
    }
}
