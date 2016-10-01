namespace cStudio {
    partial class frmImgProps {
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
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.lbCamera = new System.Windows.Forms.Label();
            this.lbLens = new System.Windows.Forms.Label();
            this.lbFocus = new System.Windows.Forms.Label();
            this.lbApp = new System.Windows.Forms.Label();
            this.lbFile = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.button1.Location = new System.Drawing.Point(88, 179);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "OK";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(18, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Camera:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(18, 46);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(33, 13);
            this.label3.TabIndex = 3;
            this.label3.Text = "Lens:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(18, 77);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(100, 13);
            this.label4.TabIndex = 4;
            this.label4.Text = "Focal Distance, mm";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(18, 105);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(50, 13);
            this.label5.TabIndex = 5;
            this.label5.Text = "Aperture:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(18, 133);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(26, 13);
            this.label6.TabIndex = 6;
            this.label6.Text = "File:";
            // 
            // lbCamera
            // 
            this.lbCamera.AutoSize = true;
            this.lbCamera.Location = new System.Drawing.Point(67, 21);
            this.lbCamera.Name = "lbCamera";
            this.lbCamera.Size = new System.Drawing.Size(16, 13);
            this.lbCamera.TabIndex = 7;
            this.lbCamera.Text = "...";
            // 
            // lbLens
            // 
            this.lbLens.AutoSize = true;
            this.lbLens.Location = new System.Drawing.Point(57, 46);
            this.lbLens.Name = "lbLens";
            this.lbLens.Size = new System.Drawing.Size(16, 13);
            this.lbLens.TabIndex = 9;
            this.lbLens.Text = "...";
            // 
            // lbFocus
            // 
            this.lbFocus.AutoSize = true;
            this.lbFocus.Location = new System.Drawing.Point(124, 77);
            this.lbFocus.Name = "lbFocus";
            this.lbFocus.Size = new System.Drawing.Size(16, 13);
            this.lbFocus.TabIndex = 10;
            this.lbFocus.Text = "...";
            // 
            // lbApp
            // 
            this.lbApp.AutoSize = true;
            this.lbApp.Location = new System.Drawing.Point(74, 105);
            this.lbApp.Name = "lbApp";
            this.lbApp.Size = new System.Drawing.Size(16, 13);
            this.lbApp.TabIndex = 11;
            this.lbApp.Text = "...";
            // 
            // lbFile
            // 
            this.lbFile.AutoSize = true;
            this.lbFile.Location = new System.Drawing.Point(50, 133);
            this.lbFile.Name = "lbFile";
            this.lbFile.Size = new System.Drawing.Size(16, 13);
            this.lbFile.TabIndex = 12;
            this.lbFile.Text = "...";
            // 
            // frmImgProps
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.button1;
            this.ClientSize = new System.Drawing.Size(244, 214);
            this.Controls.Add(this.lbFile);
            this.Controls.Add(this.lbApp);
            this.Controls.Add(this.lbFocus);
            this.Controls.Add(this.lbLens);
            this.Controls.Add(this.lbCamera);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "frmImgProps";
            this.Text = "Image Properties";
            this.Load += new System.EventHandler(this.frmImgProps_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label lbCamera;
        private System.Windows.Forms.Label lbLens;
        private System.Windows.Forms.Label lbFocus;
        private System.Windows.Forms.Label lbApp;
        private System.Windows.Forms.Label lbFile;
    }
}