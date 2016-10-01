using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Fairport.Map {
    public class CubicSpline {
        public double a, b, c, d, xj;

        public double ValueOf(double x) {
            double dx = x - xj;
            return a + b * dx + c * dx * dx + d * dx * dx * dx;
        }
    }
}
