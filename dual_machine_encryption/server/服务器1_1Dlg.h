// ·þÎñÆ÷1_1Dlg.h : header file
//

#if !defined(AFX_1_1DLG_H__E5DCC865_D61B_4D5F_BA20_920083B57DEF__INCLUDED_)
#define AFX_1_1DLG_H__E5DCC865_D61B_4D5F_BA20_920083B57DEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy1_1Dlg dialog

class CMy1_1Dlg : public CDialog
{
// Construction
public:
	CString C_file_name;

	CMy1_1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy1_1Dlg)
	enum { IDD = IDD_MY1_1_DIALOG };
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy1_1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy1_1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void Onstart();
	afx_msg void Ondata();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_1_1DLG_H__E5DCC865_D61B_4D5F_BA20_920083B57DEF__INCLUDED_)
