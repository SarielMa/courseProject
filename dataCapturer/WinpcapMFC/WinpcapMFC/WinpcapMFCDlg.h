
// WinpcapMFCDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CWinpcapMFCDlg �Ի���
class CWinpcapMFCDlg : public CDialogEx
{
// ����
public:
	CWinpcapMFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

private:
	static CWinpcapMFCDlg *instance;//to use the not static function

// �Ի�������
	enum { IDD = IDD_WINPCAPMFC_DIALOG };

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
	BOOL checkIP;
	BOOL checkICMP;
	BOOL checkARP;
	BOOL checkTCP;
	BOOL checkUDP;
	BOOL checkHTTP;
	BOOL checkSMTP;
	BOOL checkFTP;
	BOOL checkDHCP;
	int packageNum;
	CString databaseName;
	CString filePath;
	afx_msg void OnBnClickedBtnFile();
	afx_msg void OnBnClickedOk();

	int winpcpCatch();
	//void packet_handler(u_char *param,  const struct pcap_pkthdr *header, const u_char *pkt_data);

	CString outputPackage;
	afx_msg void OnCbnSelchangeComboEth();
	CComboBox comboBoxEth;
	afx_msg void OnCbnSetfocusComboEth();
	CString ethName;
	BOOL saveToDB;
	CProgressCtrl proBar;
	static DWORD ThreadProc (LPVOID lpdwThreadParam );
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//CListBox outputList;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnResult();

	afx_msg void OnBnClickedCkTodb();
	CEdit DBEditBox;
	CListCtrl resultListControl;
	void SetCtrlStyle(HWND hWnd, DWORD dwNewStyle);
	static DWORD ThreadProcInsert (LPVOID lpdwThreadParam );
	void insertForm();


	afx_msg void OnEnChangeEditPacknum();
};
