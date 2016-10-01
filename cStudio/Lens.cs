using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;
using System.Xml;

namespace cStudio {
    class Lens {
        private Camera Body;
        public enum FocusSource { Calibration, Documentation, ImageFile }
        public string Name;
        public string Label { get { return Name + " f = " + FocalLength.ToString(); } }
        // It's possible the user will calibrate several lenses of same type, for example just for testing
        // We must prevent the wrong results.
        public string Signature { get { return Body.Signature + Name + Serial + Vendor + FocalLength.ToString(); } }
        // Defines is calibration image compatible with the lens        
        public string Vendor;
        public string Serial;
        public bool IsFix { get { return ImageSets.Count <= 1; } }
        public double FocalLength;
        public FocusSource FocusSrc;                
        public CPLCalibrationImage this[string img] { get { return Images[img] as CPLCalibrationImage; } }
        public ImgIndexer Images;
        private int _ImgCount;
        public int ImgCount { get { return _ImgCount; } }
        public Hashtable ImageSets;


        public Lens(Camera ACam) {
            ImageSets = new Hashtable(); Body = ACam; _ImgCount = 0; 
            Images = new ImgIndexer(this);
        }

        public Lens() { ImageSets = new Hashtable(); _ImgCount = 0;  Images = new ImgIndexer(this); }

        public Lens Clone() {
            Lens r = new Lens();
            r.Name = Name; r.Vendor = Vendor; r.Serial = Serial; 
            r.FocalLength = FocalLength; r.FocusSrc = FocusSrc;
            return r;
        }

        public bool AddImage(CPLCalibrationImage img) {                        
            if (ContainsImage(img.Name)) {
                    EH.Err("cStudio Project Error", "The image " + img.Name + " is already attached to the project.\r\n" +
                        "If you like to add this image, please rename or delete the existing one.");
                    return false;
            }            
            if (ImgCount == 0) { // Initialize
                Name = img.Lens;
                //Vendor = img.L                
            } else { // Check compatibility
                if (Name != img.Lens || Body.Name != img.Camera) {
                    EH.Err("cStudio Project Error", "The image " + img.Name + ", " + img.Camera + " can not be added to the project " + Name +
                        ". Camera and Lens should be the same for all used images.");
                    return false;
                }
            }
            if (ImageSets.ContainsKey(img.Focus)) {
                ImageSet ist = ImageSets[img.Focus] as ImageSet;
                ist.Add(img);
            } else {
                ImageSet ist = new ImageSet();
                ist.Add(img);
                ImageSets.Add(img.Focus, ist);
            }
            _ImgCount++;
            return true;
        }

        public bool ContainsImage(string AName){
            foreach(ImageSet ist in ImageSets.Values) if(ist.Contains(AName)) return true;
            return false;
        }                

        #region XML
        public void AddTo(XmlNode xn) {
            XmlDocument xdoc = xn.OwnerDocument;
            XmlElement xl = xdoc.CreateElement("Lens");
            XmlAttribute xa = xdoc.CreateAttribute("Name");
            if (Name == null) Name = "Built in";
            xa.Value = Name;
            xl.Attributes.Append(xa);
            xa = xdoc.CreateAttribute("Vendor");
            if (Vendor == null) Vendor = "Unknown";
            xa.Value = Vendor;
            xl.Attributes.Append(xa);
            XmlNode xSerial = xdoc.CreateElement("Serial");
            if (Serial == null) Serial = "0";
            xSerial.InnerText = Serial;
            xl.AppendChild(xSerial);
            XmlNode xFocus = xdoc.CreateElement("Focus");
            XmlAttribute xFix = xdoc.CreateAttribute("Fixed");
            xFix.Value = IsFix.ToString();
            xFocus.Attributes.Append(xFix);
            XmlAttribute xLen = xdoc.CreateAttribute("FocalLength");
            xLen.Value = FocalLength.ToString();
            xFocus.Attributes.Append(xLen);
            XmlAttribute xSrc = xdoc.CreateAttribute("Source");
            xSrc.Value = FocusSrc.ToString();
            xFocus.Attributes.Append(xSrc);
            xl.AppendChild(xFocus);
            xn.AppendChild(xl);
        }

        public void Create(XmlNode xn) {
            Name = xn.Attributes["Name"].Value;
            Vendor = xn.Attributes["Vendor"].Value;
            Serial = xn.SelectSingleNode("Serial").Value;
            XmlNode xfocus = xn.SelectSingleNode("Focus");
            //IsFix = Convert.ToBoolean(xfocus.Attributes["Fixed"].Value);
            FocalLength = Convert.ToDouble(xfocus.Attributes["FocalLength"].Value);
            FocusSrc = (FocusSource)Enum.Parse(typeof(FocusSource), xfocus.Attributes["Source"].Value);
        }
        #endregion

        #region Comparison
        public override int GetHashCode() {                            
            return Signature.GetHashCode();
        }

        public override bool Equals(object obj) {            
            if (obj is Lens) return Signature == (obj as Lens).Signature;
            return false;
        }        

        public static bool operator ==(Lens l1, Lens l2){
            object o1 = l1 as object; object o2 = l2 as object;
            if(o1 == null && o2 == null) return true;
            return l1 is Lens && (l1 as Lens).Equals(l2);            
        }

        public static bool operator !=(Lens l1, Lens l2) {
            return !(l1 == l2);
        }
        #endregion

        public class ImgIndexer {
            private Lens L;

            public ImgIndexer(Lens ALens) {
                L = ALens;
            }

            public int Count { get { return L.ImgCount; } }

            public CPLCalibrationImage this[string AName] {
                get {
                    foreach (ImageSet ist in L.ImageSets.Values) if (ist.Contains(AName)) return ist[AName];
                    return null;
                }
            }

        }

    }
}
