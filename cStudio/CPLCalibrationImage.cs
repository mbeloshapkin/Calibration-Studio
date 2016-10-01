using System;
using System.Collections.Generic;
using System.Text;
using System.Collections;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;

namespace cStudio {
    class CPLCalibrationImage: CImage, IEnumerable {
        public Hashtable Lines;
        private int VCount = 0, HCount = 0;
        public int Count { get { return Lines.Count; } }
        public PlumbLine this[string line] { get { return Lines[line] as PlumbLine; } }

        public CPLCalibrationImage() { Lines = new Hashtable(); }

        public void Add(bool is_vertical){
            PlumbLine pl;
            if(is_vertical) pl = new PlumbLine(++VCount,true);
            else pl = new PlumbLine(++HCount,false);
            Lines.Add(pl.Name,pl);
        }

        public void Remove(string line) {
            Lines.Remove(line);
        }

        public IEnumerator GetEnumerator() { return Lines.GetEnumerator(); }
       
        #region XML        

        public override void Create(XmlNode xn) {
            Lines = new Hashtable(); VCount = 0; HCount = 0;
            XmlNode xi = xn.SelectSingleNode("Image");
            base.Create(xi);
            XmlNode xpb = xn.SelectSingleNode("Plumblines");
            foreach (XmlNode xpl in xpb.ChildNodes) {
                PlumbLine pb = new PlumbLine(xpl);
                Lines.Add(pb.Name, pb);
                if (pb.IsVertical) VCount++;
                else HCount++;
            }
        }

        public override void AddTo(XmlNode xn) {
            XmlDocument xdoc = xn.OwnerDocument;
            XmlNode cix = xdoc.CreateElement("CalibrationImage");
            XmlAttribute xa = xdoc.CreateAttribute("LineCount");
            xa.Value = Count.ToString();
            cix.Attributes.Append(xa);
            base.AddTo(cix);
            XmlNode xpb = xdoc.CreateElement("PlumbLines");
            foreach (PlumbLine pl in Lines.Values) {
                pl.AddTo(xpb);
            }
            cix.AppendChild(xpb);
            xn.AppendChild(cix);
        }


        #endregion

    }
}
