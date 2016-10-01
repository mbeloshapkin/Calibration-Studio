using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;

namespace cStudio {
    class PlumbLine: Hashtable {
        private int PtID = 0;
        private int ID;
        private string Prefix;
        public bool IsVertical { get { return Prefix == "v"; } }
        public string Name { get { return Prefix + ID.ToString(); } }

        public PlumbLine(int id, bool is_vertical) {
            if (is_vertical) Prefix = "v";
            else Prefix = "h";
            ID = id;
        }

        public void Add(Pt p) {            
            string ps = Name + "/" + (++PtID).ToString(); // Yes, I like C++
            base.Add(ps, p);
        }

    }
}
