using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace cStudio {
    partial class frmImage : ScrollableControl { //: Form {
        private double _Zoom;  // Zoom factor
        public double Zoom { get { return _Zoom; } set { SetZoom(value); } }
        private Pt _Pos;
        private Pt CenterScreen;
        public Bitmap Bmp;
        public Control lbPos;
        public delegate void OnImgClickDelegate(double x, double y);
        public OnImgClickDelegate OnImgClick;

        public frmImage() {
            InitializeComponent();
            this.DoubleBuffered = true;
            _Pos = new Pt(0,0);
            CenterScreen = new Pt(0, 0);            
        }

        private void frmImage_Paint(object sender, PaintEventArgs e) {
            if (Bmp != null) {
                Graphics g = e.Graphics;
                g.DrawImage(Bmp,
                    new Rectangle(AutoScrollPosition.X, AutoScrollPosition.Y,
                        (int)(Bmp.Width * Zoom), (int)(Bmp.Height * Zoom)));
            }
        }

        private void SetZoom(double z){
            if (z != _Zoom && Bmp != null) {
                Pt cs = CenterScreen; // Old center position
                _Zoom = z;
                AutoScrollMinSize = new Size((int)(Bmp.Width * Zoom), (int)(Bmp.Height * Zoom));
                // Ajust CenterScreen
                Point newPos = new Point();
                Rectangle r = DisplayRectangle;
                newPos.X = -(int)(cs.x * Zoom - 0.5 * this.Width);
                newPos.Y = -(int)((Bmp.Height - cs.y) * Zoom - 0.5 * this.Height);
                //AutoScrollPosition = newPos;
                SetDisplayRectLocation(newPos.X, newPos.Y);
                UpdateCS();
                Invalidate();
            }           
        }

        private void SetupScroll() {

        }
        
        #region Events

        private void OnMouseMove(object sender, MouseEventArgs e) {
            if (Bmp != null) {
                _Pos.x = (e.X - AutoScrollPosition.X) / Zoom; _Pos.y = Bmp.Height - (e.Y - AutoScrollPosition.Y) / Zoom;
                if (lbPos != null) {
                    lbPos.Text = _Pos.x.ToString("N2") + "  " + _Pos.y.ToString("N2");
                }
            }            
        }

        private void OnScroll(object sender, System.Windows.Forms.ScrollEventArgs e) {
            UpdateCS();
        }

        private void frmImage_Click(object sender, EventArgs e) {
            if (OnImgClick != null) {                
                OnImgClick(_Pos.x, _Pos.y);
            }
        }

        #endregion

        private void UpdateCS() {
            Pt center = new Pt(this.Width, this.Height) / 2.0;
            Pt sp = new Pt(AutoScrollPosition);
            CenterScreen = (center - sp) / Zoom;
            CenterScreen.y = Bmp.Height - CenterScreen.y;        
        }        

    }
}