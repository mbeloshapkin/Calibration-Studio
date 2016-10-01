using System;
using System.Collections.Generic;
using System.Text;

namespace cStudio {
    // the Photographic style value, like 1/100, 1/5.6 and so on
    class Rational {
        public int Num; // Numerator
        public int Den; // Denominator;

        public Rational(byte[] val) {
            int ct;
            Num = 0; Den = 0;
            for (ct = 3; ct > 0; ct--) {
                Den += val[ct]; Num += val[ct + 4];
                Num *= 256; Den *= 256;               
            }
            Den += val[0];
            Num += val[4];
        }

        public override string ToString() {
            if (Num > Den)
                return "1/" + ((decimal)Num / (decimal)Den).ToString();
            else
                return ((decimal)Den / (decimal)Num).ToString();
        }

        public static implicit operator double(Rational r) { return (double)r.Den / (double)r.Num; }
        
    }
}
