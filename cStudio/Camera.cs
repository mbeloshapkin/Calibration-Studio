using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace cStudio {
    class Camera {
        private string NameAlias = "";
        private string _Name = "";
        // The name can be given by the user, but we need for name as it is in exif.
        public string Name { get { return _Name; } set { if (NameAlias == "") NameAlias = value; _Name = value; } }
        private string VendorAlias = "";
        private string _Vendor = "";
        public string Vendor { get { return _Vendor; } set { if (VendorAlias == "") VendorAlias = value; _Vendor = value; } }
        private string SerialAlias = "";
        private string _Serial = "";
        public string Serial{ get { return _Serial; } set { if (SerialAlias == "") SerialAlias = value; _Serial = value; } }
        public bool IsDSLR;
        public Pt MatrixSize; // In mm
        public int Width;
        public int Height;
        public string Signature { get { return NameAlias + Vendor + Serial; } }

        public bool IsCompatible(CPLCalibrationImage img) {
            return img.Camera == _Name &&
            img.CamVendor == _Vendor &&
            Width == img.Bmp.Width && Height == img.Bmp.Height;
        }

        public Camera Clone() {
            Camera r = new Camera();
            r.Name = Name;
            r.Vendor = Vendor; r.Serial = Serial; r.IsDSLR = IsDSLR;
            r.MatrixSize = MatrixSize.Clone();
            r.Width = Width;
            r.Height = Height;            
            return r;
        }

        public void AddTo(XmlNode xn) {
            XmlDocument xdoc = xn.OwnerDocument;
            XmlElement xc = xdoc.CreateElement("Camera");
            XmlAttribute xa = xdoc.CreateAttribute("Name");
            xa.Value = Name;
            xc.Attributes.Append(xa);
            xa = xdoc.CreateAttribute("DSLR"); xa.Value = IsDSLR.ToString();
            xc.Attributes.Append(xa);
            XmlElement xVendor = xdoc.CreateElement("Vendor");
            xVendor.InnerText = Vendor;
            xc.AppendChild(xVendor);
            XmlElement xSerial = xdoc.CreateElement("Serial");
            xSerial.InnerText = Serial;
            xc.AppendChild(xVendor);
            XmlElement xmatrix = xdoc.CreateElement("Matrix");
            xa = xdoc.CreateAttribute("Width"); xa.Value = MatrixSize.x.ToString();
            xmatrix.Attributes.Append(xa);
            xa = xdoc.CreateAttribute("Height"); xa.Value = MatrixSize.y.ToString();
            xmatrix.Attributes.Append(xa);
            xc.AppendChild(xmatrix);
            //Lens.AddTo(xc);           
            xn.AppendChild(xc);
        }

        public void Create(XmlNode xn) {
            Name = xn.Attributes["Name"].Value;
            IsDSLR = Convert.ToBoolean(xn.Attributes["DSLR"].Value);
            Vendor = xn.SelectSingleNode("Vendor").Value;
            Serial = xn.SelectSingleNode("Serial").Value;
            XmlNode xmatrix = xn.SelectSingleNode("Matrix");
            MatrixSize = new Pt();
            MatrixSize.x = Convert.ToDouble(xmatrix.Attributes["Widht"].Value);
            MatrixSize.y = Convert.ToDouble(xmatrix.Attributes["Height"].Value);
            //Lens = new Lens();
            //Lens.Create(xn.SelectSingleNode("Lens"));
        }

    }
}
