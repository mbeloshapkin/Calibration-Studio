// ChildView.cpp : implementation file
//

#include "stdafx.h"
#include "Corr.h"
#include "ChildView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	ID_MOVE_TIMER		1001
/////////////////////////////////////////////////////////////////////////////
// CChildView

IMPLEMENT_DYNCREATE(CChildView, CScrollView)

CChildView::CChildView()
{
	m_CatchPoint.x=m_CatchPoint.y=0;
	m_bCatch=FALSE;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CScrollView)
	//{{AFX_MSG_MAP(CChildView)
	ON_COMMAND(ID_ZOOM_IN, OnZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, OnZoomOut)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_ZOOM_OFF, OnZoomOff)
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_X, OnUpdateIndicator_X)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_Y, OnUpdateIndicator_Y)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ZOOM, OnUpdateIndicatorZoom)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildView drawing

void CChildView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	// ������ ���������
	SetScrollSize();
	SetTimer(ID_MOVE_TIMER, 50,  NULL);
	m_hHandCur=::AfxGetApp()->LoadCursor(ID_HAND_CURSOR);
}

void CChildView::OnDraw(CDC* pDC)
{
	if(!m_Picture.IsValid())return;
	// TODO: add draw code here
	// ������ ���������� �������
	CRect	ClientRect(0,0,0,0);
	GetClientRect(ClientRect);
	// ������ �� ������� � ����
	if(ClientRect.right>long(m_Picture.GetPictureWidth()*m_Picture.GetZoom()))
		ClientRect.right=long(m_Picture.GetPictureWidth()*m_Picture.GetZoom());
	if(ClientRect.bottom>long(m_Picture.GetPictureHeight()*m_Picture.GetZoom()))
		ClientRect.bottom=long(m_Picture.GetPictureHeight()*m_Picture.GetZoom());
	// ������� DC � ������ � ������ � ����
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap	memBmp;
	memBmp.CreateCompatibleBitmap(pDC, ClientRect.Width(), ClientRect.Height());
	CBitmap	*pOldBmp=memDC.SelectObject(&memBmp);
	// ����������� ������
	CPoint	ScrollPos=GetScrollPosition();
	// ������ � ������
	m_Picture.Draw(memDC.m_hDC, ClientRect, ScrollPos);
	// ���������� ������ � ����
	pDC->BitBlt(ScrollPos.x, ScrollPos.y, ClientRect.right, ClientRect.bottom,
		&memDC, 0, 0, SRCCOPY);
	// ����������� Bitmap
	memDC.SelectObject(pOldBmp);

/*
	m_Picture.Draw(pDC->m_hDC);
/*
	if(m_bmpPic.m_hObject!=NULL)
	{
		BITMAP bmpInfo;
		m_bmpPic.GetBitmap(&bmpInfo);
///////////////////////////////////
		CRect	RectClient(0,0,0,0);
		CChildView::GetClientRect(RectClient);

		pDC->SetMapMode(MM_ISOTROPIC);
		pDC->SetWindowExt(RectClient.Width(), RectClient.Height());
		pDC->SetViewportExt(RectClient.Width(), RectClient.Height());
///////////////////////////////////
		CDC dcMemory;
		dcMemory.CreateCompatibleDC(pDC);

		// Select the bitmap into the in-memory DC
		dcMemory.SelectObject(&m_bmpPic);
		int nX = 0;
		int nY = 0;
		// �������
		int	nZoomedCx=(int)(bmpInfo.bmWidth*m_dZoom);
		int	nZoomedCy=(int)(bmpInfo.bmHeight*m_dZoom);
		pDC->StretchBlt(nX, nY, nZoomedCx, nZoomedCy, &dcMemory, 
			0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);
	}
*/
}

/////////////////////////////////////////////////////////////////////////////
// CChildView diagnostics

#ifdef _DEBUG
void CChildView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CChildView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
	
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

