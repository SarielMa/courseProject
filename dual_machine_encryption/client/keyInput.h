#if !defined(AFX_KEYINPUT_H__66E76BE6_4742_43F2_8FDB_AEA46280C282__INCLUDED_)
#define AFX_KEYINPUT_H__66E76BE6_4742_43F2_8FDB_AEA46280C282__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// keyInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CkeyInput dialog

class CkeyInput : public CDialog
{
// Construction
public:
	CString s;
	int key_num;
	int P_key[10];
	CkeyInput(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CkeyInput)
	enum { IDD = IDD_keyinput };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CkeyInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CkeyInput)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnChangeEDITnum();
	afx_msg void OnEnter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYINPUT_H__66E76BE6_4742_43F2_8FDB_AEA46280C282__INCLUDED_)
