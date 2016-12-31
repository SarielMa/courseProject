
// arpcDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CarpcDlg 对话框
class CarpcDlg : public CDialogEx
{
// 构造
public:
	CarpcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ARPC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo;
	afx_msg void OnBnClickedButton1();
	CString m_edit;
	CEdit m_edit2;
	int ratio1;
	CEdit m_edit3;
	CButton ratio;
};
