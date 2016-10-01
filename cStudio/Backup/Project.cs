using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Collections;
using System.Text;

namespace cStudio {
    class Project {
        public string Name;
        public string Description;
        public Hashtable Images;
        public int ImgCount { get { return Images.Count; } }        
        public Camera Cam;        
        public CPLCalibrationImage this[string img] { get { return Images[img] as CPLCalibrationImage; } }

        public Project() {
            Images = new Hashtable();
        }

        public bool AddImage(CPLCalibrationImage img) {
            if (Images == null) Images = new Hashtable();
            else {
                if(Images.ContainsKey(img.Name)){
                    EH.Err("cStudio Project Error", "The image " + img.Name + " is already attached to the project.\r\n" +
                        "If you like to add this image, please rename or delete the existing one.");
                    return false;
                }
            }
            if (ImgCount == 0) { // Initialize
                Name = img.CamID;
                Description = "Radial Distortion Model by Plumb Line Calibration";
            }
            else { // Check compatibility
                if (Name != img.CamID) {
                    EH.Err("cStudio Project Error", "The image " + img.Name + ", " + img.CamID + " can not be added to the project " + Name +
                        ". Camera, Lens and Focal Length should be the same for all used images.");
                    return false;
                }             
            }
            if (Images.Count == 0) CreateCamera(img);
            Images.Add(img.Name, img);
            return true;
        }

        private void CreateCamera(CImage img) {
            Cam = new Camera();
            Cam.MatrixSize = new Pt();
            Cam.Lens = new Lens();
            Cam.Name = img.Camera; Cam.Vendor = img.CamVendor;
            Cam.Width = img.Bmp.Width;
            Cam.Height = img.Bmp.Height;
            Cam.Serial = ""; Cam.Vendor = img.CamVendor;
            Cam.IsDSLR = img.Camera == img.Lens;
            Cam.Lens.FixFocus = img.Focus;
            Cam.Lens.IsFix = true;
        }


    }
}
