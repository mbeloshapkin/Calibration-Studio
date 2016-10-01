namespace cStudio {
    partial class FrmBody {
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmBody));
            this.lbCamera = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.rbFix = new System.Windows.Forms.RadioButton();
            this.rbDslr = new System.Windows.Forms.RadioButton();
            this.btNext = new System.Windows.Forms.Button();
            this.btBack = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lbCamera
            // 
            this.lbCamera.AutoSize = true;
            this.lbCamera.Location = new System.Drawing.Point(181, 106);
            this.lbCamera.Name = "lbCamera";
            this.lbCamera.Size = new System.Drawing.Size(89, 13);
            this.lbCamera.TabIndex = 0;
            this.lbCamera.Text = "Camera Serial No";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(276, 103);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(204, 20);
            this.textBox1.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(181, 138);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(76, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Lens Serial No";
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(276, 135);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(204, 20);
            this.textBox2.TabIndex = 3;
            // 
            // textBox3
            // 
            this.textBox3.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox3.Location = new System.Drawing.Point(184, 12);
            this.textBox3.Multiline = true;
            this.textBox3.Name = "textBox3";
            this.textBox3.ReadOnly = true;
            this.textBox3.Size = new System.Drawing.Size(296, 85);
            this.textBox3.TabIndex = 4;
            this.textBox3.Text = resources.GetString("textBox3.Text");
            // 
            // rbFix
            // 
            this.rbFix.AutoSize = true;
            this.rbFix.Location = new System.Drawing.Point(184, 174);
            this.rbFix.Name = "rbFix";
            this.rbFix.Size = new System.Drawing.Size(115, 17);
            this.rbFix.TabIndex = 5;
            this.rbFix.TabStop = true;
            this.rbFix.Text = "Fixed Lens Camera";
            this.rbFix.UseVisualStyleBackColor = true;
            // 
            // rbDslr
            // 
            this.rbDslr.AutoSize = true;
            this.rbDslr.Location = new System.Drawing.Point(333, 174);
            this.rbDslr.Name = "rbDslr";
            this.rbDslr.Size = new System.Drawing.Size(93, 17);
            this.rbDslr.TabIndex = 6;
            this.rbDslr.TabStop = true;
            this.rbDslr.Text = "DSLR Camera";
            this.rbDslr.UseVisualStyleBackColor = true;
            // 
            // btNext
            // 
            this.btNext.Location = new System.Drawing.Point(405, 231);
            this.btNext.Name = "btNext";
            this.btNext.Size = new System.Drawing.Size(75, 23);
            this.btNext.TabIndex = 7;
            this.btNext.Text = "Next >>";
            this.btNext.UseVisualStyleBackColor = true;
            // 
            // btBack
            // 
            this.btBack.Location = new System.Drawing.Point(324, 231);
            this.btBack.Name = "btBack";
            this.btBack.Size = new System.Drawing.Size(75, 23);
            this.btBack.TabIndex = 8;
            this.btBack.Text = "<< Back";
            this.btBack.UseVisualStyleBackColor = true;
            // 
            // FrmBody
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(492, 266);
            this.Controls.Add(this.btBack);
            this.Controls.Add(this.btNext);
            this.Controls.Add(this.rbDslr);
            this.Controls.Add(this.rbFix);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.lbCamera);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FrmBody";
            this.Text = "New Project: Camera and Lens Identification";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lbCamera;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.RadioButton rbFix;
        private System.Windows.Forms.RadioButton rbDslr;
        private System.Windows.Forms.Button btNext;
        private System.Windows.Forms.Button btBack;
    }
}