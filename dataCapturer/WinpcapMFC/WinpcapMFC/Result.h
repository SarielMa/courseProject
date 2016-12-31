#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CResult 对话框

class CResult : public CDialogEx
{
	DECLARE_DYNAMIC(CResult)

public:
	CResult(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CResult();

// 对话框数据
	enum { IDD = IDD_RESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
