// test1_1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "test1_1.h"
#include "test1_1Dlg.h"
#include "select.h"
#include "time.h"
#include "winsock2.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include <afxsock.h>
#pragma comment(lib, "ws2_32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define BACKLOG 5
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512
//#define ROOT_MAX_SIZE 512
CString radio_ID;//�㷨ID
int link_state;//�Ƿ����ӷ�����
CWinThread *pThread = NULL;
unsigned int file_send(LPVOID lParam);
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest1_1Dlg dialog

CTest1_1Dlg::CTest1_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTest1_1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTest1_1Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTest1_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTest1_1Dlg)
	DDX_Control(pDX, IDC_TAB1, m_tab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTest1_1Dlg, CDialog)
	//{{AFX_MSG_MAP(CTest1_1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_BN_CLICKED(IDC_select, Onselect)
	ON_BN_CLICKED(IDC_start, Onstart)
	ON_BN_CLICKED(IDC_link, Onlink)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTest1_1Dlg message handlers

BOOL CTest1_1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_tab.InsertItem(0,_T("page1"),0); //��ӱ�ǩ����
	m_tab.InsertItem(1,_T("page2"),1);
 
	m_page1.Create(IDD_page1,GetDlgItem(IDC_TAB1));
	m_page2.Create(IDD_page2,GetDlgItem(IDC_TAB1));

	CRect rect;//����λ��
	m_tab.GetClientRect(&rect); 
	rect.top+=40;
	rect.bottom-=10; 
	rect.left+=10; 
	rect.right-=10; 

	m_page1.MoveWindow(&rect);
	m_page2.MoveWindow(&rect);
	m_page1.ShowWindow(SW_SHOW);
	m_page2.ShowWindow(SW_HIDE);
	choose_page=1;//Ĭ�ϵ�һҳ
	text=m_page1.text;

	link_state=0;//δ���ӷ�����
	SetDlgItemText(IDC_IPADDRESS1,"127.0.0.1");

	flag=0;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTest1_1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTest1_1Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTest1_1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTest1_1Dlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int num=m_tab.GetCurSel();
    switch(num)
    {
    case 0:m_page1.ShowWindow(SW_SHOW);
           m_page2.ShowWindow(SW_HIDE);
		   choose_page=1;
           break;
    case 1:m_page1.ShowWindow(SW_HIDE);
           m_page2.ShowWindow(SW_SHOW);
		   choose_page=2;
    }
	*pResult = 0;
}

void CTest1_1Dlg::Onselect() 
{
	// TODO: Add your control notification handler code here
	Cselect dlg;
	if(dlg.DoModal()==IDOK)
	{
		SetDlgItemText(IDC_EDIT1,dlg.s);
		SetDlgItemText(IDC_STATIC,dlg.name);//Q
		key_num=dlg.key_num;
		for(int i=0;i<key_num;i++)
		{
			P_key[i]=dlg.P_key[i];
		}
		radio_ID=dlg.ID;
		UpdateData(FALSE);
	}

	
}
///////////////////////////////////////����
void CTest1_1Dlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CTest1_1Dlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
///////////////////////////////////////����


