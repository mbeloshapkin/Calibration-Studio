// Calibrator.h : main header file for the CALIBRATOR application
//

#if !defined(AFX_CALIBRATOR_H__F7199ECD_E3D0_41DB_91A1_3A2588CAB7B1__INCLUDED_)
#define AFX_CALIBRATOR_H__F7199ECD_E3D0_41DB_91A1_3A2588CAB7B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCalibratorApp:
// See Calibrator.cpp for the implementation of this class
//

class CCalibratorApp : public CWinApp
{
public:
	CCalibratorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalibratorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCalibratorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALIBRATOR_H__F7199ECD_E3D0_41DB_91A1_3A2588CAB7B1__INCLUDED_)
