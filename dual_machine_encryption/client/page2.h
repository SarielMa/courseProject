#if !defined(AFX_PAGE2_H__FFC5D748_B1A1_4F58_8F24_27894E10AC33__INCLUDED_)
#define AFX_PAGE2_H__FFC5D748_B1A1_4F58_8F24_27894E10AC33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// page2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cpage2 dialog

class Cpage2 : public CDialog
{
// Construction
public:
	CString path;
	CString text;
	CString file_name;
	Cpage2(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(Cpage2)
	enum { IDD = IDD_page2 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cpage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cpage2)
	afx_msg void Onbrowse1();
	afx_msg void Onbrowse2();
	afx_msg void Onopen();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGE2_H__FFC5D748_B1A1_4F58_8F24_27894E10AC33__INCLUDED_)