void CTest1_1Dlg::Onstart() 
{
	// TODO: Add your control notification handler code here
	int n;
	int r_ID;
	CWnd *pWnd1;
//	CWnd *pWnd2;


	r_ID=atoi(radio_ID);
	if(r_ID==0)
	{
		MessageBox("��ѡ���㷨");
		return;
	}
	//��ѡ�㷨��Ϣ
	//
	UpdateData();

	CString Addr;
	CString path;
	GetDlgItemText(IDC_IPADDRESS1,IP);
	GetDlgItemText(IDC_EDIT3,Port);
	GetDlgItemText(IDC_EDIT1,key);
	Addr=IP+":"+Port;
	UpdateData(TRUE);
	//MessageBox(ADDR); //����
	//////////////////////////socket
	WSADATA              wsaData;
	SOCKET               s_client;

	SOCKADDR_IN          ServerAddr;


	int                  s_Port;
	int                  Ret;

	char file_name[FILE_NAME_MAX_SIZE+1];
	char buffer[BUFFER_SIZE];
    //char root[ROOT_MAX_SIZE+1];·��
	FILE * fp;
//////////////////////////////////////////////////////////////////////////////////////////
	s_Port=atoi(Port);//�˿�ת��
	if ((Ret = WSAStartup(MAKEWORD(2,2), &wsaData)) != 0)
	{
		MessageBox("WSAStartup failed with error");
		return;
    }
	// Create a new socket to make a client connection.
	//��������
	if ((s_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))== INVALID_SOCKET)
	{
		MessageBox("socket failed with error");
		WSACleanup();
		return;
	}
	
	Dlg_client=s_client;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(s_Port);    
	ServerAddr.sin_addr.s_addr = inet_addr(IP);//192.168.1.131
	////////////////////////////////////////////////��������

	if (connect(s_client, (SOCKADDR *) &ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)//���������������
	{
		MessageBox("connect failed with error");
		closesocket(s_client);
		WSACleanup();
		return;
	} 
	link_state=1;
	///////////////////////////////////////////////////////
	//printf("׼����������.\n");
	//printf("�����뷢�͵���Ϣ\n");

	//�ļ����ͽ׶�
	//����ļ���
	memset(file_name,0,FILE_NAME_MAX_SIZE+1);//IP
	memset(buffer,0,BUFFER_SIZE);
	strcpy(file_name,IP);
	strncpy(buffer,file_name,strlen(file_name)>BUFFER_SIZE?BUFFER_SIZE:strlen(file_name));
	send(s_client,buffer,BUFFER_SIZE,0);
	
	memset(file_name,0,FILE_NAME_MAX_SIZE+1);
	memset(buffer,0,BUFFER_SIZE);
	strcpy(file_name,radio_ID);//�㷨ID
	memset(buffer,0,BUFFER_SIZE);
	strncpy(buffer,file_name,strlen(file_name)>BUFFER_SIZE?BUFFER_SIZE:strlen(file_name));
	send(s_client,buffer,BUFFER_SIZE,0);

	memset(file_name,0,FILE_NAME_MAX_SIZE+1);//�ӽ��ܷ�ʽ��1�ַ���2�ļ�
	CString temp;
	temp.Format("%d",choose_page);
	memset(buffer,0,BUFFER_SIZE);
	strcpy(file_name,temp);
	strncpy(buffer,file_name,strlen(file_name)>BUFFER_SIZE?BUFFER_SIZE:strlen(file_name));
	send(s_client,buffer,BUFFER_SIZE,0);

	/*memset(file_name,0,FILE_NAME_MAX_SIZE+1);//key
	memset(buffer,0,BUFFER_SIZE);
	strcpy(file_name,key);
	strncpy(buffer,file_name,strlen(file_name)>BUFFER_SIZE?BUFFER_SIZE:strlen(file_name));
	send(s_client,buffer,BUFFER_SIZE,0);*/
	
	

	switch(choose_page)
	{
	case 1://��ҳ�ַ�
		n=((CButton*)m_page1.GetDlgItem(IDC_RADIO1))->GetCheck();
		//////////////////////////
		temp.Format("%d",n);//����
		memset(buffer,0,BUFFER_SIZE);
		strcpy(buffer,temp);
		send(s_client,buffer,BUFFER_SIZE,0);
		//------------------------
		if(n)	
		{
			GetDlgItemText(IDC_EDIT1,key);//���ܻ����Կ
			text=m_page1.text;
			pWnd1=m_page1.GetDlgItem(IDC_EDIT2);
			pWnd1->EnableWindow(TRUE);
			//��������
			send(s_client,text.GetBuffer(text.GetLength()),text.GetLength(),0);
			//---
			recv(s_client,buffer,BUFFER_SIZE,0);
			result=buffer;
			MessageBox(result);
			
			m_page1.m_edit2=result;
			m_page1.UpdateData(FALSE);
		}
		else
		{
			text=m_page1.text;
			MessageBox(text);
			pWnd1=m_page1.GetDlgItem(IDC_EDIT1);
			pWnd1->EnableWindow(TRUE);
			//��������
			send(s_client,text.GetBuffer(text.GetLength()),text.GetLength(),0);
			//--
			result=buffer;//����
			recv(s_client,buffer,BUFFER_SIZE,0);
			result=buffer;
			MessageBox(result);
			
			m_page1.m_edit1=result;
			m_page1.UpdateData(FALSE);
		}
		break;
	case 2://��ҳ

		n=((CButton*)m_page2.GetDlgItem(IDC_RADIO1))->GetCheck();
		temp.Format("%d",n);//����
		memset(buffer,0,BUFFER_SIZE);
		strcpy(buffer,temp);
		send(s_client,buffer,BUFFER_SIZE,0);
		
		/*pThread = new CWinThread(file_send, (LPVOID)this);
		pThread->CreateThread(CREATE_SUSPENDED);
		pThread->ResumeThread();
*/
		MessageBox("1");
		
		if(n)
		{
			//�����ļ���
			/*memset(buffer,0,BUFFER_SIZE);
			strcpy(file_name,m_page2.file_name);
			strncpy(buffer,file_name,strlen(file_name)>BUFFER_SIZE?BUFFER_SIZE:strlen(file_name));
			send(s_client,buffer,BUFFER_SIZE,0);
			*/
		//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			path=m_page2.path;	
			FILE *file;
			file=fopen(path,"rb");
			int i = GetLastError();
			int buffi = 0;
			//fseek(file, 0, SEEK_SET);
			i = GetLastError();
			if(file==NULL)
			{
				MessageBox("File Not Found");
			}
			else
			{
				memset(buffer,0,BUFFER_SIZE);
				//int file_block_length = 0;
				while(	!feof(file) )
				{
					buffer[buffi++] = getc(file);
					if(buffi >= BUFFER_SIZE)
					{
						send(s_client,buffer,BUFFER_SIZE,0);
						buffi = 0;
					}
				}
				if(buffi > 0)
					send(s_client,buffer,buffi,0);
				fclose(file);
				//closesocket(s_client);
				shutdown(s_client,SD_SEND);
			}
							
			//���ջش���Ϣ


			memset(buffer,0,BUFFER_SIZE);
			strcpy(file_name,"12345.txt");
			fp=fopen(file_name,"wb");
			int length = 0;
			while(length=recv(s_client,buffer,BUFFER_SIZE,0))
			{
				if(length < 0)
				{
					break;
				}
				int write_length=fwrite(buffer,sizeof(char),length,fp);
				if (write_length<length)
				{
					MessageBox("LL");
				}
				memset(buffer,0,BUFFER_SIZE);
			}
			closesocket(s_client);
			fclose(fp);
			WSACleanup();
			return ;
		}
		else
		{
			path=m_page2.path;
			FILE *file;
			file=fopen(path,"rb");
			int i = GetLastError();
			int buffi = 0;
			//fseek(file, 0, SEEK_SET);
			i = GetLastError();
			if(file==NULL)
			{
				MessageBox("File Not Found");
			}
			else
			{
				memset(buffer,0,BUFFER_SIZE);
				//int file_block_length = 0;
				while(	!feof(file) )
				{
					buffer[buffi++] = getc(file);
					if(buffi >= BUFFER_SIZE)
					{
						send(s_client,buffer,BUFFER_SIZE,0);
						buffi = 0;
					}
				}
				if(buffi > 0)
					send(s_client,buffer,buffi,0);
				fclose(file);
				//closesocket(s_client);
				shutdown(s_client,SD_SEND);
			}
							
			//���ջش���Ϣ


			memset(buffer,0,BUFFER_SIZE);
			strcpy(file_name,"54321.txt");
			fp=fopen(file_name,"wb");
			int length = 0;
			while(length=recv(s_client,buffer,BUFFER_SIZE,0))
			{
				if(length < 0)
				{
					break;
				}
				int write_length=fwrite(buffer,sizeof(char),length,fp);
				if (write_length<length)
				{
					MessageBox("LL");
				}
				memset(buffer,0,BUFFER_SIZE);
			}
			closesocket(s_client);
			fclose(fp);
			WSACleanup();
			return ;
		}
		break;
	}
}

