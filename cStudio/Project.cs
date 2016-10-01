using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Collections;
using System.Text;
using System.Xml;
using System.IO;

namespace cStudio {
    class Project {
        public const string Version = "1.0";
        public string Name;
        public string Description;
        public Hashtable AllImages;
        public int ImgCount { get { if (Lens == null) return 0; return AllImages.Count; } }        
        public Camera Cam;        
        public CPLCalibrationImage this[string img] { get { return AllImages[img] as CPLCalibrationImage; } }
        public Lens Lens;
        public bool IsLensIntegrated { get { return Cam.Name == Lens.Name; } }

        public Project() {
            AllImages = new Hashtable();            
        }

        public bool AddImage(CPLCalibrationImage img) {
            if (AllImages.ContainsKey(img.Name)) {
                EH.Err("cStudio Project Error", "The image " + img.Name + " is already attached to the project.\r\n" +
                    "If you like to add this image, please rename or delete the existing one.");
                return false;
            }
                            
            if (ImgCount == 0) { // Initialize
                Name = img.Camera;
                Description = "Radial Distortion Model by Plumb Line Calibration";
            }
            else { // Check compatibility
                if (!Cam.IsCompatible(img)) {
                    EH.Err("cStudio Project Error", "The image " + img.Name + ", " + img.Camera + " can not be added to the project " + Name +
                        ". Camera body, Lens and Resolution should be the same for all used images.");
                    return false;
                }                
            }
            if (AllImages.Count == 0) CreateCamera(img);
            AllImages.Add(img.Name, img);
            return true;
        }

        private void CreateCamera(CPLCalibrationImage img) {
            Cam = new Camera();
            Cam.MatrixSize = new Pt();
            Lens = new Lens();
            Lens.AddImage(img);
            Cam.Name = img.Camera; Cam.Vendor = img.CamVendor;
            Cam.Width = img.Bmp.Width;
            Cam.Height = img.Bmp.Height;
            Cam.Serial = "0"; Cam.Vendor = img.CamVendor;
            Cam.IsDSLR = img.Camera != img.Lens;            
            //if (!Cam.IsDSLR) Cam.Lens.Vendor = Cam.Vendor;
        }

        public int Save(string fn) {
            XmlDocument xdoc = new XmlDocument();
            XmlElement root = xdoc.CreateElement("CCProject");
            XmlAttribute xa = xdoc.CreateAttribute("Name");
            xa.Value = Name;            
            root.Attributes.Append(xa);
            xa = xdoc.CreateAttribute("Version");
            xa.Value = Version;
            root.Attributes.Append(xa);
            XmlElement xdesc = xdoc.CreateElement("Description");
            xdesc.InnerText = Description;
            root.AppendChild(xdesc);
            Cam.AddTo(root);
            foreach (CPLCalibrationImage img in AllImages.Values) {
                img.AddTo(root);
            }
            xdoc.AppendChild(root);

            xdoc.Save(fn);
            return 0;
        }

    }
}
