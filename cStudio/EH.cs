using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace cStudio {
    static class EH {
        public static void Err(string src, string msg) {
            MessageBox.Show(msg, src);
        }

    }
}