void CTest1_1Dlg::Onlink() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CString IP;
	CString Port;
	CString Addr;
	GetDlgItemText(IDC_IPADDRESS1,IP);
	GetDlgItemText(IDC_EDIT3,Port);
	Addr=IP+":"+Port;
	UpdateData(TRUE);
	//MessageBox(ADDR); //����
	//////////////////////////socket
	WSADATA              wsaData;
	SOCKET               s_client;
	SOCKADDR_IN          ServerAddr;
	int                  s_Port;
	int                  Ret;

	char file_name[FILE_NAME_MAX_SIZE+1];
	char buffer[BUFFER_SIZE];
    //char root[ROOT_MAX_SIZE+1];·��

	s_Port=atoi(Port);//�˿�ת��
	if ((Ret = WSAStartup(MAKEWORD(2,2), &wsaData)) != 0)
	{
		MessageBox("WSAStartup failed with error");
		return;
    }
	// Create a new socket to make a client connection.
	//��������
	if ((s_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))== INVALID_SOCKET)
	{
		MessageBox("socket failed with error");
		WSACleanup();
		return;
	}
	Dlg_client=s_client;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(s_Port);    
	ServerAddr.sin_addr.s_addr = inet_addr(IP);//192.168.1.131
	////////////////////////////////////////////////��������

	if (connect(s_client, (SOCKADDR *) &ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)//���������������
	{
		MessageBox("connect failed with error");
		closesocket(s_client);
		WSACleanup();
		return;
	} 
	link_state=1;
	///////////////////////////////////////////////////////
	//printf("׼����������.\n");
	//printf("�����뷢�͵���Ϣ\n");

	//�ļ����ͽ׶�
	//����ļ���
	
	strcpy(file_name,"1");
	memset(buffer,0,BUFFER_SIZE);
	strncpy(buffer,file_name,strlen(file_name)>BUFFER_SIZE?BUFFER_SIZE:strlen(file_name));
	send(s_client,buffer,BUFFER_SIZE,0);
	MessageBox("LL");
	FILE * fp = fopen(file_name,"rb");
    if(fp==NULL)
    {
        MessageBox("File Not Found");
    }
    else
    {
        memset(buffer,0,BUFFER_SIZE);
        int file_block_length = 0;
        while((file_block_length=fread(buffer,sizeof(char),BUFFER_SIZE,fp))>0)
        {

            //printf("file_block_length=%d\n",file_block_length);�����ļ����С
            if(send(s_client,buffer,file_block_length,0)<0)
            {
                printf("Send File:\t%s Failed\n", file_name);
                break;
            }
            memset(buffer,0,BUFFER_SIZE);
        }
        fclose(fp);
        printf("File:\t%s Transfer Finished\n",file_name);
    }
	///////////////////////////////////////////////////////
	/*
	char *temp;
	temp="LLLLLLLLLLLLLLLLL";
	//int i=text.GetLength();
	int i=sizeof(temp);
	if ((Ret = send(s_client,temp, i, 0)) == SOCKET_ERROR)//�������� "Lucifer��"
	{
		printf("send failed with error %d\n", WSAGetLastError());
		closesocket(s_client);
		WSACleanup();
		return;
	}
	*/
	closesocket(s_client);
	WSACleanup();
	MessageBox("�ɹ��������� ");
}