void CChildView::OnZoomIn() 
{
	// TODO: Add your command handler code here
	double dZoom=m_Picture.GetZoom();
	if(dZoom>=1)
	{
		// ������� ����� ��� ����� 100%
		dZoom+=1;
	}
	else
	{
		// ������� ���� 100%
		dZoom*=2;
	}
	m_Picture.SetZoom(dZoom);
	// ������ ���������
	SetScrollSize();
	Invalidate();
}

void CChildView::OnZoomOut() 
{
	// TODO: Add your command handler code here
	double dZoom=m_Picture.GetZoom();
	if(dZoom>1)
	{
		// ������� ����� 100%
		dZoom-=1;
	}
	else
	{
		// ������� ���� ��� ����� 100%
		dZoom/=2;
	}
	m_Picture.SetZoom(dZoom);
	// ������ ���������
	SetScrollSize();
	Invalidate();
}

void CChildView::SetScrollSize()
{
	CSize sizeTotal;
	sizeTotal.cx=(long)(m_Picture.GetPictureWidth()*m_Picture.GetZoom());
	sizeTotal.cy=(long)(m_Picture.GetPictureHeight()*m_Picture.GetZoom());
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CChildView::OnFileOpen() 
{
	
	// TODO: Add your command handler code here
	// ��������� ����
	CFileDialog	FileDlg(TRUE, NULL, NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"����� BMP (*.bmp)|*.bmp|����� JPEG (*.jpg)|*.jpg||", this);
	if(FileDlg.DoModal()!=IDOK)
	{
		return;
	}
	CString	strFileName=FileDlg.GetPathName();
	CWaitCursor	Wait;
	if(!m_Picture.Load(strFileName))
	{
		MessageBox("������ �������� �����.", "������", MB_ICONERROR);
		return;
	}
	// �������
	OnZoomOff();
/*
	// ���������� ������ BMP
	m_bmpPic.DeleteObject();
	// ��������� ����
	HANDLE hBmp=::LoadImage(0, strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BOOL bRes=m_bmpPic.Attach(hBmp);
	// �������
	OnZoomOff();
*/

}

void CChildView::OnZoomOff() 
{
	// TODO: Add your command handler code here
	m_Picture.SetZoom(1);
	// ������ ���������
	SetScrollSize();
	Invalidate();
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBrush	Brush;
	Brush.CreateStockObject(LTGRAY_BRUSH);
	FillOutsideRect(pDC, &Brush);
	return TRUE;
}

void CChildView::OnUpdateIndicator_X(CCmdUI *pCmdUI)
{
	if(!m_Picture.IsValid())
	{
		pCmdUI->SetText("");
		return;
	}
	CPoint	PointCursor(0,0);
	::GetCursorPos(&PointCursor);
	ScreenToClient(&PointCursor);
	// ��������� ������� ����
	CRect	ClientRect(0,0,0,0);
	GetClientRect(ClientRect);
	if(PointCursor.x<ClientRect.left)PointCursor.x=ClientRect.left;
	if(PointCursor.x>ClientRect.right)PointCursor.x=ClientRect.right;
	// �������� �� ���������
	CPoint	ScrollRos=GetScrollPosition();
	PointCursor.x+=ScrollRos.x;
	// ��������� ������� �������
	if(PointCursor.x>(long)(m_Picture.GetPictureWidth()*m_Picture.GetZoom()))
		PointCursor.x=(long)(m_Picture.GetPictureWidth()*m_Picture.GetZoom());
	// �������� �������������� ��������
	PointCursor.x=(int)(PointCursor.x/m_Picture.GetZoom());
	// ������ �������
	UINT	nWidth=m_Picture.GetPictureWidth();
	// �������
	CString	strTmp;
	strTmp.Format("%ld  (%ld)", PointCursor.x, nWidth);
	pCmdUI->SetText(strTmp);
}

void CChildView::OnUpdateIndicator_Y(CCmdUI *pCmdUI)
{
	if(!m_Picture.IsValid())
	{
		pCmdUI->SetText("");
		return;
	}
	CPoint	PointCursor(0,0);
	::GetCursorPos(&PointCursor);
	ScreenToClient(&PointCursor);
	// ��������� ������� ����
	CRect	ClientRect(0,0,0,0);
	GetClientRect(ClientRect);
	if(PointCursor.y<ClientRect.top)PointCursor.y=ClientRect.top;
	if(PointCursor.y>ClientRect.bottom)PointCursor.y=ClientRect.bottom;
	// �������� �� ���������
	CPoint	ScrollRos=GetScrollPosition();
	PointCursor.y+=ScrollRos.y;
	// ��������� ������� �������
	if(PointCursor.y>(long)(m_Picture.GetPictureHeight()*m_Picture.GetZoom()))
		PointCursor.y=(long)(m_Picture.GetPictureHeight()*m_Picture.GetZoom());
	// �������� �������������� ��������
	PointCursor.y=(int)(PointCursor.y/m_Picture.GetZoom());
	// ������ �������
	UINT	nHeight=m_Picture.GetPictureHeight();
	// �������
	CString	strTmp;
	strTmp.Format("%ld  (%ld)", PointCursor.y, nHeight);
	pCmdUI->SetText(strTmp);
}

void CChildView::OnUpdateIndicatorZoom(CCmdUI *pCmdUI)
{
	if(!m_Picture.IsValid())
	{
		pCmdUI->SetText("");
		return;
	}
	CString	strTmp;
	long	nZoom=(long)(m_Picture.GetZoom()*100);
	strTmp.Format("%ld %%", nZoom);
	pCmdUI->SetText(strTmp);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_Picture.IsValid() && !m_bCatch)
	{
		GetCursorPos(&m_CatchPoint);
		m_bCatch=TRUE;
	}
	CScrollView::OnRButtonDown(nFlags, point);
}



