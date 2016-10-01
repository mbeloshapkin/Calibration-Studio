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
        public CPLCalibrationImage Img;
        public Control lbPos;
        public delegate void OnImgClickDelegate(double x, double y);
        [Browsable(true)]
        public OnImgClickDelegate OnImgClick;

        public frmImage() {
            InitializeComponent();
            this.DoubleBuffered = true;
            _Pos = new Pt(0,0);
            CenterScreen = new Pt(0, 0);            
        }

        private void frmImage_Paint(object sender, PaintEventArgs e) {
            if (Img != null) {
                Graphics g = e.Graphics;
                g.DrawImage(Img.Bmp,
                    new Rectangle(AutoScrollPosition.X, AutoScrollPosition.Y,
                        (int)(Img.Bmp.Width * Zoom), (int)(Img.Bmp.Height * Zoom)));
                foreach (PlumbLine pl in Img.Lines.Values) {
                    //int ct = 1;
                    foreach (string str in pl.Keys) {
                        //_Pos.x = (e.X - AutoScrollPosition.X) / Zoom; _Pos.y = Img.Bmp.Height - (e.Y - AutoScrollPosition.Y) / Zoom;
                        Pt p = pl[str] as Pt;
                        Pt scr = new Pt();
                        scr.x = p.x * Zoom + AutoScrollPosition.X;
                        scr.y = ((double)Img.Bmp.Height - p.y) * Zoom + AutoScrollPosition.Y;
                        DrawCPoint(g, scr, str);                        
                    }
                }
            }
        }

        private void DrawCPoint(Graphics g, Pt scr, string ALabel) {
            Pen rp = Pens.Red;
            g.DrawLine(rp, new PointF((float)(scr.x - 10), (float)scr.y), new PointF((float)(scr.x + 10), (float)scr.y));
            g.DrawLine(rp, new PointF((float)scr.x, (float)(scr.y - 10)), new PointF((float)scr.x, (float)(scr.y + 10)));
            g.DrawString(ALabel, this.Font, Brushes.Black, new PointF((float)(scr.x + 5), (float)(scr.y - 15)));
        }

        private void SetZoom(double z){
            if (z != _Zoom && Img != null) {
                Pt cs = CenterScreen; // Old center position
                _Zoom = z;
                AutoScrollMinSize = new Size((int)(Img.Bmp.Width * Zoom), (int)(Img.Bmp.Height * Zoom));
                // Ajust CenterScreen
                Point newPos = new Point();
                Rectangle r = DisplayRectangle;
                newPos.X = -(int)(cs.x * Zoom - 0.5 * this.Width);
                newPos.Y = -(int)((Img.Bmp.Height - cs.y) * Zoom - 0.5 * this.Height);
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
            if (Img != null) {
                _Pos.x = (e.X - AutoScrollPosition.X) / Zoom; _Pos.y = Img.Bmp.Height - (e.Y - AutoScrollPosition.Y) / Zoom;
                if (lbPos != null) {
                    lbPos.Text = _Pos.x.ToString("N2") + "  " + _Pos.y.ToString("N2");                    
                }
            }            
        }

        private void OnScroll(object sender, System.Windows.Forms.ScrollEventArgs e) {
            UpdateCS();
        }

        private void frmImage_Click(object sender, EventArgs e) {
            if (OnImgClick != null && Img != null) {
                //_Pos.x = (e.X - AutoScrollPosition.X) / Zoom; _Pos.y = Bmp.Height - (e.Y - AutoScrollPosition.Y) / Zoom;
                //if (lbPos != null) {
                //    lbPos.Text = _Pos.x.ToString("N2") + "  " + _Pos.y.ToString("N2");
                //}
                OnImgClick(_Pos.x, _Pos.y);
            }
        }

        #endregion

        private void UpdateCS() {
            Pt center = new Pt(this.Width, this.Height) / 2.0;
            Pt sp = new Pt(AutoScrollPosition);
            CenterScreen = (center - sp) / Zoom;
            CenterScreen.y = Img.Bmp.Height - CenterScreen.y;        
        }        

    }
}