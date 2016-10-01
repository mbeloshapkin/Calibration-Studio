using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Imaging;

namespace cStudio {
    partial class frmImgProps : Form {
        public frmImgProps() {
            InitializeComponent();
        }

        public CImage Img;

        private void frmImgProps_Load(object sender, EventArgs e) {
            lbCamera.Text = Img.Camera;
            //lbSerial.Text = Img.CamID;
            lbLens.Text = Img.Lens;
            lbFocus.Text = Img.Focus.ToString();
            if (Img.Aperture != null) {
                lbApp.Text = Img.Aperture.ToString();
            }
            else lbApp.Text = "Unknown";
            lbFile.Text = Img.FileName;
            /*
            if (Img != null) {
                int id, type, vi; string str; double fi; Rational R;
                foreach (PropertyItem pi in Img.PropertyItems) {
                    id = pi.Id; type = pi.Type;
                    str = "";                    
                    //foreach (byte b in pi.Value) str += (char)b;
                    switch (type) {
                        case 2:
                            foreach (byte b in pi.Value) if(b != 0) str += (char)b;
                            switch (id) {
                                case 272: lbCamera.Text = str;
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
                            break;
                    }
                    
                     int i = 1;
                }
            }*/
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

        //private double ProcessRational(byte[]

    }
}