void CChildView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bCatch)
	{
		m_bCatch=FALSE;
	}
	CScrollView::OnRButtonUp(nFlags, point);
}

void CChildView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==ID_MOVE_TIMER && m_bCatch)
	{
		// ������ ��������� � ������ ����������� ����
		CSize	TotalSize=GetTotalSize();
		CRect	ClientRect(0,0,0,0);
		GetClientRect(&ClientRect);
		// �� ������� ��������� ������
		CPoint	tmpPoint(0,0);
		GetCursorPos(&tmpPoint);
		{
			CRect	Rect=ClientRect;
			ClientToScreen(Rect);
			if(!Rect.PtInRect(tmpPoint))
			{
				m_bCatch=FALSE;
				return;
			}
		}
		// �� ������� ��������� ������
		tmpPoint=m_CatchPoint-tmpPoint;
		// ������� �������
		CPoint	OldPos=GetScrollPosition();
		CPoint	NewPos=OldPos;
		// ��������
		NewPos.Offset(tmpPoint);
		// ��������� ����� �������
		if(NewPos.x<0)NewPos.x=0;
		if(NewPos.y<0)NewPos.y=0;
		if(NewPos.x>(TotalSize.cx-ClientRect.Width()))
		{
			NewPos.x=(TotalSize.cx-ClientRect.Width());
		}
		if(NewPos.y>(TotalSize.cy-ClientRect.Height()))
		{
			NewPos.y=(TotalSize.cy-ClientRect.Height());
		}
		// �������� ����
		SetRedraw(FALSE);
		ScrollToPosition(NewPos);
		SetRedraw(TRUE);
		Invalidate(FALSE);
		// ���������� �������
		GetCursorPos(&m_CatchPoint);
	}	
	CScrollView::OnTimer(nIDEvent);
}

BOOL CChildView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bCatch)
	{
		::SetCursor(m_hHandCur);
		return TRUE;
	}
	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!m_bCatch && nFlags&MK_RBUTTON)
	{
		m_bCatch=TRUE;
	}	
	CScrollView::OnMouseMove(nFlags, point);
}
