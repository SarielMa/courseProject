// test1_1Dlg.h : header file
//

#if !defined(AFX_TEST1_1DLG_H__01B33946_3075_420C_A3E4_DFFC2705B2B3__INCLUDED_)
#define AFX_TEST1_1DLG_H__01B33946_3075_420C_A3E4_DFFC2705B2B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "page1.h"
#include "page2.h"
#include "winsock2.h"
/////////////////////////////////////////////////////////////////////////////
// CTest1_1Dlg dialog

class CTest1_1Dlg : public CDialog
{
// Construction
public:
	CString IP;
	CString Port;
	int flag;
	CString key;
	CString text;//
	CString result;//
	CTest1_1Dlg(CWnd* pParent = NULL);	// standard constructor
	Cpage1 m_page1;
	Cpage2 m_page2;
	int choose_page;
	int P_key[10];
	int key_num;
	SOCKET	Dlg_client;
// Dialog Data
	//{{AFX_DATA(CTest1_1Dlg)
	enum { IDD = IDD_TEST1_1_DIALOG };
	CTabCtrl	m_tab;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest1_1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTest1_1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void Onselect();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void Onstart();
	afx_msg void Onlink();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST1_1DLG_H__01B33946_3075_420C_A3E4_DFFC2705B2B3__INCLUDED_)
