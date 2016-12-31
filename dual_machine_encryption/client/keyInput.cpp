// keyInput.cpp : implementation file
//

#include "stdafx.h"
#include "test1_1.h"
#include "keyInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CkeyInput dialog


CkeyInput::CkeyInput(CWnd* pParent /*=NULL*/)
	: CDialog(CkeyInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CkeyInput)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CkeyInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CkeyInput)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CkeyInput, CDialog)
	//{{AFX_MSG_MAP(CkeyInput)
	ON_EN_CHANGE(IDC_EDIT_num, OnChangeEDITnum)
	ON_BN_CLICKED(IDC_ENTER, OnEnter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CkeyInput message handlers



BOOL CkeyInput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	UpdateData();
	// TODO: Add extra initialization here
	CWnd *pWnd[10];
	pWnd[0]=GetDlgItem(IDC_EDIT1);//获得空间句柄
	pWnd[1]=GetDlgItem(IDC_EDIT2);
	pWnd[2]=GetDlgItem(IDC_EDIT3);
	pWnd[3]=GetDlgItem(IDC_EDIT4);
	pWnd[4]=GetDlgItem(IDC_EDIT5);
	pWnd[5]=GetDlgItem(IDC_EDIT6);
	pWnd[6]=GetDlgItem(IDC_EDIT7);
	pWnd[7]=GetDlgItem(IDC_EDIT8);
	pWnd[8]=GetDlgItem(IDC_EDIT9);
	pWnd[9]=GetDlgItem(IDC_EDIT10);
	for(int i=0;i<10;i++)
	{
		pWnd[i]->EnableWindow(FALSE);
	}
	SetDlgItemText(IDC_EDIT_num,_T(""));
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CkeyInput::OnChangeEDITnum() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CWnd *pWnd[10];
	pWnd[0]=GetDlgItem(IDC_EDIT1);//获得空间句柄
	pWnd[1]=GetDlgItem(IDC_EDIT2);
	pWnd[2]=GetDlgItem(IDC_EDIT3);
	pWnd[3]=GetDlgItem(IDC_EDIT4);
	pWnd[4]=GetDlgItem(IDC_EDIT5);
	pWnd[5]=GetDlgItem(IDC_EDIT6);
	pWnd[6]=GetDlgItem(IDC_EDIT7);
	pWnd[7]=GetDlgItem(IDC_EDIT8);
	pWnd[8]=GetDlgItem(IDC_EDIT9);
	pWnd[9]=GetDlgItem(IDC_EDIT10);
	for(int i=0;i<10;i++)
	{
		pWnd[i]->EnableWindow(FALSE);
	}
	CString num;
	GetDlgItemText(IDC_EDIT_num,num);
	UpdateData(TRUE);
	key_num=atoi(num);
	if(key_num>10||key_num<0)
	{
		MessageBox("请输入0-10之间的数字");
		SetDlgItemText(IDC_EDIT_num,_T(""));
		for(int i=0;i<10;i++)
		{
			pWnd[i]->EnableWindow(FALSE);
		}
	}
	else
	{
		for(i=0;i<key_num;i++)
		{
			pWnd[i]->EnableWindow(TRUE);
		}
	}
}

void CkeyInput::OnEnter() 
{
	// TODO: Add your control notification handler code here
	CString s1,s_temp;
	s1="(";
	s=s1+s;
	CWnd *pWnd[10];
	pWnd[0]=GetDlgItem(IDC_EDIT1);//获得空间句柄
	pWnd[1]=GetDlgItem(IDC_EDIT2);
	pWnd[2]=GetDlgItem(IDC_EDIT3);
	pWnd[3]=GetDlgItem(IDC_EDIT4);
	pWnd[4]=GetDlgItem(IDC_EDIT5);
	pWnd[5]=GetDlgItem(IDC_EDIT6);
	pWnd[6]=GetDlgItem(IDC_EDIT7);
	pWnd[7]=GetDlgItem(IDC_EDIT8);
	pWnd[8]=GetDlgItem(IDC_EDIT9);
	pWnd[9]=GetDlgItem(IDC_EDIT10);
	for(int i=0;i<key_num;i++)
	{
		GetDlgItemText(pWnd[i]->GetDlgCtrlID(),s_temp);
		P_key[i]=atoi(s_temp);
		s=s+s_temp;
		if(i==key_num-1)
			break;
		s=s+",";
	}
	s=s+")";
	CDialog::OnOK();
}
