using System;
using System.Collections.Generic;
using System.Collections;
using System.Text;

namespace Fairport.Map {
    class MapPolygon: IEnumerable<Ring> {
        private Ring _Bnd;
        public Ring Boundary { get { return _Bnd; } set { _Bnd = value; } }
        private ArrayList _Holes;
        
        public MBR Mbr { get { return _Bnd.Mbr; } }

        public bool IsEmpty { get { return _Bnd == null || _Bnd.Count == 0; } }
        public bool HaveHoles { get { return _Holes != null && _Holes.Count > 0; } }

        public MapPolygon() { }
        public MapPolygon(Ring AnOuterBoundary) { _Bnd = AnOuterBoundary; }

        public void AddHole(Ring AHole) {
            if (_Holes == null) _Holes = new ArrayList();
            _Holes.Add(AHole);
        }

        public override string ToString() {
            if( _Bnd == null ) return "Empty Polygon";
            string str = "Bnd: " + _Bnd.ToString();
            if (_Holes != null) str += ", " + _Holes.Count.ToString() + " Holes";
            return str;
        }


        #region Hole Enumerator
        public class HoleEnum : IEnumerator<Ring>, IDisposable {
            int idx;
            MapPolygon pg;
            public HoleEnum(MapPolygon APolygon) {
                pg = APolygon;
                idx = -1;
            }
            public bool MoveNext() {
                if (pg._Holes == null) return false;
                idx++;
                return idx < pg._Holes.Count;
            }

            public object Current {
                get {
                    return pg._Holes[idx];
                }
            }

            Ring IEnumerator<Ring>.Current {
                get {
                    return pg._Holes[idx] as Ring;
                }
            }

            public void Reset() { idx = -1; }

            public void Dispose() { pg = null; }

        }

        IEnumerator<Ring> IEnumerable<Ring>.GetEnumerator() {
            return new HoleEnum(this);
        }

        public IEnumerator GetEnumerator() {
            return new HoleEnum(this);
        }
        #endregion

    }
}
