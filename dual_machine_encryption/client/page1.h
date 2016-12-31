#if !defined(AFX_PAGE1_H__DEC5A2DA_873E_438D_9AF2_0C1CA3815012__INCLUDED_)
#define AFX_PAGE1_H__DEC5A2DA_873E_438D_9AF2_0C1CA3815012__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// page1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cpage1 dialog

class Cpage1 : public CDialog
{
// Construction
public:
	CString path;
	CString text;
	Cpage1(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(Cpage1)
	enum { IDD = IDD_page1 };
	CString	m_edit2;
	CString	m_edit1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cpage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cpage1)
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE1_H__DEC5A2DA_873E_438D_9AF2_0C1CA3815012__INCLUDED_)
