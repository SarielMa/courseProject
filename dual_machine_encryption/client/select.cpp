// select.cpp : implementation file
//

#include "stdafx.h"
#include "test1_1.h"
#include "select.h"
#include "keyInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cselect dialog


Cselect::Cselect(CWnd* pParent /*=NULL*/)
	: CDialog(Cselect::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cselect)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Cselect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cselect)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cselect, CDialog)
	//{{AFX_MSG_MAP(Cselect)
	ON_BN_CLICKED(IDC_choose, Onchoose)
	ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cselect message handlers

void Cselect::Onchoose() 
{
	// TODO: Add your control notification handler code here
	int	nID;
	nID=GetCheckedRadioButton(IDC_RADIO1,IDC_RADIO12);//��ȡ��ѡ�ռ�ID�������nID��
	GetDlgItem(nID)->GetWindowText(name);
	ID.Format("%d",nID);
	CDialog::OnOK();
}

BOOL Cselect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//��ʼ����ѡ��ť
	CheckRadioButton(IDC_RADIO1,IDC_RADIO12,IDC_RADIO1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Cselect::OnRadio10() //XXXX������Կ�������
{
	// TODO: Add your control notification handler code here
	CkeyInput dlg;
	int n=((CButton*)GetDlgItem(IDC_RADIO10))->GetCheck();
	if(n)
	{
		if(dlg.DoModal()==IDOK)
		{
			s=dlg.s;
			key_num=dlg.key_num;
			for(int i=0;i<key_num;i++)
			{
				P_key[i]=dlg.P_key[i];
			}
			//MessageBox(s);
		}
		//pWnd1->EnableWindow(TRUE);
		//pWnd2->EnableWindow(FALSE);
		//SetDlgItemText(IDC_EDIT1,_T(""));//����ʱ���
	}
}
