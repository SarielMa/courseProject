// test1_1.h : main header file for the TEST1_1 application
//

#if !defined(AFX_TEST1_1_H__EBC7164C_05A8_40A2_9694_D28174362DEA__INCLUDED_)
#define AFX_TEST1_1_H__EBC7164C_05A8_40A2_9694_D28174362DEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTest1_1App:
// See test1_1.cpp for the implementation of this class
//

class CTest1_1App : public CWinApp
{
public:
	CTest1_1App();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest1_1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTest1_1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST1_1_H__EBC7164C_05A8_40A2_9694_D28174362DEA__INCLUDED_)
