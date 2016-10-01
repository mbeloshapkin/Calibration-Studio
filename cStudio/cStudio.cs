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
    partial class FrmcStudio: Form {
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
            if (Settings.Default.LastImagePath.Length > 0) openFileDialog.InitialDirectory = Settings.Default.LastImagePath;            
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
                fImg.Img = img;// Bmp = img.Bmp;
                Image = img;
                // Enable context menu
                foreach (ToolStripMenuItem mi in cmImage.Items) mi.Enabled = true;

                Settings.Default.LastImagePath = openFileDialog.FileName;
                Settings.Default.Save();
                fImg.AutoScroll = true;
                fImg.AutoScrollMinSize = new Size((int)(fImg.Img.Bmp.Width * fImg.Zoom), 
                    (int)(fImg.Img.Bmp.Height * fImg.Zoom));
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
            TreeNode nRoot = null;
            if (Prj.ImgCount == 0) {
                this.Text = "AeroGIS Calibration Studio";
                nRoot = tvProject.Nodes.Add("<Create New Project>");
                return;
            }
            else {
                nRoot = tvProject.Nodes.Add(Prj.Name);
                TreeNode nLens;
                if(Prj.IsLensIntegrated) nLens = nRoot;
                else nLens = nRoot.Nodes.Add(Prj.Lens.Name);
                foreach(Rational focus in Prj.Lens.ImageSets.Keys){
                    ImageSet ist = Prj.Lens.ImageSets[focus] as ImageSet;
                    TreeNode nSet = nLens.Nodes.Add("f = " + focus.ToString() + " mm");
                    nSet.Tag = ist;
                    for (int ct = 0; ct < ist.Count; ct++) {
                        TreeNode nImg = nSet.Nodes.Add(ist[ct].Name);
                        foreach(PlumbLine pl in ist[ct].Lines.Values){
                            TreeNode line_node = nImg.Nodes.Add(pl.Name);
                            line_node.Text = pl.Name + " (" + pl.Count.ToString() + " Points)";
                            line_node.Tag = pl;
                        }       
                    }                                        
                }
                this.Text = "AeroGIS Calibration Studio: " + Prj.Name;
            }            
            nRoot.ExpandAll();
            tvProject.EndUpdate();
            tvProject.Refresh();            
        }

        private void tvProject_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e) {
            // If Create new
            if (e.Node.Text == "<Create New Project>") {  // There are no existing project. // Run wizard.
                FrmPLProject flp = new FrmPLProject();
                if (flp.ShowDialog() == DialogResult.OK) {
                    Prj = flp.Prj;
                    UpdateTree();
                    return;
                }
            }
            // Just click on existing image or line
            if (Prj.ImgCount == 0) return;
            string str = e.Node.Text;
            if (e.Node.Tag is CImage){
                Image = Prj[str];
                if (Image != null){ // The root node
                    fImg.Img = Image;
                    fImg.Invalidate();
                }
                miDeleteLine.Visible = false;
                tslInfo.Text = "Calibration Image " + Image.FileName;
            }
            if (e.Node.Tag is PlumbLine) {
                miDeleteLine.Visible = true;
                PlumbLine pl = e.Node.Tag as PlumbLine;
                string info;
                if(pl.IsVertical) info = "Vertical Calibration Line";
                else info = "Horisontal Calibration Line";
                tslInfo.Text = info + ", " + pl.Count.ToString() + " Points";
            }
        }

        private void miAddVLine_Click(object sender, EventArgs e) {
            Prj[Image.Name].Add(true); UpdateTree();             
        }

        private void miAddHLine_Click(object sender, EventArgs e) {
            Prj[Image.Name].Add(false); UpdateTree();
        }

        private void OnImgClick(double x, double y) {            
            TreeNode tn = tvProject.SelectedNode;
            if (tn != null && tn.Tag != null && tn.Tag is PlumbLine) {
                Pt p1 = new Pt(x, y);
                PlumbLine pl = tn.Tag as PlumbLine; 
                pl.Add(p1);
                tn.Text = pl.Name + " (" + pl.Count.ToString() + " Points)";
                fImg.Invalidate();
                //tvProject.Refresh();
            }
        }

        #region Menu

        private void miCamera_Click(object sender, EventArgs e) {
            frmCamera fc = new frmCamera();
            fc.Setup(Prj.Cam.Clone());
            if (fc.ShowDialog() == DialogResult.OK) Prj.Cam = fc.Cam;
        }

        private void miDeleteLine_Click(object sender, EventArgs e) {
            TreeNode tn = tvProject.SelectedNode;
            if (tn.Tag is PlumbLine) {
                TreeNode imgn = tn.Parent;
                CPLCalibrationImage img = imgn.Tag as CPLCalibrationImage;
                img.Remove((tn.Tag as PlumbLine).Name);
                tvProject.Nodes.Remove(tn);
            }
        }

        private void miSave_Click(object sender, EventArgs e) {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.DefaultExt = "ccp";
            sfd.Filter = "AeroGIS Camera Calibration Projects (*.ccp)|*.ccp";
            sfd.InitialDirectory = Settings.Default.LastProject;
            if (sfd.ShowDialog() == DialogResult.OK) {
                Prj.Save(sfd.FileName);
                Settings.Default.LastProject = sfd.FileName;
            }

        }
        #endregion

        private void FrmcStudio_FormClosed(object sender, FormClosedEventArgs e) {
            Settings.Default.Save();
        }

        private void miNewProject_Click(object sender, EventArgs e) {
            FrmPLProject flp = new FrmPLProject();
            if (flp.ShowDialog() == DialogResult.OK) {
                Prj = flp.Prj;
                UpdateTree();
            }
        }        
       
    }
}