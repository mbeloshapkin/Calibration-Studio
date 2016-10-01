namespace cStudio
{
    partial class FrmcStudio
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmcStudio));
            this.ssMain = new System.Windows.Forms.StatusStrip();
            this.tsMain = new System.Windows.Forms.ToolStrip();
            this.btLoadImage = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.btZoomIn = new System.Windows.Forms.ToolStripButton();
            this.btZoomOut = new System.Windows.Forms.ToolStripButton();
            this.msMain = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.printToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.imageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.teansformToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.propertiesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.calibrationDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addCalibrationImageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addVerticalLineToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addHorizontalLineToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.startDigitizeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.processDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.viewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.zoomInToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.zoomOutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.zoomTo11ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.fitWindowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.activationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Split = new System.Windows.Forms.SplitContainer();
            this.tvProject = new System.Windows.Forms.TreeView();
            this.cmImage = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.addVerticalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addHorisontalLineToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deleteLineToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.lbPos = new System.Windows.Forms.TextBox();
            this.miCamera = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.tsMain.SuspendLayout();
            this.msMain.SuspendLayout();
            this.Split.Panel1.SuspendLayout();
            this.Split.SuspendLayout();
            this.cmImage.SuspendLayout();
            this.SuspendLayout();
            // 
            // ssMain
            // 
            this.ssMain.Location = new System.Drawing.Point(0, 344);
            this.ssMain.Name = "ssMain";
            this.ssMain.Size = new System.Drawing.Size(695, 22);
            this.ssMain.TabIndex = 0;
            this.ssMain.Text = "statusStrip1";
            // 
            // tsMain
            // 
            this.tsMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.btLoadImage,
            this.toolStripSeparator3,
            this.btZoomIn,
            this.btZoomOut});
            this.tsMain.Location = new System.Drawing.Point(0, 24);
            this.tsMain.Name = "tsMain";
            this.tsMain.Size = new System.Drawing.Size(695, 25);
            this.tsMain.TabIndex = 1;
            this.tsMain.Text = "toolStrip1";
            // 
            // btLoadImage
            // 
            this.btLoadImage.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.btLoadImage.Image = ((System.Drawing.Image)(resources.GetObject("btLoadImage.Image")));
            this.btLoadImage.ImageTransparentColor = System.Drawing.Color.Silver;
            this.btLoadImage.Name = "btLoadImage";
            this.btLoadImage.Size = new System.Drawing.Size(23, 22);
            this.btLoadImage.Text = "Load Calibration Image";
            this.btLoadImage.Click += new System.EventHandler(this.loadToolStripMenuItem_Click);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 25);
            // 
            // btZoomIn
            // 
            this.btZoomIn.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.btZoomIn.Image = ((System.Drawing.Image)(resources.GetObject("btZoomIn.Image")));
            this.btZoomIn.ImageTransparentColor = System.Drawing.Color.White;
            this.btZoomIn.Name = "btZoomIn";
            this.btZoomIn.Size = new System.Drawing.Size(23, 22);
            this.btZoomIn.Text = "Zoom In";
            this.btZoomIn.Click += new System.EventHandler(this.zoomInToolStripMenuItem_Click);
            // 
            // btZoomOut
            // 
            this.btZoomOut.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.btZoomOut.Image = ((System.Drawing.Image)(resources.GetObject("btZoomOut.Image")));
            this.btZoomOut.ImageTransparentColor = System.Drawing.Color.White;
            this.btZoomOut.Name = "btZoomOut";
            this.btZoomOut.Size = new System.Drawing.Size(23, 22);
            this.btZoomOut.Text = "Zoom Out";
            this.btZoomOut.Click += new System.EventHandler(this.zoomOutToolStripMenuItem_Click);
            // 
            // msMain
            // 
            this.msMain.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.imageToolStripMenuItem,
            this.calibrationDataToolStripMenuItem,
            this.viewToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.msMain.Location = new System.Drawing.Point(0, 0);
            this.msMain.Name = "msMain";
            this.msMain.Size = new System.Drawing.Size(695, 24);
            this.msMain.TabIndex = 2;
            this.msMain.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.saveToolStripMenuItem1,
            this.openToolStripMenuItem,
            this.toolStripSeparator1,
            this.miCamera,
            this.toolStripSeparator5,
            this.printToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(53, 20);
            this.fileToolStripMenuItem.Text = "Project";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.newToolStripMenuItem.Text = "New";
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.saveToolStripMenuItem.Text = "Save";
            // 
            // saveToolStripMenuItem1
            // 
            this.saveToolStripMenuItem1.Name = "saveToolStripMenuItem1";
            this.saveToolStripMenuItem1.Size = new System.Drawing.Size(152, 22);
            this.saveToolStripMenuItem1.Text = "Save As ...";
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.openToolStripMenuItem.Text = "Open";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(149, 6);
            // 
            // printToolStripMenuItem
            // 
            this.printToolStripMenuItem.Name = "printToolStripMenuItem";
            this.printToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.printToolStripMenuItem.Text = "Print ...";
            // 
            // imageToolStripMenuItem
            // 
            this.imageToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadToolStripMenuItem,
            this.teansformToolStripMenuItem,
            this.saveToolStripMenuItem2,
            this.saveAsToolStripMenuItem,
            this.toolStripSeparator4,
            this.propertiesToolStripMenuItem});
            this.imageToolStripMenuItem.Name = "imageToolStripMenuItem";
            this.imageToolStripMenuItem.Size = new System.Drawing.Size(49, 20);
            this.imageToolStripMenuItem.Text = "Image";
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.loadToolStripMenuItem.Text = "Load";
            this.loadToolStripMenuItem.Click += new System.EventHandler(this.loadToolStripMenuItem_Click);
            // 
            // teansformToolStripMenuItem
            // 
            this.teansformToolStripMenuItem.Name = "teansformToolStripMenuItem";
            this.teansformToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.teansformToolStripMenuItem.Text = "Transform";
            // 
            // saveToolStripMenuItem2
            // 
            this.saveToolStripMenuItem2.Name = "saveToolStripMenuItem2";
            this.saveToolStripMenuItem2.Size = new System.Drawing.Size(152, 22);
            this.saveToolStripMenuItem2.Text = "Save";
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.saveAsToolStripMenuItem.Text = "Save as ...";
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(149, 6);
            // 
            // propertiesToolStripMenuItem
            // 
            this.propertiesToolStripMenuItem.Name = "propertiesToolStripMenuItem";
            this.propertiesToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.propertiesToolStripMenuItem.Text = "Properties ...";
            this.propertiesToolStripMenuItem.Click += new System.EventHandler(this.propertiesToolStripMenuItem_Click);
            // 
            // calibrationDataToolStripMenuItem
            // 
            this.calibrationDataToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addCalibrationImageToolStripMenuItem,
            this.addVerticalLineToolStripMenuItem,
            this.addHorizontalLineToolStripMenuItem,
            this.startDigitizeToolStripMenuItem,
            this.toolStripSeparator2,
            this.processDataToolStripMenuItem});
            this.calibrationDataToolStripMenuItem.Name = "calibrationDataToolStripMenuItem";
            this.calibrationDataToolStripMenuItem.Size = new System.Drawing.Size(96, 20);
            this.calibrationDataToolStripMenuItem.Text = "Calibration Data";
            // 
            // addCalibrationImageToolStripMenuItem
            // 
            this.addCalibrationImageToolStripMenuItem.Name = "addCalibrationImageToolStripMenuItem";
            this.addCalibrationImageToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.addCalibrationImageToolStripMenuItem.Text = "Add Calibration Image";
            // 
            // addVerticalLineToolStripMenuItem
            // 
            this.addVerticalLineToolStripMenuItem.Name = "addVerticalLineToolStripMenuItem";
            this.addVerticalLineToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.addVerticalLineToolStripMenuItem.Text = "Add Vertical Line";
            // 
            // addHorizontalLineToolStripMenuItem
            // 
            this.addHorizontalLineToolStripMenuItem.Name = "addHorizontalLineToolStripMenuItem";
            this.addHorizontalLineToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.addHorizontalLineToolStripMenuItem.Text = "Add Horizontal Line";
            // 
            // startDigitizeToolStripMenuItem
            // 
            this.startDigitizeToolStripMenuItem.Name = "startDigitizeToolStripMenuItem";
            this.startDigitizeToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.startDigitizeToolStripMenuItem.Text = "Start Digitize...";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(177, 6);
            // 
            // processDataToolStripMenuItem
            // 
            this.processDataToolStripMenuItem.Name = "processDataToolStripMenuItem";
            this.processDataToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.processDataToolStripMenuItem.Text = "Process Data";
            // 
            // viewToolStripMenuItem
            // 
            this.viewToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.zoomInToolStripMenuItem,
            this.zoomOutToolStripMenuItem,
            this.zoomTo11ToolStripMenuItem,
            this.fitWindowToolStripMenuItem});
            this.viewToolStripMenuItem.Name = "viewToolStripMenuItem";
            this.viewToolStripMenuItem.Size = new System.Drawing.Size(41, 20);
            this.viewToolStripMenuItem.Text = "View";
            // 
            // zoomInToolStripMenuItem
            // 
            this.zoomInToolStripMenuItem.Name = "zoomInToolStripMenuItem";
            this.zoomInToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.zoomInToolStripMenuItem.Text = "Zoom In";
            this.zoomInToolStripMenuItem.Click += new System.EventHandler(this.zoomInToolStripMenuItem_Click);
            // 
            // zoomOutToolStripMenuItem
            // 
            this.zoomOutToolStripMenuItem.Name = "zoomOutToolStripMenuItem";
            this.zoomOutToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.zoomOutToolStripMenuItem.Text = "Zoom Out";
            this.zoomOutToolStripMenuItem.Click += new System.EventHandler(this.zoomOutToolStripMenuItem_Click);
            // 
            // zoomTo11ToolStripMenuItem
            // 
            this.zoomTo11ToolStripMenuItem.Name = "zoomTo11ToolStripMenuItem";
            this.zoomTo11ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.zoomTo11ToolStripMenuItem.Text = "Zoom to 1:1";
            // 
            // fitWindowToolStripMenuItem
            // 
            this.fitWindowToolStripMenuItem.Name = "fitWindowToolStripMenuItem";
            this.fitWindowToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.fitWindowToolStripMenuItem.Text = "Fit Window";
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem,
            this.activationToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(40, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.aboutToolStripMenuItem.Text = "About";
            // 
            // activationToolStripMenuItem
            // 
            this.activationToolStripMenuItem.Name = "activationToolStripMenuItem";
            this.activationToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.activationToolStripMenuItem.Text = "Activation";
            // 
            // Split
            // 
            this.Split.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Split.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Split.Location = new System.Drawing.Point(0, 49);
            this.Split.Name = "Split";
            // 
            // Split.Panel1
            // 
            this.Split.Panel1.Controls.Add(this.tvProject);
            // 
            // Split.Panel2
            // 
            this.Split.Panel2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.Split.Size = new System.Drawing.Size(695, 295);
            this.Split.SplitterDistance = 217;
            this.Split.TabIndex = 3;
            // 
            // tvProject
            // 
            this.tvProject.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tvProject.ContextMenuStrip = this.cmImage;
            this.tvProject.Location = new System.Drawing.Point(4, 3);
            this.tvProject.Name = "tvProject";
            this.tvProject.Size = new System.Drawing.Size(208, 236);
            this.tvProject.TabIndex = 0;
            this.tvProject.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.tvProject_AfterSelect);
            // 
            // cmImage
            // 
            this.cmImage.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addVerticalToolStripMenuItem,
            this.addHorisontalLineToolStripMenuItem,
            this.deleteLineToolStripMenuItem});
            this.cmImage.Name = "cmImage";
            this.cmImage.Size = new System.Drawing.Size(167, 70);
            this.cmImage.Opening += new System.ComponentModel.CancelEventHandler(this.contextMenuStrip1_Opening);
            // 
            // addVerticalToolStripMenuItem
            // 
            this.addVerticalToolStripMenuItem.Enabled = false;
            this.addVerticalToolStripMenuItem.Name = "addVerticalToolStripMenuItem";
            this.addVerticalToolStripMenuItem.Size = new System.Drawing.Size(166, 22);
            this.addVerticalToolStripMenuItem.Text = "Add Vertical Line";
            this.addVerticalToolStripMenuItem.Click += new System.EventHandler(this.addVerticalToolStripMenuItem_Click);
            // 
            // addHorisontalLineToolStripMenuItem
            // 
            this.addHorisontalLineToolStripMenuItem.Enabled = false;
            this.addHorisontalLineToolStripMenuItem.Name = "addHorisontalLineToolStripMenuItem";
            this.addHorisontalLineToolStripMenuItem.Size = new System.Drawing.Size(166, 22);
            this.addHorisontalLineToolStripMenuItem.Text = "Add Horizontal Line";
            this.addHorisontalLineToolStripMenuItem.Click += new System.EventHandler(this.addHorisontalLineToolStripMenuItem_Click);
            // 
            // deleteLineToolStripMenuItem
            // 
            this.deleteLineToolStripMenuItem.Enabled = false;
            this.deleteLineToolStripMenuItem.Name = "deleteLineToolStripMenuItem";
            this.deleteLineToolStripMenuItem.Size = new System.Drawing.Size(166, 22);
            this.deleteLineToolStripMenuItem.Text = "Delete Line";
            // 
            // lbPos
            // 
            this.lbPos.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.lbPos.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.lbPos.Location = new System.Drawing.Point(563, 27);
            this.lbPos.Name = "lbPos";
            this.lbPos.ReadOnly = true;
            this.lbPos.Size = new System.Drawing.Size(120, 20);
            this.lbPos.TabIndex = 4;
            this.lbPos.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // miCamera
            // 
            this.miCamera.Name = "miCamera";
            this.miCamera.Size = new System.Drawing.Size(152, 22);
            this.miCamera.Text = "Camera...";
            this.miCamera.Click += new System.EventHandler(this.miCamera_Click);
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(149, 6);
            // 
            // FrmcStudio
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(695, 366);
            this.Controls.Add(this.lbPos);
            this.Controls.Add(this.Split);
            this.Controls.Add(this.tsMain);
            this.Controls.Add(this.ssMain);
            this.Controls.Add(this.msMain);
            this.DoubleBuffered = true;
            this.MainMenuStrip = this.msMain;
            this.Name = "FrmcStudio";
            this.Text = "AeroGIS Calibration Studio";
            this.tsMain.ResumeLayout(false);
            this.tsMain.PerformLayout();
            this.msMain.ResumeLayout(false);
            this.msMain.PerformLayout();
            this.Split.Panel1.ResumeLayout(false);
            this.Split.ResumeLayout(false);
            this.cmImage.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.StatusStrip ssMain;
        private System.Windows.Forms.ToolStrip tsMain;
        private System.Windows.Forms.ToolStripButton btLoadImage;
        private System.Windows.Forms.MenuStrip msMain;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem imageToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.SplitContainer Split;
        private System.Windows.Forms.TreeView tvProject;
        private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem teansformToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem activationToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem printToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem calibrationDataToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem viewToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addCalibrationImageToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addVerticalLineToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addHorizontalLineToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem startDigitizeToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripMenuItem processDataToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem zoomInToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem zoomOutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem zoomTo11ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem fitWindowToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripButton btZoomIn;
        private System.Windows.Forms.ToolStripButton btZoomOut;
        private System.Windows.Forms.TextBox lbPos;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripMenuItem propertiesToolStripMenuItem;
        private System.Windows.Forms.ContextMenuStrip cmImage;
        private System.Windows.Forms.ToolStripMenuItem addVerticalToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addHorisontalLineToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem deleteLineToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem miCamera;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
    }
}

