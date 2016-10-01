// Matrix.h: interface for the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX_H__45E0EDA1_EFA8_11D4_BE78_92D09C0D5C71__INCLUDED_)
#define AFX_MATRIX_H__45E0EDA1_EFA8_11D4_BE78_92D09C0D5C71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMatrix : public CObject{  
protected:
	int nx, ny;
	double *a;
public:
	CMatrix(const int x = 0, const int y = 0);
	CMatrix(const CMatrix& M) : nx(M.nx), ny(M.ny) { // ����������� �����
		a = new double[nx * ny];
		memcpy(a,M.a, sizeof(double) * nx * ny);
	}
	virtual ~CMatrix();

	// ������ � ������
	inline double Get(const int x, const int y) const {
		double *p;
		p = a + y * nx + x; return *p;}
	inline void Set(const int x, const int y, const double z){
		double *p;
		p = a + y * nx + x; *p = z;}
	CSize GetSize() const { return CSize(nx,ny); } 
	double* GetData() const { return a; }

	// ��������
	inline bool IsEmpty(){ if ((nx == 0) || (ny == 0)) return true; else return false;}
	void Transpose(); // ���������������� �������
	CMatrix& operator=(const CMatrix&);
	CMatrix operator*(const CMatrix&) const; // ��������� ���������
	void operator *=(const double x); // ��������� ��������� ������� �� �����
	CMatrix GetColumn(const int n) const;
	void DelColumn(const int n);
	void Zero(); // �������� ���������� ������� �� ������� �� ��������
	// ���� ������� ������ �� ��������� ���������, ������������ ������ �������
	// ���������������
	CMatrix Inverse();

};

#endif // !defined(AFX_MATRIX_H__45E0EDA1_EFA8_11D4_BE78_92D09C0D5C71__INCLUDED_)
