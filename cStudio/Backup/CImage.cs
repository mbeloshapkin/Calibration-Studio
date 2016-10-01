using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;

namespace cStudio {
    /// <summary>
    /// Calibration Image
    /// </summary>
    class CImage {
        public Bitmap Bmp;
        public string Name;
        public string FileName;
        public string CamVendor, Camera, Lens;
        public bool DSLR { get { return Camera != Lens; } }
        public DateTime Time;
        public string SubSeconds;
        public Rational Exposure, Aperture, Distance, Focus;
        public string CamID{ get{ string r = Camera; if(DSLR) r += "/" + Lens; r += " f " + Focus + " mm"; return r; } }       

        public bool Load(string fn) {
            Bmp = (Bitmap)Bitmap.FromFile(fn);
            if (Bmp == null) return false;
            FileName = fn;
            Name = Path.GetFileName(fn);
            // process the EXIF
            CamVendor = ""; Camera = ""; Lens = "";
            int id, type, vi; string str; double fi; Rational R;
                foreach (PropertyItem pi in Bmp.PropertyItems) {
                    id = pi.Id; type = pi.Type;
                    str = "";                    
                    //foreach (byte b in pi.Value) str += (char)b;
                    switch (type) {
                        case 2:
                            foreach (byte b in pi.Value) if(b != 0) str += (char)b;
                            switch (id) {
                                case 272: Camera = str;
                                    break;
                                case 271: CamVendor = str;
                                    break;
                                case 36867:
                                    Time = ProcessDate(str);
                                    break;
                                case 37571:
                                    SubSeconds = str;
                                    break;
                            }
                            break;
                        case 1:
                        case 3:
                        case 4:
                            vi = ProcessTag(pi.Value, type); //[1] * 256 + pi.Value[0];
                            break;
                        case 5:
                            R = new Rational(pi.Value);
                            switch (id) {
                                case 33434: Exposure = R; break;
                                case 37378: Aperture = R; break;
                                case 37382: Distance = R; break;
                                case 37386: Focus = R; break;
                            }
                            break;
                    }
                    
                     int i = 1;
                }
                if (Lens.Length == 0) // Possible, it's the integrated lens
                    Lens = Camera;
            return true;
        }

        private int ProcessTag(byte[] val, int tag) {
            int r = 0, ct;
            switch (tag) {
                case 3: return val[1] * 256 + val[0];
                case 1: return (int)val[0];
                case 4:
                    for (ct = 3; ct > 0; ct--) {
                        r += val[ct];
                        r *= 256;
                    }
                    return r + val[0];
            }
            return -1;
        }

        private DateTime ProcessDate(string str) {
            DateTime d = new DateTime();
            if(str.Length != 19) return d;
            string tag = str.Substring(0, 4);
            d.AddYears(Convert.ToInt32(tag));
            tag = str.Substring(5, 2);
            d.AddMonths(Convert.ToInt32(tag));
            tag = str.Substring(8, 2);
            d.AddDays(Convert.ToInt32(tag));
            tag = str.Substring(11, 2);
            d.AddHours(Convert.ToInt32(tag));
            tag = str.Substring(14, 2);
            d.AddMinutes(Convert.ToInt32(tag));
            tag = str.Substring(17, 2);
            d.AddSeconds(Convert.ToInt32(tag));
            return d;
        }

    }
}
