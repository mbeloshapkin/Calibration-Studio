using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;

namespace cStudio {
    /// <summary>
    /// The set of images for a lens taken at the same focal length
    /// </summary>
    class ImageSet {
        private ArrayList Images;
        private ArrayList ImgNames;
        private double _Focus;
        public double Focus { get { return _Focus; } }
        public string StrFocus { get { return _Focus.ToString(); } }
        public CPLCalibrationImage this[int idx] { get { return Images[idx] as CPLCalibrationImage; } }
        public int Count { get { return Images.Count; } }
        public CPLCalibrationImage this[string AName] { get { return Images[ImgNames.IndexOf(AName)] as CPLCalibrationImage; } }

        public ImageSet() {
            Images = new ArrayList(); ImgNames = new ArrayList();
        }

        public bool Add(CPLCalibrationImage img) {
            if (Count == 0) { ImgNames.Add(img.Name); Images.Add(img); _Focus = img.Focus; return true; }
            if (_Focus == img.Focus) { ImgNames.Add(img.Name);  Images.Add(img); return true; }
            return false;
        }

        public void Remove(string AName) {
            if(ImgNames.Contains(AName)){
                Images.Remove(this[AName]);
                ImgNames.Remove(AName);
            }                
        }

        public bool Contains(string AName) { return ImgNames.Contains(AName); }

    }
}
