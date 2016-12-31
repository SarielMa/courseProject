#if !defined(AFX_SELECT_H__48E25582_0BD6_4443_8FFE_C61238C49F58__INCLUDED_)
#define AFX_SELECT_H__48E25582_0BD6_4443_8FFE_C61238C49F58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// select.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cselect dialog

class Cselect : public CDialog
{
// Construction
public:
	CString ID;
	CString name;
	CString s;
	int P_key[10];
	int key_num;
	Cselect(CWnd* pParent = NULL);   // standard constructor
	//CString temp;//Q
// Dialog Data
	//{{AFX_DATA(Cselect)
	enum { IDD = IDD_algorithm };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cselect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cselect)
	afx_msg void Onchoose();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio10();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECT_H__48E25582_0BD6_4443_8FFE_C61238C49F58__INCLUDED_)
