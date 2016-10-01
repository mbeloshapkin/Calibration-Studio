#if !defined(AFX_CHILDVIEW_H__BAFBFF3C_7909_4D6A_8A91_DC11556A1F5E__INCLUDED_)
#define AFX_CHILDVIEW_H__BAFBFF3C_7909_4D6A_8A91_DC11556A1F5E__INCLUDED_

#include "Picture.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChildView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChildView view

class CChildView : public CScrollView
{
protected:
	CChildView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CChildView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	HCURSOR m_hHandCur;
	BOOL m_bCatch;
	CPoint m_CatchPoint;
	afx_msg void OnUpdateIndicatorZoom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateIndicator_Y(CCmdUI* pCmdUI);
	afx_msg void OnUpdateIndicator_X(CCmdUI* pCmdUI);
	CPicture m_Picture;
	void SetScrollSize();
	virtual ~CChildView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CChildView)
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnFileOpen();
	afx_msg void OnZoomOff();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__BAFBFF3C_7909_4D6A_8A91_DC11556A1F5E__INCLUDED_)
