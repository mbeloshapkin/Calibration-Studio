using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;

namespace cStudio {
    class CPLCalibrationImage: CImage, IEnumerable {
        public Hashtable Lines;
        private int VLID = 0, HLID = 0;
        public int Count { get { return Lines.Count; } }
        public PlumbLine this[string line] { get { return Lines[line] as PlumbLine; } }

        public CPLCalibrationImage() { Lines = new Hashtable(); }

        public void Add(bool is_vertical){
            PlumbLine pl;
            if(is_vertical) pl = new PlumbLine(++VLID,true);
            else pl = new PlumbLine(++HLID,false);
            Lines.Add(pl.Name,pl);
        }

        public void Remove(string line) {
            Lines.Remove(line);
        }

        public IEnumerator GetEnumerator() { return Lines.GetEnumerator(); }

    }
}
