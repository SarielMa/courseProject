#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CResult �Ի���

class CResult : public CDialogEx
{
	DECLARE_DYNAMIC(CResult)

public:
	CResult(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CResult();

// �Ի�������
	enum { IDD = IDD_RESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	//CListCtrl resultListControl;
	void fillResult(char*);
	void SetCtrlStyle(HWND hWnd, DWORD dwNewStyle);
	//CListBox listResult;

	int queryFill(MYSQL *sock,char*);
	CString DBName;
	CListCtrl listControlResult;
};
