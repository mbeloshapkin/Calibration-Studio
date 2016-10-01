// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Corr.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_STATUS_BAR	1001



static UINT indicators[] =
{
	ID_INDICATOR_ZOOM_LABEL,
	ID_INDICATOR_ZOOM,
	ID_INDICATOR_X_LABEL,
	ID_INDICATOR_X,
	ID_INDICATOR_Y_LABEL,
	ID_INDICATOR_Y,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here

	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// Создаем View
	CCreateContext	Context;
	Context.m_pCurrentDoc=NULL;
	Context.m_pCurrentFrame=this;
	Context.m_pLastView=NULL;
	Context.m_pNewDocTemplate=NULL;
	Context.m_pNewViewClass= RUNTIME_CLASS(CChildView);
	m_pView=CreateView(&Context);
	// Создаем панель инструментов
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC)
		|| !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	// Настраиваем панель инструментов
	CBitmap bmpTmp;
	bmpTmp.LoadBitmap(IDB_TOOLBAR);
	CImageList Img;
	Img.Create(50, 30, ILC_COLOR32|ILC_MASK, 1, 1);
	Img.Add(&bmpTmp, RGB(255, 0, 255));
	m_wndToolBar.GetToolBarCtrl().SetImageList(&Img);
	Img.Detach();
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	// Создаем строку состояния
	if (!m_wndStatusBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, ID_STATUS_BAR) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	// Теперь настраиваем индикаторы
	m_wndStatusBar.SetPaneInfo(0, ID_INDICATOR_ZOOM_LABEL, SBPS_NORMAL|SBPS_NOBORDERS, 50);
	m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_ZOOM, SBPS_NORMAL, 40);
	m_wndStatusBar.SetPaneInfo(2, ID_INDICATOR_X_LABEL, SBPS_NORMAL|SBPS_NOBORDERS, 40);
	m_wndStatusBar.SetPaneInfo(3, ID_INDICATOR_X, SBPS_NORMAL, 70);
	m_wndStatusBar.SetPaneInfo(4, ID_INDICATOR_Y_LABEL, SBPS_NORMAL|SBPS_NOBORDERS, 40);
	m_wndStatusBar.SetPaneInfo(5, ID_INDICATOR_Y, SBPS_NORMAL, 70);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_pView->SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_pView->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
