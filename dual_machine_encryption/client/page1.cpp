// page1.cpp : implementation file
//

#include "stdafx.h"
#include "test1_1.h"
#include "page1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cpage1 dialog


Cpage1::Cpage1(CWnd* pParent /*=NULL*/)
	: CDialog(Cpage1::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cpage1)
	m_edit2 = _T("");
	m_edit1 = _T("");
	//}}AFX_DATA_INIT
}


void Cpage1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cpage1)
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cpage1, CDialog)
	//{{AFX_MSG_MAP(Cpage1)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cpage1 message handlers

void Cpage1::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	CWnd *pWnd1=GetDlgItem(IDC_EDIT1);//获得空间句柄
	CWnd *pWnd2=GetDlgItem(IDC_EDIT2);//获得空间句柄
	int n=((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck();
	if(n)
	{
		pWnd1->EnableWindow(TRUE);
		pWnd2->EnableWindow(FALSE);
		SetDlgItemText(IDC_EDIT1,_T(""));//可用时清空
	}
	
}

void Cpage1::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	CWnd *pWnd1=GetDlgItem(IDC_EDIT1);//获得空间句柄
	CWnd *pWnd2=GetDlgItem(IDC_EDIT2);//获得空间句柄
	int n=((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck();
	if(n)
	{
		pWnd1->EnableWindow(FALSE);
		pWnd2->EnableWindow(TRUE);
		SetDlgItemText(IDC_EDIT2,_T(""));//可用时清空
	}
}

BOOL Cpage1::OnInitDialog() 
{
	
	// TODO: Add extra initialization here
	CDialog::OnInitDialog();
	CWnd *pWnd1=GetDlgItem(IDC_EDIT1);//获得空间句柄
	CWnd *pWnd2=GetDlgItem(IDC_EDIT2);//获得空间句柄

	CheckRadioButton(IDC_RADIO1,IDC_RADIO2,IDC_RADIO1);//初始化单选按钮
	// TODO: Add extra initialization here
	if(((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck())
	{
		if (pWnd2->IsWindowEnabled())//初始化禁用edit2
		{
		   pWnd2->EnableWindow(FALSE);
		}
	}
	SetDlgItemText(IDC_EDIT1,_T(""));
	SetDlgItemText(IDC_EDIT2,_T(""));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Cpage1::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_EDIT1,text);
	UpdateData(TRUE);
}

void Cpage1::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_EDIT2,text);
	UpdateData(TRUE);
}
