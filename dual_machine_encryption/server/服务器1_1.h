// 服务器1_1.h : main header file for the 服务器1_1 application
//

#if !defined(AFX_1_1_H__F633C8CF_F76E_4D4B_993C_8AC79AAE05CD__INCLUDED_)
#define AFX_1_1_H__F633C8CF_F76E_4D4B_993C_8AC79AAE05CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMy1_1App:
// See 服务器1_1.cpp for the implementation of this class
//

class CMy1_1App : public CWinApp
{
public:
	CMy1_1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy1_1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMy1_1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_1_1_H__F633C8CF_F76E_4D4B_993C_8AC79AAE05CD__INCLUDED_)
