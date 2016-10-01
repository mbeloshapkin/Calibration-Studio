using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;

namespace cStudio {
    // Plumbline calibration data
    class PLCData {
        private Hashtable Images;
        public int ImgCount { get { return Images.Count; } }

        public PLCData() {
            Images = new Hashtable();
        }

        public void Add(CImage Img) {
            Images.Add(Img.Name, Img);
        }

    }
}
