// Corr.h : main header file for the CORR application
//

#if !defined(AFX_CORR_H__5F9F7904_53A3_47AD_8753_E947651BC154__INCLUDED_)
#define AFX_CORR_H__5F9F7904_53A3_47AD_8753_E947651BC154__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCorrApp:
// See Corr.cpp for the implementation of this class
//

class CCorrApp : public CWinApp
{
public:
	CCorrApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCorrApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CCorrApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CORR_H__5F9F7904_53A3_47AD_8753_E947651BC154__INCLUDED_)
