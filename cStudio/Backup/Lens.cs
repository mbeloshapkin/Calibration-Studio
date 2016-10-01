using System;
using System.Collections.Generic;
using System.Text;

namespace cStudio {
    class Lens {
        public enum FocusSource { Calibration, Documentation, File }
        public string Name;
        public string Vendor;
        public string Serial;
        public bool IsFix;
        public double FixFocus;
        public FocusSource FocusSrc;

        public Lens Clone() {
            Lens r = new Lens();
            r.Name = Name; r.Vendor = Vendor; r.Serial = Serial; r.IsFix = IsFix;
            r.FixFocus = FixFocus; r.FocusSrc = FocusSrc;
            return r;
        }
    }
}
