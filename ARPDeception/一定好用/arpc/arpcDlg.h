
// arpcDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CarpcDlg �Ի���
class CarpcDlg : public CDialogEx
{
// ����
public:
	CarpcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ARPC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
