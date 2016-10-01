using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Fairport.Common;

namespace Fairport.Map {

    public class PolyElem {
        public double Factor;
        public int Exponent;        

        public PolyElem() { Factor = 0.0; Exponent = 0; } // Just zero

        public PolyElem(double AFactor, int AnExponent) { Factor = AFactor; Exponent = AnExponent; }

        public virtual double ValueOf(double x) {
            if(Exponent == 0) return Factor;
            if(Exponent == 1) return Factor * x;
            double r = x;
            for (int ct = 1; ct < Exponent; ct++) {
                r *= x;
            }
            return Factor * r;
        }

        public PolyElem Clone() {
            return new PolyElem(Factor, Exponent);
        }

        public override string ToString() {
            return Factor.ToString() + "*x^" + Exponent.ToString();
        }

    }

    public class Polynom {        
        public PolyElem[] Elems;
        public int ElemCount { get { return Elems.Length; } }        
        public double this[int AFactorIdx] {
            get { return Elems[AFactorIdx].Factor; }
            set { Elems[AFactorIdx].Factor = value; }  
        }        

        public Polynom() { Elems = new PolyElem[0]; }

        public Polynom(int AnElemCount) { 
            Elems = new PolyElem[AnElemCount];
            for (int ct = 0; ct < Elems.Length; ct++) Elems[ct] = new PolyElem();
        }

        public Polynom(int AMinDegree, int AMaxDegree) {
            Elems = new PolyElem[AMaxDegree - AMinDegree + 1];
            for (int ct = AMinDegree; ct <= AMaxDegree; ct++) Elems[ct - AMinDegree] = new PolyElem(0, ct);
        }

        public double ValueOf(double x) {
            double r = 0;
            for (int ct = 0; ct < Elems.Length; ct++) r += Elems[ct].ValueOf(x);
            return r;
        }

        public void DropFactors() {
            foreach (PolyElem e in Elems) e.Factor = 0.0;
        }

        public Polynom Clone() {
            Polynom r = new Polynom(ElemCount);            
            for (int ct = 0; ct < ElemCount; ct++) r.Elems[ct] = Elems[ct].Clone();
            return r;
        }

    }
}
