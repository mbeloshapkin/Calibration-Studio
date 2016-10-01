// CalibratorDlg.h : header file
//

#if !defined(AFX_CALIBRATORDLG_H__3FC8F40E_0819_4C0F_8F40_6B2EEB40B15F__INCLUDED_)
#define AFX_CALIBRATORDLG_H__3FC8F40E_0819_4C0F_8F40_6B2EEB40B15F__INCLUDED_

#include "Matrix.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCalibratorDlg dialog
#include "Calpoint.h"
#include "Matrix.h"


typedef struct tagCALDATA{
	double K1,K2;
	double MSXmm; // = 22.5, 
	double MSYmm; // = 15; // Размер матрицы в мм 
	double MSXPix; // = 3504, 
	double MSYPix; //= 2336;
	double X0;		// = MSXmm / 2, 
	double Y0;		// = MSYmm / 2;
	double AI[100],BI[100];
} CALDATA, *PCALDATA;
//
//					HASSEL	Cannon	
#define		SX_MM	49.0	//22.5
#define		SY_MM	36.7	//15.0
#define		SX_PIX	5440.0	//3504.0
#define		SY_PIX	4080.0	//2336.0
#define		K1_INI	0.0001

class CCalibratorDlg : public CDialog{
// Construction
	int nlHor, nlVert;   // Число струн
	int np;				// Число точек
	int npHor, npVert;
	CALPOINT Points[1000];
	char Buf[10000];
	int BufLen;
	int ptr;

	CMatrix* M1;
	CMatrix* M2;
	CMatrix* M3;
	CMatrix* M4;
	CMatrix* L;


public:
	
	CMatrix MakeEqLine(int lnum);
	double dFidA(double x, double y);
	void ParseStr(CString& str);
	CCalibratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCalibratorDlg)
	enum { IDD = IDD_CALIBRATOR_DIALOG };
	double	m_SizeXmm;
	double	m_SizeYmm;
	int		m_SizeYpix;
	int		m_SizeXpix;
	int		m_MaxIterations;
	double	m_Precision;
	double	m_K1;
	double	m_K1Ini;
	double	m_K2;
	double	m_MaxErr;
	double	m_SQD;
	double	m_WightX0Y0;
	double	m_X0;
	double	m_Y0;
	int		m_K1Only;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalibratorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCalibratorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLoadData();
	afx_msg void OnCalibrate();
	afx_msg void OnCreateReport();
	afx_msg void OnRestore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
	int CalcNLines();
	CMatrix MakeEquation(double x, double y, double a, double b, double k1, double k2, double x0, double y0);
	double dFidA(double x, double y, double k1, double k2, double x0, double y0);
	double dFidK2(double x, double y, double a, double x0, double y0);
	double dFidK1(double x, double y, double a, double x0, double y0);
	double dFidX0(double x, double y, double a, double x0, double y0, double K1, double K2);
	double dFidY0(double x, double y, double a, double x0, double y0, double K1, double K2);
	double Fi(double x, double y, double a, double b, double k1, double k2, double x0, double y0);
	void CreateInitials();
	void MakeEquations();
	void MakeEquations_K1();
	void MakeEquations_K1K2();
	void MakeMatrixes();
	void MakeMatrixes_K1();
	void MakeMatrixes_K1K2();
	double MakeIteration();
	double MakeIteration_K1();
	double MakeIteration_K1K2();
	void Calibrate();
	void Calibrate_K1();
	void Calibrate_K1K2();

	CString GetStr();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALIBRATORDLG_H__3FC8F40E_0819_4C0F_8F40_6B2EEB40B15F__INCLUDED_)
