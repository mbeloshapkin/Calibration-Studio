using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using cStudio.Properties;

namespace cStudio
{
    public partial class FrmcStudio: Form {
        private frmImage fImg;
        private Project Prj;
        private CPLCalibrationImage Image;        

        public FrmcStudio() {
            InitializeComponent();
            fImg = new frmImage();
            fImg.Parent = Split.Panel2;
            fImg.Anchor = AnchorStyles.Right | AnchorStyles.Left | AnchorStyles.Top | AnchorStyles.Bottom;
            fImg.Zoom = 1.0;
            //fImg.Bmp = new Bitmap(2, 2);
            fImg.lbPos = lbPos;
            Prj = new Project();
            UpdateTree();
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e) {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            if (Settings.Default.LastPath.Length > 0) openFileDialog.InitialDirectory = Settings.Default.LastPath;            
            else  openFileDialog.InitialDirectory = "c:\\";
            openFileDialog.Filter = "Bitmap files (*.bmp)|*.bmp|Jpeg files (*.jpg)|*.jpg|All supported files (*.bmp,*.jpg,*.png,*.gif)|*.bmp;*.jpg;*.png;*.gif";
            openFileDialog.FilterIndex = 2;
            openFileDialog.RestoreDirectory = true;

            if (DialogResult.OK == openFileDialog.ShowDialog()) {                
                CPLCalibrationImage img = new CPLCalibrationImage();
                img.Load(openFileDialog.FileName);
                //fImg.Bmp = (Bitmap)Bitmap.FromFile(openFileDialog.FileName, false);
                if(!Prj.AddImage(img)) return;                
                UpdateTree();
                fImg.Bmp = img.Bmp;
                Image = img;
                // Enable context menu
                foreach (ToolStripMenuItem mi in cmImage.Items) mi.Enabled = true;

                Settings.Default.LastPath = openFileDialog.FileName;
                Settings.Default.Save();
                fImg.AutoScroll = true;
                fImg.AutoScrollMinSize = new Size((int)(fImg.Bmp.Width * fImg.Zoom), 
                    (int)(fImg.Bmp.Height * fImg.Zoom));
                fImg.Zoom = 1.0;
                fImg.Dock = DockStyle.Fill;
                fImg.OnImgClick = OnImgClick;
                fImg.Show();                
                fImg.Invalidate();
            }
        }
        
        private void zoomInToolStripMenuItem_Click(object sender, EventArgs e) {
            fImg.Zoom *= 2.0;            
        }

        private void zoomOutToolStripMenuItem_Click(object sender, EventArgs e) {
            fImg.Zoom /= 2.0;            
        }

        private void propertiesToolStripMenuItem_Click(object sender, EventArgs e) {
            frmImgProps fip = new frmImgProps();
            fip.Img = Image;
            fip.ShowDialog(this);
        }

        private void UpdateTree() {
            tvProject.Nodes.Clear();
            tvProject.BeginUpdate();
            if (Prj.ImgCount == 0) {
                this.Text = "AeroGIS Calibration Studio";
                tvProject.Nodes.Add("No calibration data ...");
                return;
            }
            else {
                foreach (CImage img in Prj.Images.Values) {
                    tvProject.Nodes.Add(img.Name);
                }
                this.Text = "AeroGIS Calibration Studio: " + Prj.Name;
            }
            foreach (TreeNode n in tvProject.Nodes) {
                foreach (PlumbLine pl in Prj[n.Text].Lines.Values) n.Nodes.Add(pl.Name);
            }
            tvProject.EndUpdate();
            tvProject.Refresh();
        }

        private void contextMenuStrip1_Opening(object sender, CancelEventArgs e) {

        }

        private void tvProject_AfterSelect(object sender, TreeViewEventArgs e) {
            if (Prj.ImgCount == 0) return;
            string str = e.Node.Text;            
            Image = Prj[str];
            if (Image != null) { // The root node
                fImg.Bmp = Image.Bmp;
                fImg.Invalidate();
            }
        }

        private void addVerticalToolStripMenuItem_Click(object sender, EventArgs e) {
            Prj[Image.Name].Add(true); UpdateTree();             
        }

        private void addHorisontalLineToolStripMenuItem_Click(object sender, EventArgs e) {
            Prj[Image.Name].Add(false); UpdateTree();
        }

        private void OnImgClick(double x, double y) {
            Pt p1 = new Pt(x, y);
        }

        private void miCamera_Click(object sender, EventArgs e) {
            frmCamera fc = new frmCamera();
            fc.Setup(Prj.Cam.Clone());
            if (fc.ShowDialog() == DialogResult.OK) Prj.Cam = fc.Cam;
        }
       
    }
}