unsigned int file_send(LPVOID lParam)
{
	char file_name[FILE_NAME_MAX_SIZE+1];
	char buffer[BUFFER_SIZE];

	CTest1_1Dlg *aDlg = (CTest1_1Dlg *)lParam;
	AfxSocketInit();
	CSocket aSocket;
	CString strIP;
	CString strPort;
//	CString strText;
	
	strIP=aDlg->IP;
	strPort=aDlg->Port;

	if(!aSocket.Create())
	{
		char szMsg[1024] = {0};
		sprintf(szMsg, "create faild: %d", aSocket.GetLastError());
		AfxMessageBox(szMsg);
		return 1;
	}

	int nPort = atoi(strPort);
	
	if(aSocket.Connect(strIP, nPort))
	{
		//������Ϣ
		memset(buffer,0,BUFFER_SIZE);
		strcpy(file_name,aDlg->m_page2.file_name);
		strncpy(buffer,file_name,strlen(file_name)>BUFFER_SIZE?BUFFER_SIZE:strlen(file_name));
		aSocket.Send(buffer,BUFFER_SIZE,0);
		AfxMessageBox(buffer);
		CString path;
		path=aDlg->m_page2.path;

		FILE * fp = fopen(file_name,"rb");
		if(fp==NULL)
		{
			AfxMessageBox("File Not Found");
		}
		else
		{
			memset(buffer,0,BUFFER_SIZE);
			int file_block_length = 0;
			while((file_block_length=fread(buffer,sizeof(char),BUFFER_SIZE,fp))>0)
			{

				//printf("file_block_length=%d\n",file_block_length);�����ļ����С
				if(aSocket.Send(buffer,file_block_length,0)<0)
				{
					printf("Send File:\t%s Failed\n", file_name);
					break;
				}
				memset(buffer,0,BUFFER_SIZE);
			}
			fclose(fp);
		}
	}
	else
	{
		char szMsg[1024] = {0};
		sprintf(szMsg, "create faild: %d", aSocket.GetLastError());
		AfxMessageBox(szMsg);
	}

	aSocket.Close();
	return 1;
}