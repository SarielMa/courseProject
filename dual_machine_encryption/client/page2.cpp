// page2.cpp : implementation file
//

#include "stdafx.h"
#include "test1_1.h"
#include "page2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cpage2 dialog


Cpage2::Cpage2(CWnd* pParent /*=NULL*/)
	: CDialog(Cpage2::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cpage2)
	//}}AFX_DATA_INIT
}


void Cpage2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cpage2)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cpage2, CDialog)
	//{{AFX_MSG_MAP(Cpage2)
	ON_BN_CLICKED(IDC_browse1, Onbrowse1)
	ON_BN_CLICKED(IDC_browse2, Onbrowse2)
	ON_BN_CLICKED(IDC_open, Onopen)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cpage2 message handlers

void Cpage2::Onbrowse1() 
{

	UpdateData();
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"文本文档(*.txt)|*.txt|C++文件(*.cpp,*.h)|*.cpp;*.h");
	if(dlg.DoModal()==IDOK)
	{
		path=dlg.GetPathName();
		file_name=dlg.GetFileName();
		//m_Edit1.SetWindowText(dlg.GetPathName());
		SetDlgItemText(IDC_EDIT1,path);//在编辑框中显示path的文字
		UpdateData(FALSE);
	}
}

void Cpage2::Onbrowse2() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"文本文档(*.txt)|*.txt|C++文件(*.cpp,*.h)|*.cpp;*.h");
	if(dlg.DoModal()==IDOK)
	{
		path=dlg.GetPathName();
		file_name=dlg.GetFileName();
		//m_Edit1.SetWindowText(dlg.GetPathName());
		SetDlgItemText(IDC_EDIT2,path);
		UpdateData(FALSE);
	}
	
}

void Cpage2::Onopen() 
{
	// TODO: Add your control notification handler code here
	//UpdateData(TRUE);
	//MessageBox(m_path1);
	CString path;
	int num=1;
	switch(num)
	{
	case 1:
		path=_T("");
		break;
	case 2:
		path=_T("");
		break;
	}
	CDialog::OnOK();
}

BOOL Cpage2::OnInitDialog() 
{
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
		   //SetDlgItemText(IDC_BTN_ENABLED,_T("禁用控件"));
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void Cpage2::OnRadio1() 
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

void Cpage2::OnRadio2() 
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

void Cpage2::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_EDIT1,path);
	file_name=path;
	UpdateData(TRUE);
}

void Cpage2::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	GetDlgItemText(IDC_EDIT2,path);
	file_name=path;
	UpdateData(TRUE);
}
