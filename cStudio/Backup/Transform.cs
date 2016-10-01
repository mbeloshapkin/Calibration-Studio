using System;
using System.Collections.Generic;
using System.Text;

namespace cStudio {
    abstract class Transform {
        public abstract Pt Direct(Pt p);
        public abstract Pt Inverse(Pt p);
    }

    class TrSS: Transform {
        public Pt Shift, Scale;

        public TrSS(Pt AShift, Pt AScale) { Shift = AShift; Scale = AScale; } 

        public override Pt Direct(Pt p) {
            Pt r = (p + Shift) * Scale;
            return r;
        }

        public override Pt Inverse(Pt p) {
            Pt r = p / Scale - Shift;
            return r;
        }

    }
}
