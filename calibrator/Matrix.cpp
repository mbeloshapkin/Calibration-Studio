// Matrix.cpp: implementation of the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Matrix.h"
#include "math.h"
//#include "fortran.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//
typedef struct{
		  int x,y;
		  double *a;
		  HGLOBAL hGlb;}MATRIX;

typedef MATRIX *PMATRIX;

MATRIX *WinInverseNonSquareMatrix(MATRIX *MA, double TOL, MATRIX *MS, int *ErrNo);

// Интерфейс с типом MATRIX
static MATRIX *Connect(const CMatrix& M){
	MATRIX *R = new MATRIX;
	CSize s = M.GetSize();
	R->x = s.cx; R->y = s.cy;
	R->a = M.GetData();
	R->hGlb = 0;
	return R;
}

static void Disconnect(MATRIX *M){
	delete M;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatrix::CMatrix(const int x, const int y){
	if (x > 0) nx = x; else nx = 0;
	if (y > 0) ny = y; else ny = 0;
	if ((nx + ny) > 0) a = new double[nx * ny]; else a = NULL;
}

CMatrix::~CMatrix(){ 
	if (a != NULL){
		delete [] a;
	}
}

void CMatrix::Zero(){
	if(nx > 0 && ny > 0) memset(a,0,sizeof(double) * nx * ny);
}


CMatrix CMatrix::Inverse(){
	CMatrix R(ny,nx);
	PMATRIX A,AINV,S;

	CMatrix MS(1,nx); // Матрица для сингулярных значений
	int ErrNo = 0;  // переменная для возврата кода ошибки

	A = ::Connect(*this);	
	S = ::Connect(MS);
	AINV = WinInverseNonSquareMatrix(A,0.0,S,&ErrNo);
	memcpy(R.GetData(),AINV->a,sizeof(double) * nx * ny);
	HGLOBAL h = AINV->hGlb;
	::GlobalUnlock(h);
	::GlobalFree(h);	
	::Disconnect(A);
	::Disconnect(S);
	return R;
}


void CMatrix::Transpose(){
	CMatrix B(ny,nx);
	int ctx,cty; double da;
	for (cty = 0; cty < ny; cty++)
		for (ctx = 0; ctx < nx; ctx++){
			da = Get(ctx,cty); B.Set(cty,ctx,da);
		}
	memcpy(a,B.a, sizeof(double) * nx * ny);
	nx = B.nx; ny = B.ny;
}

CMatrix& CMatrix::operator=(const CMatrix& m){
	if (this == &m) return *this;
	//this->CObject::operator=(m); // Во, блин!
	if(a) delete [] a;
	a = new double[m.nx * m.ny];
	nx = m.nx; ny = m.ny;
	memcpy(a,m.a,sizeof(double) * nx * ny);
	return *this;
}
/*
MATRIX *MulMatrix(MATRIX *B, MATRIX *A){  // C = B*A
MATRIX *C; int cx,cy,ct; double a, b, c;
if (B->x != A->y) return NULL; // B: 9x7 A:1x9
C = MakeMatrix(A->x,B->y);     // C: 1x9
for (cy = 0; cy < C->y; cy++){
  for (cx = 0; cx < C->x; cx++){
	 c = 0;
	 for(ct = 0; ct < B->x; ct++){
		b = GetA(B,ct,cy);
		a = GetA(A,cx,ct);
		c = a * b + c;
	 }
	 SetA(C,cx,cy,c);
 }
}
return C;}
*/

CMatrix CMatrix::operator *(const CMatrix& M) const{ // return this * m
	if (nx != M.ny) return CMatrix();  // this - B, M - A
	CMatrix R(M.nx,ny);
	int cx,cy,ct; 
	double a, b, c;
	for (cy = 0; cy < R.ny; cy++){
		for (cx = 0; cx < R.nx; cx++){
			c = 0;
			for(ct = 0; ct < nx; ct++){
				b = Get(ct,cy);
				a = M.Get(cx,ct);
				c = a * b + c;
			}
		R.Set(cx,cy,c);
		}
	}
	return R;
}

void CMatrix::operator *=(const double x){ // Скалярное умножение матрицы на число
	int ct;
	for (ct = 0; ct < (nx * ny); ct++) a[ct] *= x;
}

// ------------------- М А Т --------------------
// Header file for Windows version of ISML library
// MB, Feb. 1997.
// The original ISML inverse procedure
// Type "MATRIX" is defined in module det.h
// Modified for SDS-2 tech by MB, Jan 2001.

//void LGINF(MATRIX *A, int IA, int M, int N, double TOL, MATRIX *AINV,
//				int IAINV, MATRIX *S, MATRIX *WK, int *IER);

// Arguments specification:
//   ARGUMENTS	 A	- M BY N MATRIX. (INPUT)  A IS DESTROYED.
//		 IA	- ROW DIMENSION OF MATRIX A EXACTLY AS
//			    SPECIFIED IN THE DIMENSION STATEMENT IN THE
//			    CALLING PROGRAM. (INPUT)
//			    A IS USED BY LGINF AS WORK STORAGE FOR AN
//			    N BY N MATRIX. THEREFORE, IA MUST BE
//			    GREATER THAN OR EQUAL TO MAX(M,N).
//		 M	- NUMBER OF ROWS IN A. (INPUT)
//		 N	- NUMBER OF COLUMNS IN A. (INPUT)
//		 TOL	- TOLERANCE PARAMETER. (INPUT)
//			    IF TOL IS LESS THAN OR EQUAL TO ZERO ON
//			    INPUT, LGINF COMPUTES THE GENERALIZED
//			    INVERSE OF A.
//			    IF TOL IS GREATER THAN ZERO ON INPUT, LGINF
//			    COMPUTES THE GENERALIZED INVERSE OF A MATRIX
//			    CLOSE TO A, BUT HAVING CONDITION NUMBER LESS
//			    THAN 1.0/TOL.
//		 AINV	- N BY M MATRIX. (OUTPUT)
//			    AINV CONTAINS THE GENERALIZED INVERSE OF A
//			    OR THE GENERALIZED INVERSE OF A MATRIX
//			    CLOSE TO A. SEE TOL ARGUMENT DESCRIPTION.
//		 IAINV	- ROW DIMENSION OF MATRIX AINV EXACTLY AS
//			    SPECIFIED IN THE DIMENSION STATEMENT IN THE
//			    CALLING PROGRAM. (INPUT)
//		 S	- VECTOR OF LENGTH N. S CONTAINS THE ORDERED
//			    SINGULAR VALUES OF A.  S(1) .GE. S(2),...,
//			    .GE. S(N) .GE. 0. (OUTPUT)
//		 WK	- WORK VECTOR OF LENGTH 2N.
//		 IER	- ERROR PARAMETER. (OUTPUT)
//			  WARNING ERROR
//			    IER=33 INDICATES THAT MATRIX A IS NOT
//			      FULL RANK OR VERY ILL-CONDITIONED. SMALL
//			      SINGULAR VALUES MAY NOT BE VERY ACCURATE.
//			    IER=34 INDICATES THAT EITHER N.LE.0 OR
//			      M.LE.0.
//			  TERMINAL ERROR
//			    IER=129 INDICATES THAT CONVERGENCE WAS
//			      NOT OBTAINED BY LSVDB AND COMPUTATION
//			      WAS DISCONTINUED.
//
//-----------------------------------------------------------
// WinLGINF - The C version of LGINF, free from FORTRANs stupidity.
// The means of arguments is the same as for LGINF,
// except the IER parameter now is the return value.
// WinLGINF dynamically allocates memory for work arrays and
// not destroy the input matrix A
//------------------------------------------------------------
// Definitions from module Fortran.h
// Math. functions redefinitions
#define DSQRT sqrt
#define DABS fabs
#define ABS fabs
double DMAX1(double a, double b);
int MIN0(int a, int b);
//------------
// FORTRAN one and two dimentional arrays structure emulation
// (system depended)
typedef struct{int Rows,Columns; double *a;
					HGLOBAL hGlb;}FARRAY;

FARRAY *DefineArray2(int Rows, int Columns); // Define two dimentional
									 // array A(I,J), I = Rows, J = Columns, working
									 // as DefineArray.
double FGetVal(FARRAY *A, int idx); // FGetVal(A,idx) is equvivalent A(idx)
									 // in the sence of FORTRAN
void FSetVal(FARRAY *A, int idx, double x); // FSetVal(A,I,X) <-> A(I) = X
double FGetVal2(FARRAY *A, int Row, int Column); //
void FSetVal2(FARRAY *A, int Row, int Column, double x); //
									 // FSetVal2(A,I,J,X) <-> A(I,J) = X
									 // For example: FORTRAN operator A(I,J) = B(J,K)
									 // is equvivalent FSetVal2(A,I,J,FGetVal2(B,J,K);
double *FGetCell(FARRAY *A, int Row, int Column);
									 // Get address of cell A(Row,Column)
double *FGetData(FARRAY *A);// Get address of cell A(1,1)
void KillArray(FARRAY *A);  // Discard FARRAY strructure A and all of data
									 // from memory.									 // FGetVal2(A,I,J) <-> A(I,J)
BOOL ChangeDimention(FARRAY *Old, FARRAY *New, int NewRows, int NewColumns);
									 // Fill array New with data from array Old and
									 // assign to array New dimentions NewRows, NewColumns.
									 // New and Old arrays contains the same data and
									 // changing one array cause changes another.
									 // If total number of cells of Old is not equal
									 // NewRows * NewColumns, the procedure return
									 // FALSE, else - TRUE.
void DefineDimention(FARRAY *A, double *a, int Rows, int Columns);
									 // Fill array structure A with Rows and Columns
									 // values, declare the address a as cell A(1,1)
// ---------------------- The END of fortran.h -----------------
// Definitions from det.h
/*typedef struct{
		  int x,y;
		  double *a;
		  HGLOBAL hGlb;}MATRIX;

typedef MATRIX *PMATRIX; */

FARRAY *Matrix2FArray(MATRIX *M);
double GetA(MATRIX *A, int x, int y);
void SetA(MATRIX *A, int x, int y, double a);
MATRIX *MakeMatrix(int x, int y);
// ---------------------- The END of Det.h ----------------------


int WinLGINF(MATRIX *A, double TOL, MATRIX *AINV, MATRIX *S);
//MATRIX *WinInverseNonSquareMatrix(MATRIX *MA, double TOL, MATRIX *MS, int *ErrNo);

//---------------------------------------------------------------
//		Р Е А Л И З А Ц И Я
//-------------------- FORTRAN.C --------------------------------
double DMAX1(double a, double b){
if (a > b) return a; else return b;}

int MIN0(int a, int b){
if (a < b) return a; else return b;}

void KillArray(FARRAY *A){
if (A->hGlb){ GlobalUnlock(A->hGlb); GlobalFree(A->hGlb);} }

double FGetVal(FARRAY *A, int idx){
double *a; a = A->a + idx - 1; return *a;}

void FSetVal(FARRAY *A, int idx, double x){
double *a; a = A->a + idx - 1; *a = x;}

double FGetVal2(FARRAY *A, int Row, int Column){
double *a;
a = A->a + (Column - 1) * A->Rows + Row - 1; return *a;}

void FSetVal2(FARRAY *A, int Row, int Column, double x){
double *a;
a = A->a + (Column - 1) * A->Rows + Row - 1; *a = x;}

double *FGetCell(FARRAY *A, int Row, int Column){
double *a;
a = A->a + (Column - 1) * A->Rows + Row - 1; return a;}

double *FGetData(FARRAY *A){return A->a;}

BOOL ChangeDimention(FARRAY *Old, FARRAY *New, int NewRows, int NewColumns){
New->Rows = NewRows; New->Columns = NewColumns;
New->a = Old->a; New->hGlb = Old->hGlb;
if ((Old->Rows * Old->Columns) == (New->Rows * New->Columns)) return TRUE;
else return FALSE;}

void DefineDimention(FARRAY *A, double *a, int Rows, int Columns){
A->hGlb = 0; A->a = a; A->Rows = Rows; A->Columns = Columns;}

FARRAY *DefineArray(int n){
HGLOBAL hGlb; PBYTE adr;
FARRAY *f;
hGlb = GlobalAlloc(GPTR,sizeof(double) * n + sizeof(FARRAY));
if (!hGlb) return NULL;
f = (FARRAY *)GlobalLock(hGlb);
adr = (PBYTE)f; adr = adr + sizeof(FARRAY);
f->Rows = n; f->Columns = 1;
f->a = (double *)adr; f->hGlb = hGlb;
return f;}

FARRAY *DefineArray2(int Rows, int Columns){
FARRAY *f;
f = DefineArray(Rows * Columns);
f->Rows = Rows; f->Columns = Columns; return f;}


//------------------- End of FORTRAN.C -----------------------
//---------------------- DET.C -------------------------------
void SetA(MATRIX *M, int x, int y, double a){
double *p;
p = M->a + x + y*M->x; *p = a;}

double GetA(MATRIX *M, int x, int y){
double *p;
p = M->a + x + y*M->x; return *p;}

MATRIX *MakeMatrix(int x, int y){
HGLOBAL hGlb; MATRIX *M; PBYTE p;
hGlb = GlobalAlloc(GPTR,sizeof(MATRIX)+x*y*sizeof(double));
if (!hGlb) return NULL;
M = (MATRIX *)GlobalLock(hGlb);
M->x = x; M->y = y; M->hGlb = hGlb;
p = (PBYTE)M + sizeof(MATRIX);
M->a = (double *)p; return M;}

FARRAY *Matrix2FArray(MATRIX *M){
FARRAY *F; int ctx, cty; double a;
F = DefineArray2(M->y,M->x);
for (cty = 0; cty < M->y; cty++){
  for (ctx = 0; ctx < M->x; ctx++){
	 a = GetA(M,ctx,cty);
	 FSetVal2(F,cty + 1,ctx + 1,a);
}}
return F;}
//------------------- End of DET.C ---------------------------

void WinPrint(PSTR format, int i, PSTR s1, char c, PSTR s2){
char str[100];
HWND Owner;
Owner = GetActiveWindow();
sprintf(str,format,i,s1,c,s2);
MessageBox(Owner,str,"ISML Message",MB_ICONEXCLAMATION | MB_OK);
}
// Functions Declarations:
void LGINF(FARRAY *A,int IA, int M, int N,double TOL,
	FARRAY *AINV,int IAINV,FARRAY *S,FARRAY *WK,int *IER);
void LGING(FARRAY *A, int IA, int M, int N, FARRAY *B,
	 int IB, int NB, FARRAY *S, FARRAY *WK, int *IER);
void LSVDB(double *fD,double *fE,int N,double *fV,int IV,
			int NRV,double *fC,int IC,int NCC,int *IER);
void LSVG1(double A,double B,double *DCOS,double *DSIN,double *SIG);
void LSVG2(double DCOS,double DSIN,double *X,double *Y);
void UERSET(int LEVEL, int *LEVOLD);
void UERTST(int IER, PSTR NAME);
//void UGETIO(int IOPT, int *NIN, int *NOUT);
void VHS12(int MODE,int LP,int L1,int M,double *fU,int INCU,
		 double *UP,double *fC,int INCC,int ICV,int NCV);
// The Windows version of LGINF:

int WinLGINF(MATRIX *MA, double TOL, MATRIX *MAINV, MATRIX *MS){
FARRAY *WK, *A, *AINV, *S;
int ErrNo, A_Rows, A_Columns, INP_Dim;
int ctx,cty;

if (MA->x > MA->y) INP_Dim = MA->x;
else INP_Dim = MA->y;

A = Matrix2FArray(MA);

AINV = Matrix2FArray(MAINV);
S = Matrix2FArray(MS);
A_Rows = A->Rows; A_Columns = A->Columns;


WK = DefineArray2(A_Columns,2);

LGINF(A,INP_Dim,A_Rows,A_Columns,TOL,AINV,AINV->Rows,S,WK,&ErrNo);

for (cty = 0; cty < MAINV->y; cty++){
  for (ctx = 0; ctx < MAINV->x; ctx++){
	 SetA(MAINV,ctx,cty,FGetVal2(AINV,cty + 1,ctx + 1));
}}

KillArray(A); KillArray(AINV);
KillArray(S); KillArray(WK);
return ErrNo;}

MATRIX *WinInverseNonSquareMatrix(MATRIX *MA, double TOL, MATRIX *MS, int *ErrNo){
FARRAY *WK, *A, *AINV, *S; MATRIX *MAINV;
int A_Rows, A_Columns, INP_Dim;
int ctx,cty/*,r,c*/; double a;

if (MA->x > MA->y) INP_Dim = MA->x;
else INP_Dim = MA->y;
MAINV = MakeMatrix(MA->y,MA->x);

A = DefineArray2(INP_Dim,INP_Dim);
A_Rows = MA->y; A_Columns = MA->x;

for (cty = 0; cty < MA->y; cty++){
  for (ctx = 0; ctx < MA->x; ctx++){
	  a = GetA(MA,ctx,cty); FSetVal2(A,cty + 1,ctx + 1,a);
  }
}

AINV = DefineArray2(A_Columns,A_Rows);

S = Matrix2FArray(MS);

WK = DefineArray2(A_Columns,2);

LGINF(A,INP_Dim,A_Rows,A_Columns,TOL,AINV,AINV->Rows,S,WK,ErrNo);

for (cty = 0; cty < AINV->Rows; cty++){
  for (ctx = 0; ctx < AINV->Columns; ctx++){
	 SetA(MAINV,ctx,cty,FGetVal2(AINV,cty + 1,ctx + 1));
}}

KillArray(A); KillArray(AINV);
KillArray(S); KillArray(WK);
return MAINV;}
//   IMSL ROUTINE NAME	- LGINF
//
//-----------------------------------------------------------------------
//
//   COMPUTER		- DEC11/DOUBLE
//
//   LATEST REVISION	- JUNE 1, 1980
//
//   PURPOSE		- GENERALIZED INVERSE OF A REAL MATRIX
//
//   USAGE		- CALL LGINF (A,IA,M,N,TOL,AINV,IAINV,S,WK,IER)
//
//   ARGUMENTS	 A	- M BY N MATRIX. (INPUT)  A IS DESTROYED.
//		 IA	- ROW DIMENSION OF MATRIX A EXACTLY AS
//			    SPECIFIED IN THE DIMENSION STATEMENT IN THE
//			    CALLING PROGRAM. (INPUT)
//			    A IS USED BY LGINF AS WORK STORAGE FOR AN
//			    N BY N MATRIX. THEREFORE, IA MUST BE
//			    GREATER THAN OR EQUAL TO MAX(M,N).
//		 M	- NUMBER OF ROWS IN A. (INPUT)
//		 N	- NUMBER OF COLUMNS IN A. (INPUT)
//		 TOL	- TOLERANCE PARAMETER. (INPUT)
//			    IF TOL IS LESS THAN OR EQUAL TO ZERO ON
//			    INPUT, LGINF COMPUTES THE GENERALIZED
//			    INVERSE OF A.
//			    IF TOL IS GREATER THAN ZERO ON INPUT, LGINF
//			    COMPUTES THE GENERALIZED INVERSE OF A MATRIX
//			    CLOSE TO A, BUT HAVING CONDITION NUMBER LESS
//			    THAN 1.0/TOL.
//		 AINV	- N BY M MATRIX. (OUTPUT)
//			    AINV CONTAINS THE GENERALIZED INVERSE OF A
//			    OR THE GENERALIZED INVERSE OF A MATRIX
//			    CLOSE TO A. SEE TOL ARGUMENT DESCRIPTION.
//		 IAINV	- ROW DIMENSION OF MATRIX AINV EXACTLY AS
//			    SPECIFIED IN THE DIMENSION STATEMENT IN THE
//			    CALLING PROGRAM. (INPUT)
//		 S	- VECTOR OF LENGTH N. S CONTAINS THE ORDERED
//			    SINGULAR VALUES OF A.  S(1) .GE. S(2),...,
//			    .GE. S(N) .GE. 0. (OUTPUT)
//		 WK	- WORK VECTOR OF LENGTH 2N.
//		 IER	- ERROR PARAMETER. (OUTPUT)
//			  WARNING ERROR
//			    IER=33 INDICATES THAT MATRIX A IS NOT
//			      FULL RANK OR VERY ILL-CONDITIONED. SMALL
//			      SINGULAR VALUES MAY NOT BE VERY ACCURATE.
//			    IER=34 INDICATES THAT EITHER N.LE.0 OR
//			      M.LE.0.
//			  TERMINAL ERROR
//			    IER=129 INDICATES THAT CONVERGENCE WAS
//			      NOT OBTAINED BY LSVDB AND COMPUTATION
//			      WAS DISCONTINUED.
//
//   PRECISION/HARDWARE	- SINGLE AND DOUBLE/H32
//			- SINGLE/H36,H48,H60
//
//   REQD. IMSL ROUTINES - LGING,LSVDB,LSVG1,LSVG2,VHS12,UERSET,UERTST,
//			    UGETIO
//
//   NOTATION		- INFORMATION ON SPECIAL NOTATION AND
//			    CONVENTIONS IS AVAILABLE IN THE MANUAL
//			    INTRODUCTION OR THROUGH IMSL ROUTINE UHELP
//
//   COPYRIGHT		- 1978 BY IMSL, INC. ALL RIGHTS RESERVED.
//
//   WARRANTY		- IMSL WARRANTS ONLY THAT IMSL TESTING HAS BEEN
//			    APPLIED TO THIS CODE. NO OTHER WARRANTY,
//			    EXPRESSED OR IMPLIED, IS APPLICABLE.
//
//-----------------------------------------------------------------------
//
void LGINF(FARRAY *A,int IA, int M, int N,double TOL,
	FARRAY *AINV,int IAINV,FARRAY *S,FARRAY *WK,int *IER){
//
//				   SPECIFICATIONS FOR ARGUMENTS
//		INTEGER		 IA,IAINV,IER,M,N
//		DOUBLE PRECISION	 A(IA,N),S(N),TOL,WK(N,2),AINV(IAINV,M)
//			   SPECIFICATIONS FOR LOCAL VARIABLES
int I,J,K,L;
double T,TOLL;
//			   FIRST EXECUTABLE STATEMENT
*IER = 0;
for (I = 1; I <= N; I++){
  for (J = 1; J <= M; J++){
	  FSetVal2(AINV,I,J,0.0);
	  if (I == J) FSetVal2(AINV,I,J,1.0);
  M5:;} //	 CONTINUE
M10:;}  // CONTINUE
//
LGING(A,IA,M,N,AINV,IAINV,M,S,WK,IER);
//
if (*IER > 128) goto M9000;
L = MIN0(M,N);
//				   U**T HAS BEEN PLACED IN AINV
TOLL = FGetVal(S,1) * DMAX1(TOL,0.0);
//				   COMPUTE Q**(+) U**T
for (I = 1; I <= L; I++){
  if (FGetVal(S,I) <= TOLL) goto M20;
  for (J = 1; J <= M; J++){
  M15: FSetVal2(AINV,I,J,FGetVal2(AINV,I,J)/FGetVal(S,I));}
  goto M30;
  M20: for (J = 1; J <= M; J++){
		 M25:	 FSetVal2(AINV,I,J,0.0);}
M30:;} // CONTINUE
//				   COMPUTE V Q**(+) U**T
for(J = 1; J <= M; J++){
  for(I = 1; I <= N; I++){
	 T = 0.0;
	 for (K = 1; K <= L; K++){
	 M35:  T = T + FGetVal2(A,I,K) * FGetVal2(AINV,K,J);}
	 FSetVal2(WK,I,1,T);
  M40:;} //	 CONTINUE
  for (I = 1; I <= N; I++){
  M45: FSetVal2(AINV,I,J,FGetVal2(WK,I,1));}
M50:;} // CONTINUE
if (*IER == 0) goto M9005;
M9000: //CONTINUE
	UERTST(*IER,"LGINF ");
M9005:;} // RETURN
//		END
//  IMSL ROUTINE NAME	- LGING
//
//----------------------------------------------------------------------
//
//  COMPUTER		- DEC11/DOUBLE
//
//  LATEST REVISION	- JUNE 1, 1980
//
//  PURPOSE		- NUCLEUS USED ONLY BY IMSL ROUTINE LGINF
//
//
//  PRECISION/HARDWARE	- SINGLE AND DOUBLE/H32
//		- SINGLE/H36,H48,H60
//
//  REQD. IMSL ROUTINES - LSVDB,LSVG1,LSVG2,VHS12,UERSET,UERTST,UGETIO
//
//  NOTATION		- INFORMATION ON SPECIAL NOTATION AND
//		    CONVENTIONS IS AVAILABLE IN THE MANUAL
//		    INTRODUCTION OR THROUGH IMSL ROUTINE UHELP
//
//  COPYRIGHT		- 1978 BY IMSL, INC. ALL RIGHTS RESERVED.
//
//  WARRANTY		- IMSL WARRANTS ONLY THAT IMSL TESTING HAS BEEN
//		    APPLIED TO THIS CODE. NO OTHER WARRANTY,
//		    EXPRESSED OR IMPLIED, IS APPLICABLE.
//
//----------------------------------------------------------------------
//
void LGING(FARRAY *fA,int IA,int M,int N,FARRAY *fB,
			  int IB,int NB,FARRAY *fS,FARRAY *fWK,int *IER){
//C
//C				   SPECIFICATIONS FOR ARGUMENTS
//		INTEGER		 IA,M,N,IB,NB,IER
//		DOUBLE PRECISION	 A(IA,N),B(IB,1),S(N),WK(N,2)
FARRAY A,B,S,WK;
ChangeDimention(fA,&A,IA,N); ChangeDimention(fB,&B,IB,1);
ChangeDimention(fS,&S,N,1); ChangeDimention(fWK,&WK,N,2);
//C				   SPECIFICATIONS FOR LOCAL VARIABLES
int I,J,JP1,K,L,MM,NN,NNP1,NS,NSP1,NM;
double ZERO = 0.0, ONE = 1.0, T, F, FF;
//				   FIRST EXECUTABLE STATEMENT
*IER = 0;
//C				   BEGIN SPECIAL FOR ZERO ROWS AND
//C				     COLS. PACK THE NONZERO COLS TO THE
//C				     LEFT
NN = N;
*IER = 34;
if ((NN <= 0) || (M <= 0)) goto M9005;
*IER = 0;
J = NN;
M5: // CONTINUE
for (I = 1; I <= M; I++){
  if (FGetVal2(&A,I,J) != ZERO) goto M25;
M10:;} // CONTINUE
//				   COL J IS ZERO. EXCHANGE IT WITH COL
//				     N
if (J == NN) goto M20;
for (I = 1; I <= M; I++){
M15: FSetVal2(&A,I,J,FGetVal2(&A,I,NN));}
M20: // CONTINUE
FSetVal2(&A,1,NN,(double)J);
NN = NN - 1;
M25: // CONTINUE
J = J - 1;
if (J >= 1) goto M5;
//				   IF N=0 THEN A IS ENTIRELY ZERO AND
//				     SVD COMPUTATION CAN BE SKIPPED
NS = 0;
if (NN == 0) goto M125;
//C				   PACK NONZERO ROWS TO THE TOP QUIT
//C				     PACKING IF FIND N NONZERO ROWS
I = 1;
MM = M;
M30: if ((I > N) || (I >=MM)) goto M75;
if (FGetVal2(&A,I,I) != ZERO) goto M40;
for (J = 1; J <= NN; J++){
  if (FGetVal2(&A,I,J) != ZERO) goto M40;
M35:;} // CONTINUE
goto M45;
M40: I = I + 1;
goto M30;
//C				   ROW I IS ZERO EXCHANGE ROWS I AND M
M45: if (NB <= 0) goto M55;
for (J = 1; J <= NB; J++){
	 T = FGetVal2(&B,I,J);
	 FSetVal2(&B,I,J,FGetVal2(&B,MM,J));
	 FSetVal2(&B,MM,J,T);
M50:;} // CONTINUE
M55: for (J = 1; J <= NN; J++){
M60: FSetVal2(&A,I,J,FGetVal2(&A,MM,J));}
if (MM > NN) goto M70;
for (J = 1; J <= NN; J++){
M65: FSetVal2(&A,MM,J,ZERO);}
M70: // CONTINUE
//				   EXCHANGE IS FINISHED
MM = MM - 1;
goto M30;
//
M75: // CONTINUE
//C				   END SPECIAL FOR ZERO ROWS AND
//C				     COLUMNS
//C				   BEGIN SVD ALGORITHM..
//C				   (1) REDUCE THE MATRIX TO UPPER
//C				     BIDIAGONAL FORM WITH HOUSEHOLDER
//C				     TRANSFORMATIONS.
//C				     H(N)...H(1)AQ(1)...Q(N-2) =
//C				     (D**T,0)**T WHERE D IS UPPER
//C				     BIDIAGONAL.
//C				   (2) APPLY H(N)...H(1) TO B. HERE
//C				     H(N)...H(1)*B REPLACES B IN
//C				     STORAGE.
//C				   (3) THE MATRIX PRODUCT W=
//C				     Q(1)...Q(N-2) OVERWRITES THE FIRST
//C				     N ROWS OF A IN STORAGE.
//C				   (4) AN SVD FOR D IS COMPUTED. HERE K
//C				     ROTATIONS RI AND PI ARE COMPUTED
//C				     SO THAT RK...R1*D*P1**(T)...PK**(T)
//C				     = DIAG(S1,...,SM) TO WORKING
//C				     ACCURACY. THE SI ARE NONNEGATIVE
//C				     AND NONINCREASING. HERE RK...R1*B
//C				     OVERWRITES B IN STORAGE WHILE
//C				     A*P1**(T)...PK**(T) OVERWRITES A
//C				     IN STORAGE.
//C				   (5) IT FOLLOWS THAT,WITH THE PROPER
//C				     DEFINITIONS, U**(T)*B OVERWRITES
//C				     B, WHILE V OVERWRITES THE FIRST N
//C				     ROW AND COLUMNS OF A.
L = MIN0(MM,NN);
//C				   THE FOLLOWING LOOP REDUCES A TO
//C				     UPPER BIDIAGONAL AND ALSO APPLIES
//C				     THE PREMULTIPLYING TRANSFORMATIONS
//C				     TO B.
for (J = 1; J <= L; J++){
  if (J >= MM) goto M80;
  JP1 = MIN0(J+1,NN);
  VHS12(1,J,J+1,MM,FGetCell(&A,1,J),1,&T,FGetCell(&A,1,JP1),1,IA,NN-J);
  FSetVal(&S,J,T);
  M80: if (J >= (NN-1)) goto M85;
  VHS12(1,J+1,J+2,NN,FGetCell(&A,J,1),IA,FGetCell(&WK,J,2),
	  FGetCell(&A,J+1,1),IA,1,MM-J);
M85:;} // CONTINUE
//				   CONSTRUCT THE EXPLICIT N X M PRODUCT
//				     MATRIX (I,0)*HL*...*H2*H1
int JJ;
for (JJ = 1; JJ <= L; JJ++){
  J = L + 1 - JJ;
  if (J >= MM) goto M90;
  T = FGetVal(&S,J);
  VHS12(2,J,J+1,MM,FGetCell(&A,1,J),1,&T,FGetCell(&B,1,1),IB,1,N);
M90:;} // CONTINUE
//C				   COPY THE BIDIAGONAL MATRIX INTO THE
//C				     ARRAY S FOR LSVDB
if (L == 1) goto M100;
for (J = 2; J <= L; J++){
  FSetVal(&S,J,FGetVal2(&A,J,J));
  FSetVal2(&WK,J,1,FGetVal2(&A,J-1,J));
M95:;} // CONTINUE
M100: FSetVal(&S,1,FGetVal2(&A,1,1));
//C
NS = NN;
if (MM >= NN) goto M105;
NS = MM + 1;
FSetVal(&S,NS,ZERO);
FSetVal2(&WK,NS,1,FGetVal2(&A,MM,MM+1));
M105: // CONTINUE
//C				   CONSTRUCT THE EXPLICIT N BY N
//C				     PRODUCT MATRIX, W=Q1*Q2*...*QL*I
//C				     IN THE ARRAY A
for (K = 1; K <= NN; K++){
  I = NN + 1 - K;
  if (I > MIN0(MM,NN-2)) goto M110;
  VHS12(2,I+1,I+2,NN,FGetCell(&A,I,1),IA,FGetCell(&WK,I,2),
		FGetCell(&A,1,I+1),1,IA,NN-I);
  M110: for(J = 1; J <= NN; J++){
  M115: FSetVal2(&A,I,J,ZERO);}
  FSetVal2(&A,I,I,ONE);
M120:;} // CONTINUE
//C				   COMPUTE THE SVD OF THE BIDIAGONAL
//C				     MATRIX
//C
int LEVEL,LEVOLD;

LEVEL = 1;
UERSET(LEVEL,&LEVOLD);
LSVDB(FGetCell(&S,1,1),FGetCell(&WK,1,1),NS,FGetData(&A),IA,NN,FGetData(&B),IB,NB,IER);
//C
if (*IER > 128) goto M9005;
UERSET(LEVOLD,&LEVOLD);
if (*IER != 33) goto M125;
FF = 0.0;
NM = MIN0(N,M);
if (FGetVal(&S,1) != ZERO) FF = FGetVal(&S,NM) / FGetVal(&S,1);
F = 100.0 + FF;
if (F == 100.0) goto M125;
*IER = 0;
M125: // CONTINUE
if (NS >= NN) goto M135;
NSP1 = NS+1;
for (J = NSP1; J <= NN; J++){
M130: FSetVal(&S,J,ZERO);}
M135: // CONTINUE
if (NN == N) goto M9005;
NNP1 = NN+1;
//C				   MOVE RECORD OF PERMUTATIONS AND
//C				     STORE ZEROS
for (J = NNP1; J <= N; J++){
  FSetVal(&S,J,FGetVal2(&A,1,J));
  if (NN < 1) goto M145;
  for (I = 1; I <= NN; I++){
  M140: FSetVal2(&A,I,J,ZERO);}
M145:;} // CONTINUE
//C				   PERMUTE ROWS AND SET ZERO SINGULAR
//C				     VALUES
for (K = NNP1; K <= N; K++){
  I = (int)FGetVal(&S,K);
  FSetVal(&S,K,ZERO);
  for (J = 1; J <= N; J++){
	 FSetVal2(&A,K,J,FGetVal2(&A,I,J));
  M150:	FSetVal2(&A,I,J,ZERO);}
	 FSetVal2(&A,I,K,ONE);
M155:;} // CONTINUE
//C				   END SPECIAL FOR ZERO ROWS AND
//C				     COLUMNS
M9000: // CONTINUE
M9005:;} //  RETURN
//		END
//  IMSL ROUTINE NAME	- LSVDB
//
//----------------------------------------------------------------------
//
//  COMPUTER		- DEC11/DOUBLE
//
//  LATEST REVISION	- JANUARY 1, 1978
//
//  PURPOSE		- SINGULAR VALUE DECOMPOSITION OF A BIDIAGONAL
//		    MATRIX.
//
//  USAGE		- CALL LSVDB (D,E,N,V,IV,NRV,C,IC,NCC,IER)
//
//  ARGUMENTS	 D	- VECTOR OF LENGTH N. (INPUT/OUTPUT)
//		  ON INPUT, D CONTAINS THE DIAGONAL ELEMENTS
//		    OF THE BIDIAGONAL MATRIX B. D(I)=B(I,I),
//		    I=1,...,N.
//		  ON OUTPUT, D CONTAINS THE N (NONNEGATIVE)
//		    SINGULAR VALUES OF B IN NONINCREASING
//		    ORDER.
//	 E	- VECTOR OF LENGTH N. (INPUT/OUTPUT)
//		  ON INPUT, E CONTAINS THE SUPERDIAGONAL
//		    ELEMENTS OF B. E(1) IS ARBITRARY,
//		    E(I)=B(I-1,I), I=2,...,N.
//		  ON OUTPUT, THE CONTENTS OF E ARE MODIFIED
//		    BY THE SUBROUTINE.
//	 N	- ORDER OF THE MATRIX B. (INPUT)
//	 V	- NRV BY N MATRIX. (INPUT/OUTPUT)
//		    IF NRV.LE.0, V IS NOT USED. OTHERWISE,
//		    V IS REPLACED BY THE NRV BY N PRODUCT
//		    MATRIX V*VB. SEE REMARKS.
//	 IV	- ROW DIMENSION OF MATRIX V EXACTLY AS
//		    SPECIFIED IN THE DIMENSION STATEMENT IN THE
//		    CALLING PROGRAM. (INPUT)
//	 NRV	- NUMBER OF ROWS OF V. (INPUT)
//	 C	- N BY NCC MATRIX. (INPUT/OUTPUT)
//		    IF NCC.LE.0 C IS NOT USED. OTHERWISE, C
//		    IS REPLACED BY THE N BY NCC PRODUCT
//		    MATRIX UB**(T) * C. SEE REMARKS.
//	 IC	- ROW DIMENSION OF MATRIX C EXACTLY AS
//		    SPECIFIED IN THE DIMENSION STATEMENT IN THE
//		    CALLING PROGRAM. (INPUT)
//	 NCC	- NUMBER OF COLUMNS IN C. (INPUT)
//	 IER	- ERROR PARAMETER. (INPUT)
//		  WARNING ERROR
//		    IER=33 INDICATES THAT MATRIX B IS NOT FULL
//		      RANK OR VERY ILL-CONDITIONED. SMALL
//		      SINGULAR VALUES MAY NOT BE VERY ACCURATE.
//		  TERMINAL ERROR
//		    IER=129 INDICATES THAT CONVERGENCE WAS
//		      NOT ATTAINED AFTER 10*N QR SWEEPS.
//		      (CONVERGENCE USUALLY OCCURS IN ABOUT
//		      2*N SWEEPS).
//
//  PRECISION/HARDWARE	- SINGLE AND DOUBLE/H32
//		- SINGLE/H36,H48,H60
//
//  REQD. IMSL ROUTINES - LSVG1,LSVG2,VHS12,UERTST,UGETIO
//
//  NOTATION		- INFORMATION ON SPECIAL NOTATION AND
//		    CONVENTIONS IS AVAILABLE IN THE MANUAL
//		    INTRODUCTION OR THROUGH IMSL ROUTINE UHELP
//
//  REMARKS	 LSVDB COMPUTES THE SINGULAR VALUE DECOMPOSITION OF
//	 AN N BY N BIDIAGONAL MATRIX
//	      B = UB * S * VB**(T)    WHERE
//	 UB AND VB ARE N BY N ORTHOGONAL MATRICES AND
//	 S IS DIAGONAL.
//	 IF ARGUMENTS V AND C ARE N BY N IDENTITY MATRICES,
//	 ON EXIT THEY ARE REPLACED BY VB AND UB**T,
//	 RESPECTIVELY.
//
//  COPYRIGHT		- 1978 BY IMSL, INC. ALL RIGHTS RESERVED.
//
//  WARRANTY		- IMSL WARRANTS ONLY THAT IMSL TESTING HAS BEEN
//		    APPLIED TO THIS CODE. NO OTHER WARRANTY,
//		    EXPRESSED OR IMPLIED, IS APPLICABLE.
//
//----------------------------------------------------------------------
//
void LSVDB(double *fD,double *fE,int N,double *fV,int IV,
			int NRV,double *fC,int IC,int NCC,int *IER){
//C
//C				   SPECIFICATIONS FOR ARGUMENTS
//		INTEGER		 N,IV,NRV,IC,NCC,IER
//		DOUBLE PRECISION	 D(N),E(N),V(IV,1),C(IC,1)
FARRAY D,E,V,C;
DefineDimention(&D,fD,N,1); DefineDimention(&E,fE,N,1);
DefineDimention(&V,fV,IV,1); DefineDimention(&C,fC,IC,1);
//C				   SPECIFICATIONS FOR LOCAL VARIABLES
int	 I,II,J,K,KK,L,LL,LP1,NQRS,N10;
BOOL	 WNTV,HAVERS,FAIL;
double DNORM,ZERO = 0.0,ONE = 1.0,TWO = 2.0,CS,F,G,H,SN,T,X,Y,Z;
//      DATA		 ZERO/0.0D0/,ONE/1.0D0/,TWO/2.0D0/
//C				   FIRST EXECUTABLE STATEMENT
*IER = 0;
if (N <= 0) goto M9005;
N10 = 10 * N;
WNTV = (NRV > 0);
HAVERS = (NCC > 0);
FAIL = FALSE;
NQRS = 0;
FSetVal(&E,1,ZERO);
DNORM = ZERO;
for (J = 1; J <= N; J++){
M5: DNORM = DMAX1(DABS(FGetVal(&D,J)) + DABS(FGetVal(&E,J)),DNORM);}
for (KK = 1; KK <= N; KK++){
  K = N + 1 - KK;
//C				   TEST FOR SPLITTING OR RANK
//C				     DEFICIENCIES FIRST MAKE TEST FOR
//C				     LAST DIAGONAL TERM, D(K), BEING
//C				     SMALL.
  M10: if (K == 1) goto M25;
  T = DNORM + FGetVal(&D,K);
  if (T != DNORM) goto M25;
//C
//C				   SINCE D(K) IS SMALL WE WILL MAKE A
//C				     SPECIAL PASS TO TRANSFORM E(K) TO
//C				     ZERO.
  CS = ZERO;
  SN = -ONE;
  for (II = 2; II <= K; II++){
	 I = K + 1 - II;
	 F = -SN * FGetVal(&E,I+1);
	 FSetVal(&E,I+1,CS * FGetVal(&E,I+1));
	 T = FGetVal(&D,I);
	 LSVG1(T,F,&CS,&SN,FGetCell(&D,I,1));
//C				   TRANSFORMATION CONSTRUCTED TO ZERO
//C				     POSITION (I,K).
	 if (!WNTV) goto M20;
	 for (J=1; J <= NRV; J++){// 15
	 M15: LSVG2(CS,SN,FGetCell(&V,J,I),FGetCell(&V,J,K));}
//C
//C				   ACCUMULATE RT. TRANSFORMATIONS IN V.
  M20:;} //	 CONTINUE
//C				   THE MATRIX IS NOW BIDIAGONAL, AND OF
//C				     LOWER ORDER SINCE E(K) .EQ. ZERO
  M25: for(LL = 1; LL <= K; LL++) { // 30
			L = K+1-LL;
			T = DNORM + FGetVal(&E,L);
			if (T == DNORM) goto M50;
			T = DNORM + FGetVal(&D,L-1);
		 if (T == DNORM) goto M35;
		 M30:;} //	 CONTINUE
//C				   THIS LOOP CANT COMPLETE SINCE E(1) =
//C				     ZERO.
  goto M50;
//C				   CANCELLATION OF E(L), L.GT.1.
  M35: CS = ZERO;
  SN = -ONE;
  for (I = L; I <= K; I++){ // 45
	 F = -SN * FGetVal(&E,I);
	 FSetVal(&E,I,CS * FGetVal(&E,I));
	 T = DNORM + F;
	 if (T == DNORM) goto M50;
	 T = FGetVal(&D,I);
	 LSVG1(T,F,&CS,&SN,FGetCell(&D,I,1));
	 if (!HAVERS) goto M45;
	 for (J = 1; J <= NCC; J++){  //40
	 M40: LSVG2(CS,SN,FGetCell(&C,I,J),FGetCell(&C,L-1,J));}
  M45:;} //	 CONTINUE
//C				   TEST FOR CONVERGENCE
  M50:  Z = FGetVal(&D,K);
  if (L == K) goto M85;
//C				   SHIFT FROM BOTTOM 2 BY 2 MINOR OF
//C				     B**(T)*B.
  X = FGetVal(&D,L);
  Y = FGetVal(&D,K-1);
  G = FGetVal(&E,K-1);
  H = FGetVal(&E,K);
  F = ((Y-Z) * (Y+Z) + (G-H) * (G+H))/(TWO * H * Y);
  G = DSQRT(ONE + F*F);
  if (F < ZERO) goto M55;
  T = F + G;
  goto M60;
  M55: T = F - G;
  M60: F = ((X-Z) * (X+Z) + H * (Y/T - H))/X;
//C				   NEXT QR SWEEP
  CS = ONE;
  SN = ONE;
  LP1 = L+1;
  for (I = LP1; I <= K; I++){  // 80
	 G = FGetVal(&E,I);
	 Y = FGetVal(&D,I);
	 H = SN * G;
	 G = CS * G;
	 LSVG1(F,H,&CS,&SN,FGetCell(&E,I-1,1));
	 F = X * CS + G * SN;
	 G = -X * SN + G * CS;
	 H = Y * SN;
	 Y = Y * CS;
	 if (!WNTV) goto M70;
//C				   ACCUMULATE ROTATIONS (FROM THE
//C				     RIGHT) IN V
	 for (J = 1; J <= NRV; J++){ //65
	 M65:	 LSVG2(CS,SN,FGetCell(&V,J,I-1),FGetCell(&V,J,I));}
	 M70:  LSVG1(F,H,&CS,&SN,FGetCell(&D,I-1,1));
	 F = CS * G + SN * Y;
	 X = -SN * G + CS * Y;
	 if (!HAVERS) goto M80;
	 for (J = 1; J <= NCC; J++){ //75
	 M75:	LSVG2(CS,SN,FGetCell(&C,I-1,J),FGetCell(&C,I,J));}
//C
//C				   APPLY ROTATIONS FROM THE LEFT TO
//C				     RIGHT HAND SIDES IN C
  M80:;}//	 CONTINUE
  FSetVal(&E,L,ZERO);
  FSetVal(&E,K,F);
  FSetVal(&D,K,X);
  NQRS = NQRS + 1;
  if (NQRS <= N10) goto M10;
//C				   RETURN TO TEST FOR SPLITTING.
  FAIL = TRUE;
//C				   CUTOFF FOR CONVERGENCE FAILURE. NQRS
//C				     WILL BE 2*N USUALLY.
  M85: if (Z >= ZERO) goto M95;
  FSetVal(&D,K,-Z);
  if (!WNTV) goto M95;
  for (J = 1; J <= NRV; J++){  // 90
  M90: FSetVal2(&V,J,K,-FGetVal2(&V,J,K));}
  M95: //	 CONTINUE
//C				   CONVERGENCE. D(K) IS MADE
//C				     NONNEGATIVE
M100:;} // CONTINUE
if (N == 1) goto M140;
for (I = 2; I <= N; I++){  // 105
  if (FGetVal(&D,I) > FGetVal(&D,I-1)) goto M110;
M105:;} // CONTINUE
goto M140;
//C				   EVERY SINGULAR VALUE IS IN ORDER
M110: for (I = 2; I <= N; I++){  // 135
  T = FGetVal(&D,I-1);
  K = I-1;
  for (J = I; J <= N; J++){  // 115
	 if (T >= FGetVal(&D,J)) goto M115;
	 T = FGetVal(&D,J);
	 K = J;
  M115:;} //	 CONTINUE
  if (K == (I-1)) goto M135;
  FSetVal(&D,K,FGetVal(&D,I-1));
  FSetVal(&D,I-1,T);
  if (!HAVERS) goto M125;
  for (J = 1; J <= NCC; J++){  // 120
	 T = FGetVal2(&C,I-1,J);
	 FSetVal2(&C,I-1,J,FGetVal2(&C,K,J));
  M120: FSetVal2(&C,K,J,T); }
  M125: if (!WNTV) goto M135;
  for (J = 1; J <= NRV; J++){  // 130
	 T = FGetVal2(&V,J,I-1);
	 FSetVal2(&V,J,I-1,FGetVal2(&V,J,K));
  M130:	FSetVal2(&V,J,K,T); }
M135:;} // CONTINUE
//C				   END OF ORDERING ALGORITHM.
M140: *IER = 129;
if (FAIL) goto M9000;
//C				   CHECK FOR POSSIBLE RANK DEFICIENCY
*IER = 33;
T = 0.0;
if (FGetVal(&D,1) != ZERO) T = FGetVal(&D,N) / FGetVal(&D,1);
F = 100.0 + T;
if (F == 100.0) goto M9000;
*IER = 0;
goto M9005;
M9000: // CONTINUE
UERTST(*IER,"LSVDB ");
M9005:;} // RETURN
//		END
//C   IMSL ROUTINE NAME	- LSVG1
//C
//C-----------------------------------------------------------------------
//C
//C   COMPUTER		- DEC11/DOUBLE
//C
//C   LATEST REVISION	- JANUARY 1, 1978
//C
//C   PURPOSE		- NUCLEUS CALLED ONLY BY IMSL ROUTINE LSVDB
//C
//C   PRECISION/HARDWARE	- SINGLE AND DOUBLE/H32
//C			- SINGLE/H36,H48,H60
//C
//C   REQD. IMSL ROUTINES - NONE REQUIRED
//C
//C   NOTATION		- INFORMATION ON SPECIAL NOTATION AND
//C			    CONVENTIONS IS AVAILABLE IN THE MANUAL
//C			    INTRODUCTION OR THROUGH IMSL ROUTINE UHELP
//C
//C   COPYRIGHT		- 1978 BY IMSL, INC. ALL RIGHTS RESERVED.
//C
//C   WARRANTY		- IMSL WARRANTS ONLY THAT IMSL TESTING HAS BEEN
//C			    APPLIED TO THIS CODE. NO OTHER WARRANTY,
//C			    EXPRESSED OR IMPLIED, IS APPLICABLE.
//C
//C-----------------------------------------------------------------------
//C
void LSVG1(double A,double B,double *DCOS,double *DSIN,double *SIG){
//C
//C				   SPECIFICATIONS FOR ARGUMENTS
//		DOUBLE PRECISION	 A,B,DCOS,DSIN,SIG
//C				   SPECIFICATIONS FOR LOCAL VARIABLES
double AA,BB;
//C				   FIRST EXECUTABLE STATEMENT
if (DABS(A) <= DABS(B)) goto M5;
AA = DABS(A+A);
*SIG = AA * DSQRT(0.25 + (B / AA) * (B / AA));
*DCOS = A / *SIG;
*DSIN = B / *SIG;
goto ret; //		RETURN
M5: if (B == 0.0) goto M10;
BB = DABS(B + B);
*SIG = BB * DSQRT(0.25 + (A / BB) * (A / BB));
*DCOS = A / *SIG;
*DSIN = B / *SIG;
goto ret;
M10: *SIG = 0.0;
	  *DCOS = 0.0;
	  *DSIN = 1.0;
ret:;} //		RETURN
//		END
//C   IMSL ROUTINE NAME	- LSVG2
//C
//C-----------------------------------------------------------------------
//C
//C   COMPUTER		- DEC11/DOUBLE
//C
//C   LATEST REVISION	- JANUARY 1, 1978
//C
//C   PURPOSE		- NUCLEUS CALLED ONLY BY IMSL ROUTINE LSVDB
//C
//C   PRECISION/HARDWARE	- SINGLE AND DOUBLE/H32
//C			- SINGLE/H36,H48,H60
//C
//C   REQD. IMSL ROUTINES - NONE REQUIRED
//C
//C   NOTATION		- INFORMATION ON SPECIAL NOTATION AND
//C			    CONVENTIONS IS AVAILABLE IN THE MANUAL
//C			    INTRODUCTION OR THROUGH IMSL ROUTINE UHELP
//C
//C   COPYRIGHT		- 1978 BY IMSL, INC. ALL RIGHTS RESERVED.
//C
//C   WARRANTY		- IMSL WARRANTS ONLY THAT IMSL TESTING HAS BEEN
//C			    APPLIED TO THIS CODE. NO OTHER WARRANTY,
//C			    EXPRESSED OR IMPLIED, IS APPLICABLE.
//C
//C-----------------------------------------------------------------------
//C
void LSVG2(double DCOS,double DSIN,double *X,double *Y){
//C
//C				   SPECIFICATIONS FOR ARGUMENTS
//		DOUBLE PRECISION	 DCOS,DSIN,X,Y
//C				   SPECIFICATIONS FOR LOCAL VARIABLES
double XR;
//C				   FIRST EXECUTABLE STATEMENT
XR = DCOS * *X + DSIN * *Y;
*Y = -DSIN * *X + DCOS * *Y;
*X = XR;}
//		RETURN
//		END
//C   IMSL ROUTINE NAME	- UERSET
//C
//C-----------------------------------------------------------------------
//C
//C   COMPUTER		- DEC11/SINGLE
//C
//C   LATEST REVISION	- JANUARY 1, 1978
//C
//C   PURPOSE		- SET MESSAGE LEVEL FOR IMSL ROUTINE UERTST
//C
//C   USAGE		- CALL UERSET (LEVEL,LEVOLD)
//C
//C   ARGUMENTS	 LEVEL	- NEW VALUE FOR MESSAGE LEVEL. (INPUT)
//C			    OUTPUT FROM IMSL ROUTINE UERTST IS
//C			    CONTROLLED SELECTIVELY AS FOLLOWS,
//C			      LEVEL = 4 CAUSES ALL MESSAGES TO BE
//C					PRINTED,
//C			      LEVEL = 3 MESSAGES ARE PRINTED IF IER IS
//C					GREATER THAN 32,
//C			      LEVEL = 2 MESSAGES ARE PRINTED IF IER IS
//C					GREATER THAN 64,
//C			      LEVEL = 1 MESSAGES ARE PRINTED IF IER IS
//C					GREATER THAN 128,
//C			      LEVEL = 0 ALL MESSAGE PRINTING IS
//C					SUPPRESSED.
//C		 LEVOLD - PREVIOUS MESSAGE LEVEL. (OUTPUT)
//C
//C   PRECISION/HARDWARE	- SINGLE/ALL
//C
//C   REQD. IMSL ROUTINES - UERTST,UGETIO
//C
//C   NOTATION		- INFORMATION ON SPECIAL NOTATION AND
//C			    CONVENTIONS IS AVAILABLE IN THE MANUAL
//C			    INTRODUCTION OR THROUGH IMSL ROUTINE UHELP
//C
//C   COPYRIGHT		- 1978 BY IMSL, INC. ALL RIGHTS RESERVED.
//C
//C   WARRANTY		- IMSL WARRANTS ONLY THAT IMSL TESTING HAS BEEN
//C			    APPLIED TO THIS CODE. NO OTHER WARRANTY,
//C			    EXPRESSED OR IMPLIED, IS APPLICABLE.
//C
//C-----------------------------------------------------------------------
//C
void UERSET(int LEVEL, int *LEVOLD){
//C				   SPECIFICATIONS FOR ARGUMENTS
//		INTEGER		 LEVEL,LEVOLD
//C				   FIRST EXECUTABLE STATEMENT
*LEVOLD = LEVEL;
UERTST(*LEVOLD,"UERSET");
}//		RETURN
//		END
//C-----------------------------------------------------------------------
//C
//C   COMPUTER		- DEC11/SINGLE
//C
//C   LATEST REVISION	- JANUARY 1, 1978
//C
//C   PURPOSE		- PRINT A MESSAGE REFLECTING AN ERROR CONDITION
//C
//C   USAGE		- CALL UERTST (IER,NAME)
//C
//C   ARGUMENTS	 IER	- ERROR PARAMETER. (INPUT)
//C			    IER = I+J WHERE
//C			      I = 128 IMPLIES TERMINAL ERROR,
//C			      I =  64 IMPLIES WARNING WITH FIX, AND
//C			      I =  32 IMPLIES WARNING.
//C			      J = ERROR CODE RELEVANT TO CALLING
//C				  ROUTINE.
//C		 NAME	- A SIX CHARACTER LITERAL STRING GIVING THE
//C			    NAME OF THE CALLING ROUTINE. (INPUT)
//C
//C   PRECISION/HARDWARE	- SINGLE/ALL
//C
//C   REQD. IMSL ROUTINES - UGETIO
//C
//C   NOTATION		- INFORMATION ON SPECIAL NOTATION AND
//C			    CONVENTIONS IS AVAILABLE IN THE MANUAL
//C			    INTRODUCTION OR THROUGH IMSL ROUTINE UHELP
//C
//C   REMARKS	 THE ERROR MESSAGE PRODUCED BY UERTST IS WRITTEN
//C		 ONTO THE STANDARD OUTPUT UNIT. THE OUTPUT UNIT
//C		 NUMBER CAN BE DETERMINED BY CALLING UGETIO AS
//C		 FOLLOWS..   CALL UGETIO(1,NIN,NOUT).
//C		 THE OUTPUT UNIT NUMBER CAN BE CHANGED BY CALLING
//C		 UGETIO AS FOLLOWS..
//C				 NIN = 0
//C				 NOUT = NEW OUTPUT UNIT NUMBER
//C				 CALL UGETIO(3,NIN,NOUT)
//C		 SEE THE UGETIO DOCUMENT FOR MORE DETAILS.
//C
//C   COPYRIGHT		- 1978 BY IMSL, INC. ALL RIGHTS RESERVED.
//C
//C   WARRANTY		- IMSL WARRANTS ONLY THAT IMSL TESTING HAS BEEN
//C			    APPLIED TO THIS CODE. NO OTHER WARRANTY,
//C			    EXPRESSED OR IMPLIED, IS APPLICABLE.
//C
//C-----------------------------------------------------------------------
//C
void UERTST(int IER,PSTR NAME){
//C				   SPECIFICATIONS FOR ARGUMENTS
//		INTEGER		 IER,NAME(3)
//C				   SPECIFICATIONS FOR LOCAL VARIABLES
char NAMSET[] = "UERSET";
char NAMEQ[] = "      ";
//		DATA		 NAMSET/2HUE,2HRS,2HET/
//		DATA		 NAMEQ/2H  ,2H  ,2H  /
//C				   FIRST EXECUTABLE STATEMENT
int LEVEL = 4, IEQDF = 0, LEVOLD; char IEQ = '=';
char format35[] = "TERMINAL ERROR,10X,7H(IER = %i) FROM IMSL ROUTINE %s%c%s";
char format40[] = "WARNING WITH FIX ERROR  (IER = %i) FROM IMSL ROUTINE %s%c%s";
char format45[] = "WARNING ERROR,11X,7H(IER = %i) FROM IMSL ROUTINE %s%c%s";
char format50[] = "UNDEFINED ERROR,9X,7H(IER = %i) FROM IMSL ROUTINE %s%c%s";
//
if (IER > 999) goto M25;
if (IER < -32) goto M55;
if (IER <= 128) goto M5;
if (LEVEL < 1) goto M30;
//C				   PRINT TERMINAL MESSAGE
//		CALL UGETIO(1,NIN,IOUNIT)
if (IEQDF == 1) WinPrint(format35,IER,NAMEQ,IEQ,NAME);
if (IEQDF == 0) WinPrint(format35,IER,NAME,' '," ");
goto M30;
M5: if (IER <= 64) goto M10;
if (LEVEL < 2) goto M30;
//C				   PRINT WARNING WITH FIX MESSAGE
//      CALL UGETIO(1,NIN,IOUNIT)
if (IEQDF == 1) WinPrint(format40,IER,NAMEQ,IEQ,NAME);
if (IEQDF == 0) WinPrint(format40,IER,NAME,' '," ");
goto M30;
M10: if (IER <= 32) goto M15;
//C				   PRINT WARNING MESSAGE
if (LEVEL < 3) goto M30;
//		CALL UGETIO(1,NIN,IOUNIT)
if (IEQDF == 1) WinPrint(format45,IER,NAMEQ,IEQ,NAME);
if (IEQDF == 0) WinPrint(format45,IER,NAME,' '," ");
goto M30;
M15: // CONTINUE
//C			CHECK FOR UERSET CALL
int I;
for (I = 0; I < 3; I++){
  if (NAME[I]!= NAMSET[I]) goto M25;
  M20:;} // CONTINUE
LEVOLD = LEVEL;
LEVEL = IER;
IER = LEVOLD;
if (LEVEL < 0) LEVEL = 4;
if (LEVEL > 4) LEVEL = 4;
goto M30;
M25: // CONTINUE
if (LEVEL < 4) goto M30;
//C				   PRINT NON-DEFINED MESSAGE
//		CALL UGETIO(1,NIN,IOUNIT)
if (IEQDF == 1) WinPrint(format50,IER,NAMEQ,IEQ,NAME);
if (IEQDF == 0) WinPrint(format50,IER,NAME,' '," ");
M30: IEQDF = 0;
//		RETURN
//	35 FORMAT(19H *** TERMINAL ERROR,10X,7H(IER = ,I3,
//	  1	     20H) FROM IMSL ROUTINE ,3A2,A1,3A2)
//	40 FORMAT(36H *** WARNING WITH FIX ERROR  (IER = ,I3,
//	  1	     20H) FROM IMSL ROUTINE ,3A2,A1,3A2)
//	45 FORMAT(18H *** WARNING ERROR,11X,7H(IER = ,I3,
//	  1	     20H) FROM IMSL ROUTINE ,3A2,A1,3A2)
//	50 FORMAT(20H *** UNDEFINED ERROR,9X,7H(IER = ,I5,
//	  1	     20H) FROM IMSL ROUTINE ,3A2,A1,3A2)
//C				   SAVE P FOR P = R CASE
//C				     P IS THE PAGE NAME
//C				     R IS THE ROUTINE NAME
M55: IEQDF = 1;
for (I = 0; I < 3; I++){
M60: NAMEQ[I] = NAME[I];}
M65:;} // RETURN
//		END
//C   IMSL ROUTINE NAME	- UGETIO
//C
//C-----------------------------------------------------------------------
//C
//C   COMPUTER		- DEC11/SINGLE
//C
//C   LATEST REVISION	- JANUARY 1, 1978
//C
//C   PURPOSE		- TO RETRIEVE CURRENT VALUES AND TO SET NEW
//C			    VALUES FOR INPUT AND OUTPUT UNIT
//C			    IDENTIFIERS.
//C
//C   USAGE		- CALL UGETIO(IOPT,NIN,NOUT)
//C
//C   ARGUMENTS	 IOPT	- OPTION PARAMETER. (INPUT)
//C			    IF IOPT=1, THE CURRENT INPUT AND OUTPUT
//C			    UNIT IDENTIFIER VALUES ARE RETURNED IN NIN
//C			    AND NOUT, RESPECTIVELY.
//C			    IF IOPT=2 (3) THE INTERNAL VALUE OF
//C			    NIN (NOUT) IS RESET FOR SUBSEQUENT USE.
//C		 NIN	- INPUT UNIT IDENTIFIER.
//C			    OUTPUT IF IOPT=1, INPUT IF IOPT=2.
//C		 NOUT	- OUTPUT UNIT IDENTIFIER.
//C			    OUTPUT IF IOPT=1, INPUT IF IOPT=3.
//C
//C   PRECISION/HARDWARE	- SINGLE/ALL
//C
//C   REQD. IMSL ROUTINES - NONE REQUIRED
//C
//C   NOTATION		- INFORMATION ON SPECIAL NOTATION AND
//C			    CONVENTIONS IS AVAILABLE IN THE MANUAL
//C			    INTRODUCTION OR THROUGH IMSL ROUTINE UHELP
//C
//C   REMARKS	 EACH IMSL ROUTINE THAT PERFORMS INPUT AND/OR OUTPUT
//C		 OPERATIONS CALLS UGETIO TO OBTAIN THE CURRENT UNIT
//C		 IDENTIFIER VALUES. IF UGETIO IS CALLED WITH IOPT=2 OR 3
//C		 NEW UNIT IDENTIFIER VALUES ARE ESTABLISHED. SUBSEQUENT
//C		 INPUT/OUTPUT IS PERFORMED ON THE NEW UNITS.
//C
//C   COPYRIGHT		- 1978 BY IMSL, INC. ALL RIGHTS RESERVED.
//C
//C   WARRANTY		- IMSL WARRANTS ONLY THAT IMSL TESTING HAS BEEN
//C			    APPLIED TO THIS CODE. NO OTHER WARRANTY,
//C			    EXPRESSED OR IMPLIED, IS APPLICABLE.
//C
//C-----------------------------------------------------------------------
//C
//		SUBROUTINE UGETIO(IOPT,NIN,NOUT)
//C				   SPECIFICATIONS FOR ARGUMENTS
//      INTEGER		 IOPT,NIN,NOUT
//C				   SPECIFICATIONS FOR LOCAL VARIABLES
//      INTEGER		 NIND,NOUTD
//      DATA		 NIND/1/,NOUTD/2/
//C				   FIRST EXECUTABLE STATEMENT
//      if (IOPT == 3) goto M10
//      if (IOPT == 2) goto M5
//      if (IOPT.NE.1) goto M9005
//      NIN = NIND
//      NOUT = NOUTD
//      goto M9005
//    5 NIND = NIN
//      goto M9005
//	10 NOUTD = NOUT
// 9005 RETURN
//      END
//C
//C
//C   IMSL ROUTINE NAME	- VHS12
//C
//C-----------------------------------------------------------------------
//C
//C   COMPUTER		- DEC11/DOUBLE
//C
//C   LATEST REVISION	- JANUARY 1, 1978
//C
//C   PURPOSE		- REAL HOUSEHOLDER TRANSFORMATION -
//C			    COMPUTATION AND APPLICATIONS.
//C
//C   USAGE		- CALL VHS12 (MODE,LP,L1,M,U,INCU,UP,C,INCC,
//C			    ICV,NCV)
//C
//C   ARGUMENTS	 MODE	- OPTION PARAMETER. (INPUT)
//C			  if MODE=1, THE SUBROUTINE COMPUTES A
//C			    HOUSEHOLDER TRANSFORMATION AND if NCV.GT.0,
//C			    MULTIPLIES IT BY THE SET OF NCV VECTORS
//C			    (EACH OF LENGTH M) STORED IN C. FOR A
//C			    GIVEN VECTOR V OF LENGTH M AND TWO INTEGER
//C			    INDICES LP AND L1 THAT SATISFY
//C			    1 .LE. LP .LT. L1 .LE. M, THE SUBROUTINE
//C			    DEFINES AN M BY M HOUSEHOLDER
//C			    TRANSFORMATION Q WHICH SATIFIES QV=W WHERE
//C			    W(I)=V(I) FOR I.LT.LP
//C			    W(LP)=-SIG*SQRT(V(LP)**2+V(L1)**2+...
//C			      +V(M)**2)
//C			      SIG=1  if V(LP) >= 0
//C			      SIG=-1 if V(LP).LT.0
//C			    W(I)=V(I) FOR LP.LT.I.LT.L1
//C			    W(I)=0    FOR I.GE.L1.
//C			  if MODE=2, THE SUBROUTINE ASSUMES THAT A
//C			    HOUSEHOLDER TRANSFORMATION HAS ALREADY
//C			    BEEN DEFINED BY A PREVIOUS CALL WITH
//C			    MODE=1, AND if NCV.GT.0, MULTIPLIES IT BY
//C			    THE SET OF NCV VECTORS (EACH OF LENGTH
//C			    M) STORED IN C.
//C		 LP	- PARAMETERS THAT DEFINE THE DESIRED
//C		 L1	    HOUSEHOLDER TRANSFORMATION. (INPUT)
//C		 M	    if THE CONDITION 1.LE.LP.LT.L1.LE.M IS
//C			    NOT SATISFIED, THE SUBROUTINE RETURNS TO
//C			    THE CALLING PROGRAM WITHOUT PERFORMING
//C			    ANY COMPUTATIONS.
//C		 U	- VECTOR OF M ELEMENTS. (INPUT, AND OUTPUT IF
//C			    MODE=1)
//C			    THE STORAGE INCREMENT BETWEEN ELEMENTS
//C			    OF U IS INCU. (I.E., U(1+(J-1)*INCU),
//C			    J=1,...,M). IF MODE=1, THE ARRAY V IS
//C			    DEFINED AS V(J)=U(1+(J-1)*INCU),
//C			    J=1,...,M.
//C			  ON OUTPUT, U(1+(LP-1)*INCU) IS SET TO
//C			    W(LP) (AS DEFINED ABOVE IN THE DESCRIPTION
//C			    OF MODE=1).
//C		 INCU	- INCREMENT BETWEEN ELEMENTS OF U. (INPUT)
//C		 UP	- SCALAR SET TO V(LP)-W(LP) TO DEFINE THE
//C			    HOUSEHOLDER TRANSFORMATION Q. (INPUT IF
//C			    MODE=2, OUTPUT IF MODE=1)
//C		 C	- VECTOR OF NCV*M ELEMENTS. (INPUT/OUTPUT)
//C			    IF NCV.LE.0, C IS NOT USED.
//C			    IF NCV.GT.0, C CONTAINS NCV VECTORS
//C			    OF LENGTH M WITH INCREMENT INCC BETWEEN
//C			    ELEMENTS OF VECTORS AND INCREMENT ICV
//C			    BETWEEN VECTORS. ELEMENT I OF VECTOR J IS
//C			    DEFINED AS C(1+(I-1)*INCC+(J-1)*ICV),
//C			    I=1,...,M AND J=1,...,NCV.
//C			  ON OUTPUT, C CONTAINS THE SET OF NCV
//C			    VECTORS RESULTING FROM MULTIPLYING
//C			    THE GIVEN VECTORS BY Q.
//C		 INCC	- INCREMENT BETWEEN ELEMENTS OF VECTORS
//C			    IN C. (INPUT)
//C		 ICV	- INCREMENT BETWEEN VECTORS IN C. (INPUT)
//C		 NCV	- NUMBER OF VECTORS STORED IN C. (INPUT)
//C
//C   PRECISION/HARDWARE	- SINGLE AND DOUBLE/H32
//C			- SINGLE/H36,H48,H60
//C
//C   REQD. IMSL ROUTINES - NONE REQUIRED
//C
//C   NOTATION		- INFORMATION ON SPECIAL NOTATION AND
//C			    CONVENTIONS IS AVAILABLE IN THE MANUAL
//C			    INTRODUCTION OR THROUGH IMSL ROUTINE UHELP
//C
//C   REMARKS  1.  IF U IS A SINGLE SUBSCRIPTED ARRAY OR THE J-TH COLUMN
//C		 OF A MATRIX, THEN INCU=1. IF U IS THE I-TH ROW OF A
//C		 MATRIX THEN INCU IS THE ROW DIMENSION OF THE MATRIX
//C		 EXACTLY AS SPECIFIED IN THE CALLING PROGRAM.
//C	     2.  IF C IS A DOUBLE SUBSCRIPTED MATRIX AND THE VECTORS
//C		 ARE THE FIRST NCV COLUMNS OF C, THEN INCC=1 AND ICV
//C		 IS THE ROW DIMENSION OF C EXACTLY AS SPECIFIED IN
//C		 THE CALLING PROGRAM. IN THIS CASE C IS REPLACED
//C		 BY QC. IF THE VECTORS ARE SUCCESSIVE ROWS OF C
//C		 THEN INCC IS THE ROW DIMENSION OF C EXACTLY AS
//C		 SPECIFIED IN THE CALLING PROGRAM AND ICV=1. IN THIS
//C		 CASE C IS REPLACED BY CQ.
//C
//C   COPYRIGHT		- 1978 BY IMSL, INC. ALL RIGHTS RESERVED.
//C
//C   WARRANTY		- IMSL WARRANTS ONLY THAT IMSL TESTING HAS BEEN
//C			    APPLIED TO THIS CODE. NO OTHER WARRANTY,
//C			    EXPRESSED OR IMPLIED, IS APPLICABLE.
//C
//C-----------------------------------------------------------------------
//C
void VHS12(int MODE,int LP,int L1,int M,double *fU,int INCU,
		 double *UP,double *fC,int INCC,int ICV,int NCV){
//C
//C				   SPECIFICATIONS FOR ARGUMENTS
//		INTEGER		 MODE,LP,L1,M,INCU,INCC,ICV,NCV
//		DOUBLE PRECISION	 U(1),UP,C(1)
FARRAY U,C;
DefineDimention(&U,fU,1,1); DefineDimention(&C,fC,1,1);
//C				   SPECIFICATIONS FOR LOCAL VARIABLES
int IJ,ILP,IL1,IM,INCR,I2,I3,I4,J;
double SM,B;
double ONE = 1.0,CL,CLINV,SM1;
//C				   FIRST EXECUTABLE STATEMENT
//		ONE = 1.D0
//C
if ((0 >= LP) || (LP >= L1) || (L1 > M)) goto M9005;
ILP = (LP-1) * INCU + 1;
IL1 = (L1-1) * INCU + 1;
IM = (M-1) * INCU + 1;
CL = DABS(FGetVal(&U,ILP));
if (MODE == 2) goto M15;
//C				   CONSTRUCT THE TRANSFORMATION.
for (IJ = IL1; IJ <= IM; IJ += INCU){  // 5
M5: CL = DMAX1(DABS(FGetVal(&U,IJ)),CL);}
if (CL <= 0.0) goto M9005;
CLINV = ONE / CL;
SM = (FGetVal(&U,ILP) * CLINV) * (FGetVal(&U,ILP) * CLINV);
for (IJ = IL1; IJ <= IM; IJ += INCU){  // 10
M10: SM = SM + (FGetVal(&U,IJ) * CLINV) * (FGetVal(&U,IJ) * CLINV);}
//C				   CONVERT DBLE. PREC. SM TO SNGL.
//C				     PREC. SM1
SM1 = SM;
CL = CL * DSQRT(SM1);
if (FGetVal(&U,ILP) > 0.0) CL = -CL;
*UP = FGetVal(&U,ILP) - CL;
FSetVal(&U,ILP,CL);
goto M20;
//C				   APPLY THE TRANSFORMATION
//C				     I+U*(U**T)/B TO C.
M15: if (CL <= 0.0) goto M9005;
M20: if (NCV <= 0) goto M9005;
B = *UP * FGetVal(&U,ILP);
//C				   B MUST BE NONPOSITIVE HERE. IF B =
//C				     0., RETURN.
if (B >= 0.0) goto M9005;
B = ONE / B;
I2 = 1 - ICV + INCC * (LP - 1);
INCR = INCC * (L1 - LP);
for (J = 1; J <= NCV; J++){  // 35
  I2 = I2 + ICV;
  I3 = I2 + INCR;
  I4 = I3;
  SM = FGetVal(&C,I2) * *UP;
  for (IJ = IL1; IJ <= IM; IJ += INCU){  // 25
	 SM = SM + FGetVal(&C,I3) * FGetVal(&U,IJ);
	 I3 = I3+INCC;
  M25:;} //	 CONTINUE
  if (SM == 0.0) goto M35;
  SM = SM * B;
  FSetVal(&C,I2,FGetVal(&C,I2) + SM * *UP);
  for (IJ = IL1; IJ <= IM; IJ += INCU){ // 30
	 FSetVal(&C,I4,FGetVal(&C,I4) + SM * FGetVal(&U,IJ));
	 I4 = I4 + INCC;
  M30:;} //	 CONTINUE
M35:;} // CONTINUE
M9005:;} // RETURN
//		END
//C
//C
//C



CMatrix CMatrix::GetColumn(const int n) const {
	if ((n >= nx) || (n < 0)) return CMatrix(0,0);
	CMatrix R(1,ny);
	int ct;
	for (ct = 0; ct < ny; ct++)	R.Set(0,ct,Get(n,ct));
	return R;
}


void CMatrix::DelColumn(const int n){ // Не слишком быстрая реализация
	if (IsEmpty()) return;
	if (nx == 1){ delete [] a; nx = 0; ny = 0; return;}
	double* newdata = new double[(nx - 1) * ny];
	double *src, *dst;
	int ctx, cty;
	for (cty = 0; cty < ny; cty++){
	// копирование
	   if (n > 0){ // левая часть существует
		   src = a + cty * nx;
		   dst = newdata + cty * (nx - 1);
		   memcpy(dst,src,sizeof(double) * n);
	   }
	   if (n < (nx - 1)){ // правая часть существует
		   src = a + cty * nx + n + 1;
		   dst = newdata + cty * (nx - 1) + n;
		   memcpy(dst,src,sizeof(double) * (nx - 1 - n));
	   }
	}
	nx--;
	delete [] a;
	a = newdata;
}