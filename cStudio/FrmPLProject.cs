using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

using cStudio.Properties;

namespace cStudio {
    partial class FrmPLProject : Form {
        public Project Prj;
        public string[] Files;
        public FrmPLProject() {
            InitializeComponent();
            Prj = null;
            btOK.Enabled = false;
        }

        private void btCancel_Click(object sender, EventArgs e) {
            DialogResult = DialogResult.Cancel;
            Close();
        }

        private void btOK_Click(object sender, EventArgs e) {
            DialogResult = DialogResult.OK;
            this.Close();
            //FrmBody fb = new FrmBody();
            //if(fb.ShowDialog() == DialogResult.Cancel) this.Show();
        }

        private void btSelect_Click(object sender, EventArgs e) {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Title = "Select one or more Calibration Images";
            ofd.Multiselect = true;
            if (Settings.Default.LastImagePath.Length > 0) ofd.InitialDirectory = Settings.Default.LastImagePath;
            else ofd.InitialDirectory = "c:\\";
            ofd.Filter = "Bitmap files (*.bmp)|*.bmp|Jpeg files (*.jpg)|*.jpg|All supported files (*.bmp,*.jpg,*.png,*.gif)|*.bmp;*.jpg;*.png;*.gif";
            ofd.FilterIndex = 2;
            ofd.RestoreDirectory = true;
            if (ofd.ShowDialog() == DialogResult.OK) {
                string[] files = ofd.FileNames;
                if (files.Length == 0) return;
                Cursor old = Cursor;
                Cursor = Cursors.WaitCursor;

                Settings.Default.LastImagePath = Path.GetDirectoryName(files[0]);
                grdImages.Rows.Clear();

                CPLCalibrationImage first = new CPLCalibrationImage();
                first.Load(files[0]);
                int skipped = 0;
                // Create project
                Prj = new Project();
                if (!Prj.AddImage(first)) return;

                object[] row = new object[2];
                row[0] = Path.GetFileName(first.FileName);
                row[1] = first.Focus.ToString();
                grdImages.Rows.Add(row);

                for(int ct = 1; ct < files.Length; ct++) {
                    try {
                        CPLCalibrationImage img = new CPLCalibrationImage();
                        img.Load(files[ct]);
                        if (!Prj.AddImage(img)) skipped++;
                        else {
                            row = new object[2];
                            row[0] = Path.GetFileName(img.FileName);
                            row[1] = img.Focus.ToString();
                            grdImages.Rows.Add(row);
                        }
                    }
                    catch (Exception ex) {
                        EH.Err("Failed to add Image", files[ct] +
                            " can not be added to the project: " + ex.Message);
                        skipped++;
                    }
                }
                Cursor = old;
                btOK.Enabled = files.Length - skipped > 0;
                // Ajust column
                int noscrollcount = (int)Math.Floor((double)grdImages.ClientSize.Height / (grdImages.RowTemplate.Height + 1));
                int ColumnWidth;
                if (grdImages.Rows.Count > noscrollcount)
                    ColumnWidth = (int)(grdImages.ClientSize.Width - 18) / 2;
                else
                    ColumnWidth = (int)Math.Floor((double)(grdImages.ClientSize.Width - 2) / 2.0);
                foreach (DataGridViewColumn cl in grdImages.Columns) cl.Width = ColumnWidth;
            }// Open files OK

        }

    }
}
