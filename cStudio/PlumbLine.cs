using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;

namespace cStudio {
    class PlumbLine: Hashtable, IEnumerable<Pt> {
        private int PtID = 0;
        private int ID;
        private string Prefix;
        public bool IsVertical { get { return Prefix == "v"; } }
        public string Name { get { return Prefix + ID.ToString(); } }
        private MathLine mLine;

        public PlumbLine(int id, bool is_vertical) {
            if (is_vertical) Prefix = "v";
            else Prefix = "h";
            ID = id;
        }

        public PlumbLine(XmlNode xn) {
            Create(xn);
        }

        public void Add(Pt p) {            
            string ps = Name + "-" + (++PtID).ToString(); // Yes, I like C++
            base.Add(ps, p);           
        }

        public class PtEnum : IEnumerator<Pt>, IDisposable {
            IEnumerator e;
            public PtEnum(PlumbLine ALine) {
                e = ALine.Values.GetEnumerator();                
            }
            public bool MoveNext() {                
                return e.MoveNext();                
            }

            public object Current {
                get {
                    return e.Current;
                }
            }

            Pt IEnumerator<Pt>.Current {
                get {
                    return e.Current as Pt;
                }
            }

            public void Reset() { e.Reset(); }

            public void Dispose() { e = null; }

        }

        IEnumerator<Pt> IEnumerable<Pt>.GetEnumerator() {
            return new PtEnum(this);
        }

        public new IEnumerator GetEnumerator() {
            return new PtEnum(this);
        }


        #region XML        

        public void Create(XmlNode xn) {
            //xr.ReadStartElement("PlumbLine");
            //ID = Convert.ToInt32(xn.Attributes["ID"]);
            string name = xn.Attributes["Name"].Value;
            Prefix = name.Substring(0, 1);
            ID = Convert.ToInt32(name.Substring(1));
            mLine.Create(xn.SelectSingleNode("MathLine"));
            base.Clear();
            foreach (XmlNode xp in xn.ChildNodes) {
                if (xp.Name == "Pt") {
                    string pname = xp.Attributes["Name"].Value;
                    Pt p = new Pt(Convert.ToDouble(xp.Attributes["x"].Value), Convert.ToDouble(xp.Attributes["y"].Value));
                    base.Add(pname, p);
                }
            }            
        }

        public void AddTo(XmlNode ARoot) {
            XmlDocument xdoc = ARoot.OwnerDocument;
            XmlNode xn = xdoc.CreateElement("PlumbLine");
            XmlAttribute xaName = xdoc.CreateAttribute("Name");
            xaName.Value = Name;
            xn.Attributes.Append(xaName);
            //mLine.AddTo(xn);
            foreach (string sp in Keys) {
                Pt p = this[sp] as Pt;
                XmlNode xp = xdoc.CreateElement("Pt");
                XmlAttribute xpa = xdoc.CreateAttribute("Name");
                xpa.Value = sp;
                xp.Attributes.Append(xpa);
                xpa = xdoc.CreateAttribute("x");
                xpa.Value = p.x.ToString("E");
                xp.Attributes.Append(xpa);
                xpa = xdoc.CreateAttribute("y");
                xpa.Value = p.y.ToString("E");
                xp.Attributes.Append(xpa);
                xn.AppendChild(xp);
            }
            ARoot.AppendChild(xn);
        }
        #endregion
        
    }
}
