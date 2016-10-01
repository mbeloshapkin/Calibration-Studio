using System;
using System.Collections.Generic;
using System.Text;

namespace cStudio {
    class Camera {
        public string Name;
        public string Vendor;
        public string Serial;
        public bool IsDSLR;
        public Pt MatrixSize; // In mm
        public int Width;
        public int Height;
        public Lens Lens;

        public Camera Clone() {
            Camera r = new Camera();
            r.Name = Name;
            r.Vendor = Vendor; r.Serial = Serial; r.IsDSLR = IsDSLR;
            r.MatrixSize = MatrixSize.Clone();
            r.Width = Width;
            r.Height = Height;
            r.Lens = Lens.Clone();
            return r;
        }
    }
}
