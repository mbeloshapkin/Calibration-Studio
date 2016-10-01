namespace cStudio {
    partial class FrmPLProject {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmPLProject));
            this.btOK = new System.Windows.Forms.Button();
            this.btCancel = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btSelect = new System.Windows.Forms.Button();
            this.grdImages = new System.Windows.Forms.DataGridView();
            this.clFile = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.clFocus = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.grdImages)).BeginInit();
            this.SuspendLayout();
            // 
            // btOK
            // 
            this.btOK.Location = new System.Drawing.Point(405, 231);
            this.btOK.Name = "btOK";
            this.btOK.Size = new System.Drawing.Size(75, 23);
            this.btOK.TabIndex = 0;
            this.btOK.Text = "OK";
            this.btOK.UseVisualStyleBackColor = true;
            this.btOK.Click += new System.EventHandler(this.btOK_Click);
            // 
            // btCancel
            // 
            this.btCancel.Location = new System.Drawing.Point(324, 231);
            this.btCancel.Name = "btCancel";
            this.btCancel.Size = new System.Drawing.Size(75, 23);
            this.btCancel.TabIndex = 1;
            this.btCancel.Text = "Cancel";
            this.btCancel.UseVisualStyleBackColor = true;
            this.btCancel.Click += new System.EventHandler(this.btCancel_Click);
            // 
            // textBox1
            // 
            this.textBox1.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox1.Location = new System.Drawing.Point(12, 66);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(245, 68);
            this.textBox1.TabIndex = 2;
            this.textBox1.Text = resources.GetString("textBox1.Text");
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(222, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Please, select one or more calibration images.";
            // 
            // btSelect
            // 
            this.btSelect.Location = new System.Drawing.Point(65, 190);
            this.btSelect.Name = "btSelect";
            this.btSelect.Size = new System.Drawing.Size(114, 23);
            this.btSelect.TabIndex = 4;
            this.btSelect.Text = "Select Images...";
            this.btSelect.UseVisualStyleBackColor = true;
            this.btSelect.Click += new System.EventHandler(this.btSelect_Click);
            // 
            // grdImages
            // 
            this.grdImages.AllowUserToAddRows = false;
            this.grdImages.AllowUserToDeleteRows = false;
            this.grdImages.AllowUserToResizeRows = false;
            this.grdImages.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.grdImages.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.clFile,
            this.clFocus});
            this.grdImages.Location = new System.Drawing.Point(263, 12);
            this.grdImages.Name = "grdImages";
            this.grdImages.ReadOnly = true;
            this.grdImages.RowHeadersVisible = false;
            this.grdImages.RowTemplate.Height = 18;
            this.grdImages.Size = new System.Drawing.Size(217, 201);
            this.grdImages.TabIndex = 5;
            // 
            // clFile
            // 
            this.clFile.HeaderText = "File";
            this.clFile.Name = "clFile";
            this.clFile.ReadOnly = true;
            // 
            // clFocus
            // 
            this.clFocus.HeaderText = "Focus, mm";
            this.clFocus.Name = "clFocus";
            this.clFocus.ReadOnly = true;
            // 
            // FrmPLProject
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(492, 266);
            this.Controls.Add(this.grdImages);
            this.Controls.Add(this.btSelect);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.btCancel);
            this.Controls.Add(this.btOK);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FrmPLProject";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "New Project: Add Calibration Images";
            ((System.ComponentModel.ISupportInitialize)(this.grdImages)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btOK;
        private System.Windows.Forms.Button btCancel;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btSelect;
        private System.Windows.Forms.DataGridView grdImages;
        private System.Windows.Forms.DataGridViewTextBoxColumn clFile;
        private System.Windows.Forms.DataGridViewTextBoxColumn clFocus;
    }
}