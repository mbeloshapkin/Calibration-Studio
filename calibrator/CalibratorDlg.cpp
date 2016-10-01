// CalibratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calibrator.h"
#include "CalibratorDlg.h"

#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
static CALDATA CD;
static CALDATA tmpCD;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalibratorDlg dialog

CCalibratorDlg::CCalibratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalibratorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalibratorDlg)
	m_SizeXmm = 0.0;
	m_SizeYmm = 0.0;
	m_SizeYpix = 0;
	m_SizeXpix = 0;
	m_MaxIterations = 0;
	m_Precision = 0.0;
	m_K1 = 0.0;
	m_K1Ini = 0.0;
	m_K2 = 0.0;
	m_MaxErr = 0.0;
	m_SQD = 0.0;
	m_WightX0Y0 = 0.0;
	m_X0 = 0.0;
	m_Y0 = 0.0;
	m_K1Only = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	M1 = NULL;
	M2 = NULL;
	M3 = NULL;
	M4 = NULL;
	L = NULL;
}

void CCalibratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalibratorDlg)
	DDX_Text(pDX, IDC_SIZEX_MM, m_SizeXmm);
	DDV_MinMaxDouble(pDX, m_SizeXmm, 0., 600.);
	DDX_Text(pDX, IDC_SIZEY_MM, m_SizeYmm);
	DDV_MinMaxDouble(pDX, m_SizeYmm, 0., 600.);
	DDX_Text(pDX, IDC_SIZEY_PIX, m_SizeYpix);
	DDV_MinMaxInt(pDX, m_SizeYpix, 100, 100000);
	DDX_Text(pDX, IDC_SIZEX_PIX, m_SizeXpix);
	DDV_MinMaxInt(pDX, m_SizeXpix, 100, 100000);
	DDX_Text(pDX, IDC_MAX_ITERATIONS, m_MaxIterations);
	DDV_MinMaxInt(pDX, m_MaxIterations, 1, 10000);
	DDX_Text(pDX, IDC_PRECISION, m_Precision);
	DDV_MinMaxDouble(pDX, m_Precision, 1.e-005, 100.);
	DDX_Text(pDX, IDC_K1, m_K1);
	DDX_Text(pDX, IDC_K1_INI, m_K1Ini);
	DDX_Text(pDX, IDC_K2, m_K2);
	DDX_Text(pDX, IDC_MAX_ERR, m_MaxErr);
	DDX_Text(pDX, IDC_SQD, m_SQD);
	DDX_Text(pDX, IDC_WEGHT_X0Y0, m_WightX0Y0);
	DDV_MinMaxDouble(pDX, m_WightX0Y0, 0., 1.);
	DDX_Text(pDX, IDC_X0, m_X0);
	DDX_Text(pDX, IDC_Y0, m_Y0);
	DDX_Radio(pDX, IDC_K1_ONLY, m_K1Only);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalibratorDlg, CDialog)
	//{{AFX_MSG_MAP(CCalibratorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD_DATA, OnLoadData)
	ON_BN_CLICKED(IDC_CALIBRATE, OnCalibrate)
	ON_BN_CLICKED(IDC_CREATE_REPORT, OnCreateReport)
	ON_BN_CLICKED(IDC_RESTORE, OnRestore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalibratorDlg message handlers

BOOL CCalibratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
//	double tmp = 10e+1;
	m_K1Ini = 0.0001;
	m_K1 = m_K1Ini;
	m_SizeXmm = SX_MM;
	m_SizeYmm = SY_MM;
	m_MaxIterations = 1000;
	m_Precision = 0.1;
	m_SizeXpix = (int)SX_PIX;
	m_SizeYpix = (int)SY_PIX;
	m_WightX0Y0 = 0.001;
	m_X0 = 0;
	m_Y0 = 0;
	m_K1Only = 0;

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalibratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalibratorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalibratorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CCalibratorDlg::OnLoadData(){

	UpdateData();

	CD.MSXPix = SX_PIX;
	CD.MSYPix = SY_PIX;
	CD.MSXmm = SX_MM;
	CD.MSYmm = SY_MM;
	CD.X0 = CD.MSXmm / 2, CD.Y0 = CD.MSYmm / 2;
	CD.K1 = K1_INI; CD.K2 = 0;
	
	CFileDialog fd(TRUE,"txt", NULL, 0, "Data as text (*.txt)|*.txt||");

	if(fd.DoModal() == IDOK){
		nlHor = 0; nlVert = 0;
		np = 0;
		CFile f;
		CString fname = fd.GetFileName();
		f.Open(fname,CFile::modeRead);
		BufLen = f.GetLength();
		if(BufLen >= 10000){
			AfxMessageBox(CString("Too large data file"), MB_ICONSTOP | MB_OK);
			return;
		}
		f.Read(Buf,BufLen);
		f.Close();
		
		CString str;
		ptr = 0;
		while(ptr < BufLen){
			str = GetStr();
			ParseStr(str);
		}
	}

	
}

CString CCalibratorDlg::GetStr(){
	
	CString ret;
	
	while(((Buf[ptr] == '\r') || 
			(Buf[ptr] == '\n') || 
			(Buf[ptr] == ' ') ||
			(Buf[ptr] == '\t')) && (ptr < BufLen)) ptr++;

	if(Buf[ptr] == '/'){ // Пропустить целую строку
		while((Buf[ptr] != '\r') && 
			(Buf[ptr] != '\n') && (ptr < BufLen)) ptr++;
		while((Buf[ptr] == '\r') || 
			(Buf[ptr] == '\n') && (ptr < BufLen)) ptr++;
		return ret;
	}
	// Скопировать строку
	while(((Buf[ptr] == '\r') || 
			(Buf[ptr] == '\n') || 
			(Buf[ptr] == ' ') ||
			(Buf[ptr] == '\t')) && (ptr < BufLen)) ptr++;
	if(ptr == BufLen) return ret; // Файл кончился
	while((Buf[ptr] != '\r') && 
		(Buf[ptr] != '\n') && (ptr < BufLen)){
		ret += Buf[ptr++];
	}
	return ret;
}


void CCalibratorDlg::ParseStr(CString &str){

	if(!str.GetLength()) return;

	CString tag;

	str.TrimLeft();
	tag = str.SpanExcluding(" \t;");
	int linenum = atoi((LPCSTR)tag);
	Points[np].LNum = linenum;
	Points[np].Vert = linenum >= 100;

	str.Delete(0,tag.GetLength());
	str.TrimLeft();
	tag = str.SpanExcluding(" \t;");
	Points[np].PNum = atoi((LPCSTR)tag);
	str.Delete(0,tag.GetLength());
	str.TrimLeft();
	
	tag = str.SpanExcluding(" \t;");
	Points[np].x = atof((LPCSTR)tag) * CD.MSXmm / CD.MSXPix;
	str.Delete(0,tag.GetLength());
	str.TrimLeft();
	
	if(np > 88){
		int i = 1;
	}


	tag = str.SpanExcluding(" \t;");
	Points[np++].y = (CD.MSYPix - atof((LPCSTR)tag)) * CD.MSYmm / CD.MSYPix;

}



double CCalibratorDlg::Fi(double x, double y, double a, double b, double k1, double k2, double x0, double y0){
	double r2 = (x - x0) * (x - x0) + (y - y0) * (y - y0);
	double cr = 1 + k1 * r2 + k2 * r2 * r2;
	double ret = a * (x - x0) * cr + b - (y - y0) * cr;
	return ret;
}


double CCalibratorDlg::dFidA(double x, double y, double k1, double k2, double x0, double y0){
	double r2 = (x - x0) * (x - x0) + (y - y0) * (y - y0);
	double cr = 1 + k1 * r2 + k2 * r2 * r2;
	double ret = (x - x0) * cr;
	return ret;
}


double CCalibratorDlg::dFidK1(double x, double y, double a, double x0, double y0){
	double r2 = (x - x0) * (x - x0) + (y - y0) * (y - y0);
	double ret = a * (x - x0) * r2 - (y - y0) * r2;
	return ret;
}

double CCalibratorDlg::dFidK2(double x, double y, double a, double x0, double y0){
	double r2 = (x - x0) * (x - x0) + (y - y0) * (y - y0);
	double ret = a * (x - x0) * r2 * r2 - (y - y0) * r2 * r2;
	return ret;
}

double CCalibratorDlg::dFidX0(double x, double y, double a, double x0, double y0, double K1, double K2){
	double u = x0, v = y0;
	double x2 = x*x,	y2 = y*y,	u2 = u*u,	v2 = v*v;
	double x3 = x2*x,	y3 = y2*y,	u3 = u2*u,	v3 = v2*v;
	double x4 = x3*x,	y4 = y3*y,	u4 = u3*u,	v4 = v3*v;
	double ret,r1,r2,r3,r4,r5,r6,r7;
	r1 = -a*K1*y2 + 2*v*u*K1 - a - 3*a*K1*u2 - 2*v*x*K1 - 5*a*K2*u4 + 12*a*K2*x2*y*v + 12*a*K2*x*u*v2;
	r2 = 4*a*K2*y*v3 + 12*a*K2*x*u*y2 - 24*a*K2*x*u*y*v - 6*a*K2*y2*v2 - a*K2*y4 + 6*a*K1*x*u;
	r3 = 20*a*K2*x3*u - 6*a*K2*x2*y2 - a*K1*v2 - 6*a*K2*u2*v2 +4*a*K2*y3*v + 20*a*K2*x*u3 - 6*a*K2*u2*y2;
	r4 = 12*a*K2*u2*y*v - 6*a*K2*x2*v2 + 4*y*x3*K2 - 5*a*K2*x4 - 3*a*K1*x2 - 12*v*x*K2*u2;
	r5 = 12*K2*(v*x*u2 + y2*u*v - y*u*v2 + v*x2*u + y*x*u2 - y2*x*v + y*x*v2);
	r6 = -4*y*u3*K2 - 12*y*x2*K2*u + 2*a*K1*y*v - 30*a*K2*x2*u2 - a*K2*v4 + 2*y*x*K1;
	r7 = -2*y*u*K1 + 4*K2*(-v*x3 - v3*x - y3*u + y3*x + v3*u + v*u3);

	ret = r1 + r2 + r3 + r4 + r5 + r6 + r7;

	return ret;
}

double CCalibratorDlg::dFidY0(double x, double y, double a, double x0, double y0, double K1, double K2){
	double u = x0, v = y0;
	double x2 = x*x,	y2 = y*y,	u2 = u*u,	v2 = v*v;
	double x3 = x2*x,	y3 = y2*y,	u3 = u2*u,	v3 = v2*v;
	double x4 = x3*x,	y4 = y3*y,	u4 = u3*u,	v4 = v3*v;
	double ret,r1,r2,r3,r4,r5,r6,r7;
	
	r1 = 1 - 2*K1*x*u - 6*K1*y*v - 4*K2*x3*u + K1*x2 - 20*K2*y3*v + 5*K2*y4 - 12*K2*(x*u*v2 + x2*y*v + x*u*y2);
	r2 = 24*K2*x*u*y*v + 6*K2*x2*v2 + K2*x4 + K2*u4 + 5*K2*v4 + 3*K1*y2 + 2*a*x*v*K1 - 4*a*x3*y*K2;
	r3 = 4*K2*(a*u*y3 + a*u3*y) - 2*a*u*v*K1 + 4*a*K2*(x*v3 + x3*v - u*v3);
	r4 = 2*a*u*y*K1 - 12*a*x*y*K2*u2 + 12*a*x*y2*K2*v - 4*a*K2*(u3*v + x*y3) - 12*a*x2*v*K2*u;
	r5 = K1*u2 - 12*a*x*y*K2*v2 - 2*a*x*y*K1 - 12*a*x*v*K2*u2;
	r6 = 12*a*K2*(x*v*u2 + x2*y*u + u*y*v2) - 12*K2*u2*y*v + 6*K2*x2*u2 - 20*K2*y*v3;
	r7 = K2 * (30*y2*v2 + 6*u2*y2 + 6*x2*y2 - 4*x*u3 + 6*u2*v2);

	ret = r1 + r2 + r3 + r4 + r5 + r6 + r7;

	return ret;
}


void CCalibratorDlg::CreateInitials(){

	CD.MSXPix = SX_PIX;
	CD.MSYPix = SY_PIX;
	CD.MSXmm = SX_MM;
	CD.MSYmm = SY_MM;
	CD.X0 = CD.MSXmm / 2, CD.Y0 = CD.MSYmm / 2;
	CD.K1 = K1_INI; CD.K2 = 0;

	int curlnum = Points[0].LNum;
	int lidx = 0; double bsum = 0;
	int npl = 0;
	int pidx;
	for(pidx = 0; pidx < np; pidx++){
		if(curlnum != Points[pidx].LNum){
			CD.BI[lidx] = bsum/npl - CD.Y0;
			CD.AI[lidx] = 0;
			npl = 0;
			bsum = 0;
			lidx++;
			curlnum = Points[pidx].LNum;
		}
		else{
			bsum += Points[pidx].y;
			npl++;
		}
	}
	
	// Инициализировать последнюю пару значений

	CD.BI[lidx] = bsum/npl - CD.Y0;
	CD.AI[lidx] = 0;

}

// Порядок следования переменных:
// dK1,dK2,dX0,dY0,dA0,dB0,dA1,dB1....

void CCalibratorDlg::MakeEquations(){
	int curlnum = Points[0].LNum;
	int lnum = 0;
	int pidx;
	int eqofs;
	M4->Zero();
	for(pidx = 0; pidx < np; pidx++){
		if(curlnum != Points[pidx].LNum){
			curlnum = Points[pidx].LNum;
			lnum++;
		}
		double dfidk1 = dFidK1(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.X0,CD.Y0);
		double dfidk2 = dFidK2(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.X0,CD.Y0);
		double dfidx0 = dFidX0(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.X0,CD.Y0,CD.K1,CD.K2);
		double dfidy0 = dFidY0(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.X0,CD.Y0,CD.K1,CD.K2);
		double dfida = dFidA(Points[pidx].x,Points[pidx].y,CD.K1,CD.K2,CD.X0,CD.Y0);
		double dfidb = 1;
		double fi0 = Fi(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.BI[lnum],CD.K1,CD.K2,CD.X0,CD.Y0);
		eqofs = lnum * 2 + 4; //2; //2;
		L->Set(0,pidx,fi0);
		M4->Set(0,pidx,dfidk1);
		M4->Set(1,pidx,dfidk2);
		M4->Set(2,pidx,dfidx0);
		M4->Set(3,pidx,dfidy0);
		M4->Set(eqofs,pidx,dfida);
		M4->Set(eqofs + 1,pidx,dfidb);
	}
}

void CCalibratorDlg::MakeEquations_K1(){
	int curlnum = Points[0].LNum;
	int lnum = 0;
	int pidx;
	int eqofs;
	M1->Zero();
	for(pidx = 0; pidx < np; pidx++){
		if(curlnum != Points[pidx].LNum){
			curlnum = Points[pidx].LNum;
			lnum++;
		}
		double dfidk1 = dFidK1(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.X0,CD.Y0);
		double dfidk2 = dFidK2(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.X0,CD.Y0);
		double dfidx0 = dFidX0(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.X0,CD.Y0,CD.K1,CD.K2);
		double dfidy0 = dFidY0(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.X0,CD.Y0,CD.K1,CD.K2);
		double dfida = dFidA(Points[pidx].x,Points[pidx].y,CD.K1,CD.K2,CD.X0,CD.Y0);
		double dfidb = 1;
		double fi0 = Fi(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.BI[lnum],CD.K1,CD.K2,CD.X0,CD.Y0);
		eqofs = lnum * 2 + 1; //2; //2;
		L->Set(0,pidx,fi0);
		M1->Set(0,pidx,dfidk1);
//		M->Set(1,pidx,dfidk2);
//		M->Set(2,pidx,dfidx0);
//		M->Set(3,pidx,dfidy0);
		M1->Set(eqofs,pidx,dfida);
		M1->Set(eqofs + 1,pidx,dfidb);
	}
}

void CCalibratorDlg::MakeEquations_K1K2(){
	int curlnum = Points[0].LNum;
	int lnum = 0;
	int pidx;
	int eqofs;
	M2->Zero();
	for(pidx = 0; pidx < np; pidx++){
		if(curlnum != Points[pidx].LNum){
			curlnum = Points[pidx].LNum;
			lnum++;
		}
		double dfidk1 = dFidK1(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.X0,CD.Y0);
		double dfidk2 = dFidK2(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.X0,CD.Y0);
		double dfidx0 = dFidX0(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.X0,CD.Y0,CD.K1,CD.K2);
		double dfidy0 = dFidY0(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.X0,CD.Y0,CD.K1,CD.K2);
		double dfida = dFidA(Points[pidx].x,Points[pidx].y,CD.K1,CD.K2,CD.X0,CD.Y0);
		double dfidb = 1;
		double fi0 = Fi(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.BI[lnum],CD.K1,CD.K2,CD.X0,CD.Y0);
		eqofs = lnum * 2 + 2; //2; //2;
		L->Set(0,pidx,fi0);
		M2->Set(0,pidx,dfidk1);
		M2->Set(1,pidx,dfidk2);
//		M->Set(2,pidx,dfidx0);
//		M->Set(3,pidx,dfidy0);
		M2->Set(eqofs,pidx,dfida);
		M2->Set(eqofs + 1,pidx,dfidb);
	}
}


void CCalibratorDlg::MakeMatrixes(){
	// Подсчет числа точек и струн 
	nlHor = 0; nlVert = 0;
	npHor = 0; npVert = 0;
	int idx; int curlnum = Points[0].LNum;
	if(Points[0].Vert) nlVert = 1;
	else nlHor = 1;

	for(idx = 0; idx < np; idx++){
		if(curlnum != Points[idx].LNum){ // Новая линия
			curlnum = Points[idx].LNum;
			if(Points[idx].Vert) nlVert++;
			else nlHor++;
		}
		if(Points[idx].Vert) npVert++;
		else npHor++;
	}
	
	int nCol,nStr;
	nCol = nlHor * 2 + 4; //2; //2;
	nStr = npHor;

	if(M4) delete M4;
	M4 = new CMatrix(nCol,nStr);
	M4->Zero();
	if(L) delete L;
	L = new CMatrix(1,nStr);
	L->Zero();
}

void CCalibratorDlg::MakeMatrixes_K1(){
	// Подсчет числа точек и струн 
	nlHor = 0; nlVert = 0;
	npHor = 0; npVert = 0;
	int idx; int curlnum = Points[0].LNum;
	if(Points[0].Vert) nlVert = 1;
	else nlHor = 1;

	for(idx = 0; idx < np; idx++){
		if(curlnum != Points[idx].LNum){ // Новая линия
			curlnum = Points[idx].LNum;
			if(Points[idx].Vert) nlVert++;
			else nlHor++;
		}
		if(Points[idx].Vert) npVert++;
		else npHor++;
	}
	
	int nCol,nStr;
	nCol = nlHor * 2 + 1; //2; //2;
	nStr = npHor;

	if(M1) delete M1;
	M1 = new CMatrix(nCol,nStr);
	M1->Zero();
	if(L) delete L;
	L = new CMatrix(1,nStr);
	L->Zero();
}

void CCalibratorDlg::MakeMatrixes_K1K2(){
	// Подсчет числа точек и струн 
	nlHor = 0; nlVert = 0;
	npHor = 0; npVert = 0;
	int idx; int curlnum = Points[0].LNum;
	if(Points[0].Vert) nlVert = 1;
	else nlHor = 1;

	for(idx = 0; idx < np; idx++){
		if(curlnum != Points[idx].LNum){ // Новая линия
			curlnum = Points[idx].LNum;
			if(Points[idx].Vert) nlVert++;
			else nlHor++;
		}
		if(Points[idx].Vert) npVert++;
		else npHor++;
	}
	
	int nCol,nStr;
	nCol = nlHor * 2 + 2; //2; //2;
	nStr = npHor;

	if(M2) delete M2;
	M2 = new CMatrix(nCol,nStr);
	M2->Zero();
	if(L) delete L;
	L = new CMatrix(1,nStr);
	L->Zero();
}



double CCalibratorDlg::MakeIteration(){
	double sqd0,sqd;
	double max0,max; // ошибки до итерации и после нее
	double fi;
	int ct;
	CMatrix* B;
	CMatrix* X;
	MakeEquations();

	// Оценка погрешности до итерации
	sqd0 = 0; fi = L->Get(0,0); max0 = fi * fi;
	for(ct = 0; ct < L->GetSize().cy; ct++){
		fi = L->Get(0,ct);
		if(max0 < fi * fi) max0 = fi * fi;
		sqd0 += fi * fi;
	}

	sqd0 = sqrt(sqd0 / L->GetSize().cy);
	max0 = sqrt(max0);


	B = new CMatrix();
	X = new CMatrix();

	*B = M4->Inverse();
	*L *= -1;

	*X = *B * *L;
	delete B;

	// Внесение поправок
	CD.K1 += X->Get(0,0);
	CD.K2 += X->Get(1,0);

	CD.X0 += X->Get(2,0) * m_WightX0Y0;
	CD.Y0 += X->Get(3,0) * m_WightX0Y0; //10E-3;

	int idx;
	for(ct = 0; ct < nlHor; ct++){
		idx = 2 * ct + 4; //2; //2;
		CD.AI[ct] += X->Get(idx,0);
		CD.BI[ct] += X->Get(idx + 1,0);
		if(CD.BI[ct] > 10){
			int i = 1;
		}
	}

	delete X;
	// Оценка погрешности после итерации
	MakeEquations();
	sqd = 0; fi = L->Get(0,0); max = fi * fi;
	for(ct = 0; ct < L->GetSize().cy; ct++){
		fi = L->Get(0,ct);
		if(max < fi * fi) max = fi * fi;
		sqd += fi * fi;
	}

	sqd = sqrt(sqd / L->GetSize().cy);
	max = sqrt(max);
	m_MaxErr = max * 1000.0;

	return sqd;
}

double CCalibratorDlg::MakeIteration_K1(){
	double sqd0,sqd;
	double max0,max; // ошибки до итерации и после нее
	double fi;
	int ct;
	CMatrix* B;
	CMatrix* X;
	MakeEquations_K1();

	// Оценка погрешности до итерации
	sqd0 = 0; fi = L->Get(0,0); max0 = fi * fi;
	for(ct = 0; ct < L->GetSize().cy; ct++){
		fi = L->Get(0,ct);
		if(max0 < fi * fi) max0 = fi * fi;
		sqd0 += fi * fi;
	}

	sqd0 = sqrt(sqd0 / L->GetSize().cy);
	max0 = sqrt(max0);


	B = new CMatrix();
	X = new CMatrix();

	*B = M1->Inverse();
	*L *= -1;

	*X = *B * *L;

	delete B;

	// Внесение поправок
	CD.K1 += X->Get(0,0);
//	CD.K2 += X.Get(1,0);

//	CD.X0 += X.Get(2,0) * m_WightX0Y0;
//	CD.Y0 += X.Get(3,0) * m_WightX0Y0; //10E-3;

	int idx;
	for(ct = 0; ct < nlHor; ct++){
		idx = 2 * ct + 1; //2; //2;
		CD.AI[ct] += X->Get(idx,0);
		CD.BI[ct] += X->Get(idx + 1,0);
	}


	delete X;

	// Оценка погрешности после итерации
	MakeEquations_K1();
	sqd = 0; fi = L->Get(0,0); max = fi * fi;
	for(ct = 0; ct < L->GetSize().cy; ct++){
		fi = L->Get(0,ct);
		if(max < fi * fi) max = fi * fi;
		sqd += fi * fi;
	}

	sqd = sqrt(sqd / L->GetSize().cy);
	max = sqrt(max);
	m_MaxErr = max * 1000.0;

	return sqd;
}

double CCalibratorDlg::MakeIteration_K1K2(){
	double sqd0,sqd;
	double max0,max; // ошибки до итерации и после нее
	double fi;
	int ct;
	CMatrix* B;
	CMatrix* X;
	MakeEquations_K1K2();

	// Оценка погрешности до итерации
	sqd0 = 0; fi = L->Get(0,0); max0 = fi * fi;
	for(ct = 0; ct < L->GetSize().cy; ct++){
		fi = L->Get(0,ct);
		if(max0 < fi * fi) max0 = fi * fi;
		sqd0 += fi * fi;
	}

	sqd0 = sqrt(sqd0 / L->GetSize().cy);
	max0 = sqrt(max0);


	B = new CMatrix();
	X = new CMatrix();

	*B = M2->Inverse();
	*L *= -1;

	*X = *B * *L;

	delete B;

	// Внесение поправок
	CD.K1 += X->Get(0,0);
	CD.K2 += X->Get(1,0);

//	CD.X0 += X.Get(2,0) * m_WightX0Y0;
//	CD.Y0 += X.Get(3,0) * m_WightX0Y0; //10E-3;

	int idx;
	for(ct = 0; ct < nlHor; ct++){
		idx = 2 * ct + 2; //2; //2;
		CD.AI[ct] += X->Get(idx,0);
		CD.BI[ct] += X->Get(idx + 1,0);
	}


	delete X;

	// Оценка погрешности после итерации
	MakeEquations_K1K2();
	sqd = 0; fi = L->Get(0,0); max = fi * fi;
	for(ct = 0; ct < L->GetSize().cy; ct++){
		fi = L->Get(0,ct);
		if(max < fi * fi) max = fi * fi;
		sqd += fi * fi;
	}

	sqd = sqrt(sqd / L->GetSize().cy);
	max = sqrt(max);
	m_MaxErr = max * 1000.0;

	return sqd;
}





void CCalibratorDlg::Calibrate(){

	if(!M4){
		MakeMatrixes();
//		CreateInitials();
	}

	double sqd0 = MakeIteration();
	double sqd1,eff;
	int icnt = m_MaxIterations;

	while(1){
		sqd1 = MakeIteration();
		eff = (sqd0 - sqd1) * 1000.0; // В мкронах
		if(eff < m_Precision) break;  // Достигнута заданная точность
		sqd0 = sqd1;
		icnt--;
		if(icnt < 0) break; // Достигнуто предельное число итераций		
	}

	double cx = m_SizeXmm / 2;
	double cy = m_SizeYmm / 2;
	m_X0 = (CD.X0 - cx) * 1000.0;
	m_Y0 = (CD.Y0 - cy) * 1000.0;
	m_SQD = sqd1 * 1000.0;
	m_K1 = CD.K1;
	m_K2 = CD.K2;
	
}


void CCalibratorDlg::Calibrate_K1(){

	if(!M1){
		MakeMatrixes_K1();
		CreateInitials();
	}

	double sqd0 = MakeIteration_K1();
	double sqd1,eff;
	int icnt = m_MaxIterations;

	while(1){
		sqd1 = MakeIteration_K1();
		eff = (sqd0 - sqd1) * 1000.0; // В мкронах
		if(eff < m_Precision) break;  // Достигнута заданная точность
		sqd0 = sqd1;
		icnt--;
		if(icnt < 0) break; // Достигнуто предельное число итераций		
	}

	double cx = m_SizeXmm / 2;
	double cy = m_SizeYmm / 2;
	m_X0 = (CD.X0 - cx) * 1000.0;
	m_Y0 = (CD.Y0 - cy) * 1000.0;
	m_SQD = sqd1 * 1000.0;
	m_K1 = CD.K1;
	m_K2 = CD.K2;
	
}

void CCalibratorDlg::Calibrate_K1K2(){

	if(!M2){
		MakeMatrixes_K1K2();
		CreateInitials();
	}

	double sqd0 = MakeIteration_K1K2();
	double sqd1,eff;
	int icnt = m_MaxIterations;

	while(1){
		sqd1 = MakeIteration_K1K2();
		eff = (sqd0 - sqd1) * 1000.0; // В мкронах
		if(eff < m_Precision) break;  // Достигнута заданная точность
		sqd0 = sqd1;
		icnt--;
		if(icnt < 0) break; // Достигнуто предельное число итераций		
	}

	double cx = m_SizeXmm / 2;
	double cy = m_SizeYmm / 2;
	m_X0 = (CD.X0 - cx) * 1000.0;
	m_Y0 = (CD.Y0 - cy) * 1000.0;
	m_SQD = sqd1 * 1000.0;
	m_K1 = CD.K1;
	m_K2 = CD.K2;
	
}



void CCalibratorDlg::OnCalibrate(){

	UpdateData();
//	CD.MSXPix = m_SizeXpix;
//	CD.MSYPix = m_SizeYpix;
//	CD.MSXmm = m_SizeXmm;
//	MSYmm = m_SizeYmm;
//	X0 = MSXmm / 2, Y0 = MSYmm / 2;
	CWaitCursor cw;
	tmpCD = CD;
	switch(m_K1Only){
	case 0:	Calibrate_K1();
		break;
	case 1: Calibrate_K1K2();
		break;
	case 3: Calibrate();
		break;
	}
	UpdateData(FALSE);
	
}

void CCalibratorDlg::OnCreateReport(){
	
	CFileDialog fd(FALSE,"txt", NULL, 0, "Calibration report (*.txt)|*.txt||");

	if(fd.DoModal() == IDOK){
		
		CFile f;
		CString fname = fd.GetFileName();
		f.Open(fname,CFile::modeCreate | CFile::modeWrite);
		
		CArchive ar(&f,CArchive::store);

		CString str;
		str = "//\tDigital Camera Calibration report\r\n";
		str += "//\t(c) AeroGIS, Ltd. 2006\r\n";
		str += "//\te-mail: info@aerogis.com\r\n\r\n";
		ar.WriteString(str);

		str.Format(
"Principal point of symmetry (PPS)\r\n\
relative to center of the matrix, mcm:\t\tx0 = %6.3f\ty0 = %6.3f\r\n\r\n",
					m_X0,m_Y0); 
		ar.WriteString(str);

		str.Format(
"Radial distortion coefficients\r\n\
in according to SMAC                  \t\tK1 = %.6e\tK2 = %.6e\r\n\r\n",
					CD.K1,CD.K2);
		ar.WriteString(str);
		str.Format(
"Average quadratic error, mcm         \t\t%.1f\r\n\r\n",m_SQD);
		ar.WriteString(str);
		str.Format(
"Maximum error, mcm                   \t\t%.1f\r\n\r\nErrors by points:\r\n",m_MaxErr);
		ar.WriteString(str);
		str.Format("\r\nString\t\tPoint\t\tx,mm\t\ty,mm\t\tError, mcm\r\n");
		ar.WriteString(str);

		int pidx, curlnum = Points[0].LNum, lnum = 0;
		double fi0;
		
		for(pidx = 0; pidx < np; pidx++){
			if(curlnum != Points[pidx].LNum){
				curlnum = Points[pidx].LNum;
				lnum++;
			}
			fi0 = Fi(Points[pidx].x,Points[pidx].y,CD.AI[lnum],CD.BI[lnum],CD.K1,CD.K2,CD.X0,CD.Y0);
			str.Format("%i\t\t%i\t\t%.4f\t\t%.4f\t\t%.1f\r\n",curlnum,Points[pidx].PNum,Points[pidx].x,Points[pidx].y,fi0 * 1000.0);
			ar.WriteString(str);
		
		}
		
		ar.Close();
		f.Close();

	}
	
	
}

void CCalibratorDlg::OnRestore(){
	// TODO: Add your control notification handler code here
	CD = tmpCD;
	UpdateData(FALSE);
	
}
