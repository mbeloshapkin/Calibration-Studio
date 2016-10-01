using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace cStudio {
    partial class frmCamera : Form {
        public Camera Cam;
        public frmCamera() {
            InitializeComponent();
        }

        public void Setup(Camera c) {
            Cam = c;
            tbxCam.Text = Cam.Name; tbxCamSerial.Text = Cam.Serial; tbxCamVendor.Text = Cam.Vendor;
            tbxHeight_mm.Text = Cam.MatrixSize.y.ToString(); tbxWidth_mm.Text = Cam.MatrixSize.y.ToString();
            tbxHeight_pix.Text = Cam.Height.ToString(); tbxWidth_pix.Text = Cam.Width.ToString();
            tbxLens.Text = Cam.Lens.Name; tbxLensSerial.Text = Cam.Lens.Serial;
            tbxLensVendor.Text = Cam.Lens.Vendor;
            cbxDSLR.Checked = Cam.IsDSLR;
            cbxFix.Checked = Cam.Lens.IsFix;
            tbxFocus.Text = Cam.Lens.FixFocus.ToString();
            UpdateInfo();
        }

        private void UpdateInfo() {            
                tbxLens.Enabled = cbxDSLR.Checked;
                tbxLensVendor.Enabled = cbxDSLR.Checked;
                tbxLensSerial.Enabled = cbxDSLR.Checked;            
        }

        private void cbxDSLR_CheckedChanged(object sender, EventArgs e) {
            UpdateInfo();
        }

        private void cbxFix_CheckedChanged(object sender, EventArgs e) {
            if (cbxFix.Checked) {
                tbxFocus.Enabled = true;
                if (Cam.Lens.FixFocus > 0) tbxFocus.Text = Cam.Lens.FixFocus.ToString();
                else tbxFocus.Text = "Unknown";
            }
            else {
                tbxFocus.Text = "Variable"; tbxFocus.Enabled = false;
            }
        }

    }
}