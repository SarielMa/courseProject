// 服务器1_1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "服务器1_1.h"
#include "服务器1_1Dlg.h"
#include "time.h"
#include "winsock2.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "RSA2.h"
#include "CA.h"

#include "Caesar.h"
#include "KeyWord.h"
#include "Vigenere.h"
#include "ColumnPermutation.H"
#include "RC4.h"
#include "DES.h"
#include "playfair.h"
#include "autokey_plaintext.h"
#include "autokey_ciphertext.h"
#include "Permutation.h"

#pragma comment(lib, "ws2_32.lib")
#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define TIME 1//时间列
#define MESSAGE 2//信息列
#define BACKLOG 5
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512
unsigned int file_receive(LPVOID lParam);
int num;
	CString key;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
CWinThread *pThread = NULL;

bool m_exit = false;
unsigned int StartServer(LPVOID lParam);


void StopServer()
{
	m_exit = true;
}
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
// CMy1_1Dlg dialog

CMy1_1Dlg::CMy1_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy1_1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy1_1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy1_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy1_1Dlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy1_1Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy1_1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_start, Onstart)
	ON_BN_CLICKED(IDC_data, Ondata)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy1_1Dlg message handlers

BOOL CMy1_1Dlg::OnInitDialog()
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
	//list
	num=0;//序号//行号
	//list=0;
	m_list.InsertColumn(0,"#",LVCFMT_LEFT,40);
	m_list.InsertColumn(1,"time",LVCFMT_LEFT,160);
	m_list.InsertColumn(2,"message",LVCFMT_LEFT,380);
	//信息输出功能块
	//////////////////////////////////////////////添加一行信息
	//num++;
	CString msge;
	CString t;
	msge.Format("%.4d",num);
	m_list.InsertItem(num,msge);//序号列
	//获取当前时间
	time_t timep;
	time (&timep);
	t=asctime(gmtime(&timep));
	m_list.SetItemText(num,TIME,t);
	//t
	m_list.SetItemText(num,MESSAGE,"初始化完成");
	////////////////////////////////////////////////////
	/*
	num++;
	CString msge;
	CString t;
	msge.Format("%.4d",num);
	m_list.InsertItem(num,msge);
	time_t timep;
	time (&timep);
	t=asctime(gmtime(&timep));
	m_list.SetItemText(num,TIME,t);
	//t
	m_list.SetItemText(num,MESSAGE,"");
	*/
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy1_1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CMy1_1Dlg::OnPaint() 
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
HCURSOR CMy1_1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}






void CMy1_1Dlg::Onstart() 
{
	pThread = new CWinThread(StartServer, (LPVOID)this);
	pThread->CreateThread(CREATE_SUSPENDED);
	pThread->ResumeThread();
}

void CMy1_1Dlg::Ondata() 
{
	// TODO: Add your control notification handler code here
	
}

unsigned int StartServer(LPVOID lParam)
{
	CMy1_1Dlg *aDlg = (CMy1_1Dlg *)lParam;
	
	char file_name[FILE_NAME_MAX_SIZE+1];

	char                 DataBuffer[BUFFER_SIZE];
	CString IP;
	//
	CString msge;
	CString t;
	time_t timep;
	int r_ID=0;
	int choose_page;
	int n;
	FILE *fp;
/////////////////////////////////////////////////////////////////////////////////////////
	if (!AfxSocketInit())
	{
		AfxMessageBox("LL");
		return 1;
	}
	CString strPort;
	aDlg->GetDlgItemText(IDC_EDIT1, strPort);	//端口
	UINT nPort = atoi(strPort);
	//socket------------------------------------------------	
	CSocket aSocket, serverSocket;
	if (!aSocket.Socket())
	{
		char szError[256] = {0};	
		sprintf(szError, "Create Faild: %d", GetLastError());
		AfxMessageBox(szError);
		return 1; 
	}
	BOOL bOptVal = TRUE;
	int bOptLen = sizeof(BOOL);
	aSocket.SetSockOpt(SO_REUSEADDR, (void *)&bOptVal, bOptLen, SOL_SOCKET);
	//绑定
	if (!aSocket.Bind(nPort))
	{
		char szError[256] = {0};	
		sprintf(szError, "Bind Faild: %d", GetLastError());	
		AfxMessageBox(szError);	
		return 1; 
	}
	//
	if(!aSocket.Listen(30))
	{	
		char szError[256] = {0};
		sprintf(szError, "Listen Faild: %d", GetLastError());
		AfxMessageBox(szError);
		return 1;
	}
	num++;
	msge.Format("%.4d",num);
	aDlg->m_list.InsertItem(num,msge);
	time (&timep);
	t=asctime(gmtime(&timep));
	aDlg->m_list.SetItemText(num,TIME,t);
	aDlg->m_list.SetItemText(num,MESSAGE,"监听...");
	while(!m_exit)
	{	
		if(!aSocket.Accept(serverSocket))
		{
			
			continue;
		}
		else
		{//1
			//显示信息
			//AfxMessageBox("LLL");
			serverSocket.Receive(DataBuffer,BUFFER_SIZE);//接收信息IP
			IP.Format("%s",DataBuffer);//接收加密算法
			
			memset(DataBuffer,0,BUFFER_SIZE);
			memset(file_name,0,FILE_NAME_MAX_SIZE+1);
			serverSocket.Receive(DataBuffer,BUFFER_SIZE);//接收信息
			strcpy(file_name,DataBuffer);//接收加密算法
			r_ID=atoi(file_name);

			memset(DataBuffer,0,BUFFER_SIZE);
			memset(file_name,0,FILE_NAME_MAX_SIZE+1);
			serverSocket.Receive(DataBuffer,BUFFER_SIZE);//接收信息
			strcpy(file_name,DataBuffer);//接收加解密方式
			choose_page=atoi(file_name);

			memset(DataBuffer,0,BUFFER_SIZE);
			memset(file_name,0,FILE_NAME_MAX_SIZE+1);
			serverSocket.Receive(DataBuffer,BUFFER_SIZE);//接收加密或解密选择，1加密
			n=atoi(DataBuffer);

		/*	memset(DataBuffer,0,BUFFER_SIZE);//key
			memset(file_name,0,FILE_NAME_MAX_SIZE+1);
			serverSocket.Receive(DataBuffer,BUFFER_SIZE);//接收信息
			strcpy(file_name,DataBuffer);
			key.Format("%s",file_name);//
			AfxMessageBox(key);*/
			////////////////////////////////////
			CString text;
			CString result;

			CString m_KEY = "2";//承接密钥 已写定！！！！！！！！！！！

			/*************  RSA密钥存放处  ************/
			//用的是文件
			//----------------------------------------


			//------------CA密钥存放处--------------
			int Length=3;
			int Random=2;
			char* ca_key="010";
			int Rule=30;
			//------------------------------------


			//------------Permutation密钥存放处---------
//			int key_num;
//			int P_key[10];
			//-----------------------------------------
	
			switch(choose_page)
			{//2
			case 1://左页
				//显示信息
				num++;
				msge.Format("%.4d",num);
				aDlg->m_list.InsertItem(num,msge);
				time (&timep);
				t=asctime(gmtime(&timep));
				aDlg->m_list.SetItemText(num,TIME,t);
				if(n)
				{
					aDlg->m_list.SetItemText(num,MESSAGE,"接收加密字符");
				}
				else
				{
					aDlg->m_list.SetItemText(num,MESSAGE,"接收解密字符");
				}
	//------------------------------------------------------------------------------------------------------------
				memset(DataBuffer,0,BUFFER_SIZE);
				serverSocket.Receive(DataBuffer,BUFFER_SIZE);//接收信息
				text.Format("%s",DataBuffer);
				//text保存信息
				//添加加密算法

				switch(r_ID)//字符串加密算法
				{
				case 1009://CAESAR
					{
						CAESAR Caesar;
						int CAESAR_key = atoi(m_KEY);//密钥
						if(n)
						{
							Caesar.ciphertext = Caesar.INCODE(text.GetBuffer(0) , CAESAR_key);
							text.ReleaseBuffer();
							result = Caesar.ciphertext.c_str();
						}
						else
						{
							Caesar.plaintext = Caesar.DECODE(text.GetBuffer(0) , CAESAR_key);
							text.ReleaseBuffer();
							result=Caesar.plaintext.c_str();
						}

						break;
					}
				case 1010://radio 2 keyword
					{
						KEYWORD KeyWord;
						KeyWord.KeyTable_INIT((LPSTR)(LPCTSTR)m_KEY.GetBuffer(0));
						m_KEY.ReleaseBuffer();

						if(n)
						{
							KeyWord.ciphertext = KeyWord.INCODE(text.GetBuffer(0));
							text.ReleaseBuffer();
							result = KeyWord.ciphertext.c_str();
						}
						else
						{
							KeyWord.plaintext = KeyWord.DECODE(text.GetBuffer(0));
							text.ReleaseBuffer();
							result = KeyWord.plaintext.c_str();
						}

						break;
					}
				case 1011://radio 3 vigenere
					{
						VIGENERE Vigenere;
						Vigenere.key = m_KEY.GetBuffer(0);
						m_KEY.ReleaseBuffer();

						if(n)
						{
							Vigenere.plaintext = text.GetBuffer(0);
							text.ReleaseBuffer();
							Vigenere.plaintext = Vigenere.Str_erase(Vigenere.plaintext);
							Vigenere.INCODE();
							result = Vigenere.ciphertext.c_str();
						}
						else
						{
							Vigenere.ciphertext = text.GetBuffer(0);
							text.ReleaseBuffer();
							Vigenere.ciphertext = Vigenere.Str_erase(Vigenere.ciphertext);
							Vigenere.DECODE();
							result = Vigenere.plaintext.c_str();
						}

						break;
					}
				case 1012://radio 4 column permutation
					{
						COLUMN_PERMUTATION COL_PER;
						COL_PER.key = m_KEY.GetBuffer(0);
						m_KEY.ReleaseBuffer();
						
						if(n)
						{
							COL_PER.plaintext = text.GetBuffer(0);
							text.ReleaseBuffer();
							COL_PER.plaintext = COL_PER.Str_erase(COL_PER.plaintext); //去除非字母
							COL_PER.INCODE();
							result = COL_PER.CIPHERTEXT.c_str();
						}
						else
						{
							COL_PER.deciphertext = text.GetBuffer(0);
							text.ReleaseBuffer();
							COL_PER.deciphertext = COL_PER.Str_erase(COL_PER.deciphertext);
							COL_PER.DECODE();
							result = COL_PER.PLAINTEXT.c_str();
						}

						break;
					}
				case 1013://radio 5 rc4----------------------------------rc4字符串加解密不适用
					{
						if(n)
						{
						}
						else
						{
						}

						break;
					}
				case 1015://radio 6 des
					{
						DES Cdes;
						Cdes.key = m_KEY.GetBuffer(0);
						m_KEY.ReleaseBuffer();

						if(n)
						{
							Cdes.plaintext = text.GetBuffer(0);
							text.ReleaseBuffer();
							Cdes.StringIncode();
							result = Cdes.CIPHERTEXT.c_str();
						}
						else
						{
							Cdes.deCipher = text.GetBuffer(0);
							text.ReleaseBuffer();
							Cdes.StringDecode();
							result = Cdes.deplaintext.c_str();
						}

						break;
					}
				case 1016://radio 7 playfair
					{
						Playfair playfair;
						string playfair_key = m_KEY.GetBuffer(0);
						m_KEY.ReleaseBuffer();

						if(n)
						{
							playfair.ciphertext = playfair.keyboard_plain(text.GetBuffer(0) , playfair_key);
							text.ReleaseBuffer();
							result = playfair.ciphertext.c_str();
						}
						else
						{
							playfair.plaintext = playfair.keyboard_cipher(text.GetBuffer(0) , playfair_key);
							text.ReleaseBuffer();
							result = playfair.plaintext.c_str();
						}

						break;
					}
				case 1017://radio 8 rsa
					{
						int i;
						char  c;
						int  p[100],q[100],nn[100],d[100],e[100],m[100],p1[100],q1[100];
						struct rsan *head,*h1,*h2,*h3,*h4;
						for(i=0;i<100;i++)
							m[i]=p[i]=q[i]=nn[i]=d[i]=e[i]=0;
						for(i=0;i<100;i++)
							m[i]=p[i]=q[i]=nn[i]=d[i]=e[i]=0;
						RSA ob;
						if(n)//sjia
						{
							
							char*filename="d:\\mima\\mima4.txt";//文件密钥开始
				 	   ob.loadpkey(e,nn,filename);
							filename="d:\\mima\\mima5.txt";
						ob.loadskey(d,nn,filename); //文件密钥结束

					h3=(struct rsan * )malloc(LENGTH);
		//char *ch="ma";
						int sum;
						int x1=0;
						char ch3;
						
						char* rsa_ch=text.GetBuffer(text.GetLength());
						struct rsan *p1=(struct rsan * )malloc(LENGTH);
						sum=ob.jiami(  e,  nn, rsa_ch,h3);
						char *b=new char[sum];
						struct rsan *p=h3;
			//ob.jiemi(  d,  n, h1);
			
			
					 if(h3!=NULL)
					 do
					 {
					  ob.expmod( p->num , e ,nn ,p1->num);
					  ch3=p1->num[98];
					  //printf("%c",ch3);
					  b[x1]=ch3;
					  x1++;
     
					  if ((p1->num[99]/10) ==0)/*/判断p1->num[99]的是否大于十；*/
					  {
					   ch3=0+48;
					  // printf("%c",ch3);
						b[x1]=ch3;
					  x1++;
 
					   ch3=p1->num[99]+48;
					  // printf("%c",ch3);
						b[x1]=ch3;
					  x1++;

					  }
					  else
					  {
					   ch3=p1->num[99]/10+48;
						  //      printf("%c",ch3);
								 b[x1]=ch3;
								 x1++;
								
   
					   ch3=p1->num[99]%10+48;
					  // printf("%c",ch3);
						b[x1]=ch3;
					  x1++;
  
  
					  }

						 for(i=0;i<p1->num[99];i++)
						 {
					   //printf("%d",p1->num[i]);
   
							 ch3=p1->num[i]+48;
							  b[x1]=ch3;
							 x1++;
						}
						 p=p->next;
					  p1=(struct rsan * )malloc(LENGTH);
					 }while(p!=NULL);
					 printf("\n完成!\n");
					 //字符串加密
					result.Format("%s",b);
					result = result.Left(x1);
						}
						else//sjie
						{
							char*filename="d:\\mima\\mima4.txt";//文件密钥开始
				    ob.loadpkey(e,nn,filename);
					filename="d:\\mima\\mima5.txt";
					ob.loadskey(d,nn,filename); //文件密钥结束

			int sum,i=0;
			int temp;
			char ch2;
			int k=0;
			h4=(struct rsan * )malloc(LENGTH);
		//	char* ch="1206509232800810794775512039905399152787041554";
			//h1=ob.jiami(  e,  n, head);
		char *rsa_ch=text.GetBuffer(text.GetLength());
			sum=ob.jiemi( d,nn,rsa_ch,h4);
			char *a=new char[sum];
			struct rsan * p1=h4;
			struct rsan *p2;
			p2=(struct rsan * )malloc(LENGTH);
			if(h4!=NULL)/*/temp为暂存ASIIC码的int值*/
				  do
				   {
					for(i=0;i<100;i++)
					 p2->num[i]=0;

					ob.expmod( p1->num , d ,nn ,p2->num);   
					temp=p2->num[0]+p2->num[1]*10+p2->num[2]*100;
				  if (( p2->num[98])=='0')
					{
					   temp=0-temp;
					} 
						ch2=temp;/*  str[k]--->ch */
				
						 a[k]=ch2;
						k++;
						 p1=p1->next;
				  p2=(struct rsan * )malloc(LENGTH);
				  }while (p1!=NULL);

						else if ((c=='0'))
							break;
					
					result.Format("%s",a);
					result = result.Left(sum);
						}

						break;
					}
				case 1018://radio 9 ca
					{
						CA Ca;
						if(n)
						{
							ele* head=NULL;
					ele* p1;
					ele* p2;
					char *results;
					char ch;
					int i=0;
				/*	int Length=atoi(length);
					int Random=atoi(random);
					int Rule=atoi(rule);
				//	
					char* ca_key=CA_key.GetBuffer(CA_key.GetLength());*/
					char* x=text.GetBuffer(text.GetLength());
				//	AfxMessageBox(x);
				//	char *ca="010";
					fflush(stdin);
					while((ch=x[i])!='\0')
					{
				
						if(head==NULL)
						{
							head=(ele*)malloc(CA_len);
							head->a=ch;
							head->c=ch;
							p1=head;
							p2=head;
						}
							else
							{
								p1=(ele*)malloc(CA_len);
								p1->a=ch;
								p1->c=ch;
								p2->next=p1;
								p2=p1;
							}
							i++;
					}
					p1=head;
					p2->next=NULL;
					
					int caxx=Ca.ca_sjiami(head,i,Length,Random,ca_key,Rule);//...........................
					results=new char[caxx];
					int c=0;
					while(p1->next!=NULL)
					{
						for( i=0;i<=7;i++)
							{
								results[c]=p1->b[7-i]+48;
								c++;
							}
						p1=p1->next;
					}
					for( i=0;i<=7;i++)
					{
							results[c]=p1->b[7-i]+48;
							c++;
						
					}
				//	CString n;
				//	n.Format("%d",caxx);
//					MessageBox(n);
				//	AfxMessageBox(results);
					result.Format("%s",results);
						}
						else
						{
							ele* head=NULL;
							ele* p1;
							ele* p2;
							char *results1;
							char ch;
							int i=0;
				/*	int Length=atoi(length);
					int Random=atoi(random);
					int Rule=atoi(rule);
				//	
					char* ca_key=CA_key.GetBuffer(CA_key.GetLength());*/
					char* x=text.GetBuffer(text.GetLength());
				//	AfxMessageBox(x);
				//	char *ca="010";
					fflush(stdin);
					int s=0;
					while((ch=x[s])!='\0')
					{
						if(head==NULL)
						{
							head=(ele*)malloc(CA_len);
							head->b[7]=ch-'0';
							for(int i=0;i<7;i++)
							{
								ch=x[s+1];
								head->b[6-i]=ch-'0';
								s++;
							}
							p1=head;
							p2=head;
						}
						else
						{
							p1=(ele*)malloc(CA_len);
							p1->b[7]=ch-'0';
							for(int i=0;i<7;i++)
							{
								ch=x[s+1];
								p1->b[6-i]=ch-'0';
								s++;
							}
							p2->next=p1;
							p2=p1;
						}
						s++;
					}
					p1=head;
					p2->next=NULL;
					int caxx=Ca.ca_sjiemi(head,s/8,Length,Random,ca_key,Rule);
					results1=new char[caxx];
					int c=0;
					while(p1->next!=NULL)
					{
						results1[c]=p1->a;
						c++;
							
						p1=p1->next;
					}
					
							results1[c]=p1->a;
							c++;
						
					
				//	CString n;
			//		n.Format("%d",c);
//					MessageBox(n);
				//	AfxMessageBox(results1);
					result.Format("%s",results1);
					result=result.Left(c);
						}

						break;
					}
				case 1019://radio 10 permutation
					{
						if(n)
						{
						}
						else
						{
						}

						break;
					}
				case 1027://11	autokey plaintext
					{
						Autokey_plaintext autokey;
						string Autokey_plain_key = m_KEY.GetBuffer(0);
						m_KEY.ReleaseBuffer();

						if(n)
						{
							autokey.ciphertext = autokey.keyboard_encrypt(text.GetBuffer(0) , Autokey_plain_key);
							text.ReleaseBuffer();
							result = autokey.ciphertext.c_str();
						}
						else
						{
							autokey.plaintext = autokey.keyboard_decrypt(text.GetBuffer(0) , Autokey_plain_key);
							text.ReleaseBuffer();
							result = autokey.plaintext.c_str();
						}

						break;
					}
				case 1028://12	autokey ciphertext
					{
						Autokey_ciphertext autokey;
						string Autokey_cipher_key = m_KEY.GetBuffer(0);
						m_KEY.ReleaseBuffer();

						if(n)
						{
							autokey.ciphertext = autokey.keyboard_encrypt(text.GetBuffer(0) , Autokey_cipher_key);
							text.ReleaseBuffer();
							result = autokey.ciphertext.c_str();
						}
						else
						{
							autokey.plaintext = autokey.keyboard_decrypt(text.GetBuffer(0) , Autokey_cipher_key);
							text.ReleaseBuffer();
							result = autokey.plaintext.c_str();
						}

						break;
					}
				}
	//--------------------------------------------------------------------------------------------------------
				num++;
				msge.Format("%.4d",num);
				aDlg->m_list.InsertItem(num,msge);
				time (&timep);
				t=asctime(gmtime(&timep));
				aDlg->m_list.SetItemText(num,TIME,t);
				if(n)
				{
					aDlg->m_list.SetItemText(num,MESSAGE,"向客户端发送密文字符");
				}
				else
				{
					aDlg->m_list.SetItemText(num,MESSAGE,"向客户端发送明文字符");
				}
				//返回加解密信息

				strcpy(DataBuffer,result);
				serverSocket.Send(DataBuffer,BUFFER_SIZE);//向客户端返回信息

				serverSocket.Close();//连接关闭
				num++;
				msge.Format("%.4d",num);
				aDlg->m_list.InsertItem(num,msge);
				time (&timep);
				t=asctime(gmtime(&timep));
				aDlg->m_list.SetItemText(num,TIME,t);
				aDlg->m_list.SetItemText(num,MESSAGE,"连接关闭");
				break;
			case 2://右页文件
				
					strcpy(file_name,"RECEIVE_FROM_CLIENT.txt");
					fp=fopen(file_name,"wb"); //filename是文件路径
					if(fp==NULL)
					{
						num++;
						msge.Format("%.4d",num);
						aDlg->m_list.InsertItem(num,msge);
						time (&timep);
						t=asctime(gmtime(&timep));
						aDlg->m_list.SetItemText(num,TIME,t);
						aDlg->m_list.SetItemText(num,MESSAGE,"打开文件"+aDlg->C_file_name+"失败");
						exit(1);
					}
					else
					{
						num++;
						msge.Format("%.4d",num);
						aDlg->m_list.InsertItem(num,msge);
						time (&timep);
						t=asctime(gmtime(&timep));
						aDlg->m_list.SetItemText(num,TIME,t);
						aDlg->m_list.SetItemText(num,MESSAGE,"创建文件");
					}
					memset(DataBuffer,0,BUFFER_SIZE);
					int length = 1;
					/////////////////////////////////////////////
					while(length)
					{//3
						length=serverSocket.Receive(DataBuffer,BUFFER_SIZE);
						if(length==0)
						{
							AfxMessageBox("0");
						}
						if(length < 0)
						{
							num++;
							msge.Format("%.4d",num);
							aDlg->m_list.InsertItem(num,msge);
							time (&timep);
							t=asctime(gmtime(&timep));
							aDlg->m_list.SetItemText(num,TIME,t);
							aDlg->m_list.SetItemText(num,MESSAGE,"接收数据失败");
							break;
						}
						int write_length=fwrite(DataBuffer,sizeof(char),length,fp);
							CString file_length;
							file_length.Format("%d",write_length);
							num++;
							msge.Format("%.4d",num);
							aDlg->m_list.InsertItem(num,msge);
							time (&timep);
							t=asctime(gmtime(&timep));
							aDlg->m_list.SetItemText(num,TIME,t);
							aDlg->m_list.SetItemText(num,MESSAGE,"接收数据"+write_length);
						if (write_length<length)
						{
							num++;
							msge.Format("%.4d",num);
							aDlg->m_list.InsertItem(num,msge);
							time (&timep);
							t=asctime(gmtime(&timep));
							aDlg->m_list.SetItemText(num,TIME,t);
							aDlg->m_list.SetItemText(num,MESSAGE,"文件写入失败");
							exit(1);
						}
						memset(DataBuffer,0,BUFFER_SIZE);
					}//3

					num++;
					msge.Format("%.4d",num);
					aDlg->m_list.InsertItem(num,msge);
					time (&timep);
					t=asctime(gmtime(&timep));
					aDlg->m_list.SetItemText(num,TIME,t);
					aDlg->m_list.SetItemText(num,MESSAGE,"文件传输完成");
					fclose(fp);//关闭文件


					switch(r_ID)//加密算法
					{
					case 1009:
						{
							CAESAR Caesar;
							int CAESAR_key = atoi(m_KEY);
							if(n)
							{
								Caesar.FILE_INCODE(file_name , CAESAR_key);
							}
							else
							{
								Caesar.FILE_DECODE(file_name , CAESAR_key);
							}

							break;
						}
					case 1010://radio 2
						{
							KEYWORD KeyWord;
							KeyWord.KeyTable_INIT((LPSTR)(LPCTSTR)m_KEY.GetBuffer(0));
							m_KEY.ReleaseBuffer();

							if(n)
							{
								KeyWord.FILE_INCODE(file_name);
							}
							else
							{
								KeyWord.FILE_DECODE(file_name);
							}

							break;
						}
					case 1011://radio 3
						{
							VIGENERE Vigenere;
							Vigenere.key = m_KEY.GetBuffer(0);
							m_KEY.ReleaseBuffer();

							if(n)
							{
								Vigenere.FILE_INCODE(file_name);
							}
							else
							{
								Vigenere.FILE_DECODE(file_name);
							}

							break;
						}
					case 1012://radio 4
						{
							COLUMN_PERMUTATION COL_PER;
							COL_PER.key = m_KEY.GetBuffer(0);
							m_KEY.ReleaseBuffer();

							if(n)
							{
								COL_PER.FILE_INCODE(file_name);
							}
							else
							{
								COL_PER.FILE_DECODE(file_name);
							}

							break;
						}
					case 1013://radio 5
						{
							RC_FOUR rc4;
							rc4.key = m_KEY.GetBuffer(0);
							m_KEY.ReleaseBuffer();

							if(n)
							{
								rc4.FILE_INCODE(file_name);
							}
							else
							{
								rc4.FILE_DECODE(file_name);
							}

							break;
						}
					case 1015://radio 6
						{
							DES Cdes;
							Cdes.key = m_KEY.GetBuffer(0);
							m_KEY.ReleaseBuffer();
							if(n)
							{
								Cdes.FileIncode(file_name);
							}
							else
							{
								Cdes.FileDecode(file_name);
							}

							break;
						}
					case 1016://radio 7
						{
							Playfair playfair;
							string playfair_key = m_KEY.GetBuffer(0);
							m_KEY.ReleaseBuffer();

							if(n)
							{
								playfair.file_plain(file_name , playfair_key);
							}
							else
							{
								playfair.file_cipher(file_name , playfair_key);
							}

							break;
						}
					case 1017://radio 8
						{
							int i;
							char  c;
							int  p[100],q[100],nn[100],d[100],e[100],m[100],p1[100],q1[100];
							struct rsan *head,*h1,*h2,*h3,*h4;
							for(i=0;i<100;i++)
								m[i]=p[i]=q[i]=nn[i]=d[i]=e[i]=0;
							for(i=0;i<100;i++)
								m[i]=p[i]=q[i]=nn[i]=d[i]=e[i]=0;
							RSA ob;
							if(n)
							{
								char*filename="d:\\mima\\mima4.txt";//文件密钥开始
								ob.loadpkey(e,nn,filename);
							//	filename="d:\\mima\\mima5.txt";
							//	ob.loadskey(d,nn,filename); //文件密钥结束
							filename="RECEIVE_FROM_CLIENT.txt";
								ob.tencrypto( e,nn,filename );
							}
							else
							{
							//	char*filename="d:\\mima\\mima4.txt";//文件密钥开始
							//ob.loadpkey(e,nn,filename);
							char *filename="d:\\mima\\mima5.txt";
							ob.loadskey(d,nn,filename); //文件密钥结束
					         filename="RECEIVE_FROM_CLIENT.txt";
								ob.tdecrypto( d, nn,filename );
							}

							break;
						}
					case 1018://radio 9
						{
							CA Ca;
							if(n)
							{
							/*	int Length=atoi(length);
								int Random=atoi(random);
								int Rule=atoi(rule);
								char* ca_key=CA_key.GetBuffer(CA_key.GetLength());*/
							//	char* x=text.GetBuffer(text.GetLength());
							//	char *filename=text.GetBuffer(text.GetLength());
								char *savefile="EventHandle.txt";
								char *filename="RECEIVE_FROM_CLIENT.txt";
								Ca.ca_jiami(filename ,savefile,Length,Random,ca_key,Rule);
							}
							else
							{
								/*int Length=atoi(length);
								int Random=atoi(random);
								int Rule=atoi(rule);
								char* ca_key=CA_key.GetBuffer(CA_key.GetLength());*/
							//	char* x=text.GetBuffer(text.GetLength());
								char *filename="RECEIVE_FROM_CLIENT.txt";
								char *savefile="EventHandle.txt";
								Ca.ca_jiemi(filename,savefile,Length,Random,ca_key,Rule);
							}

							break;
						}
					case 1019://radio 10
						{
							if(n)
							{
							}
							else
							{
							}

							break;
						}
					case 1027://11
						{
							Autokey_plaintext autokey;
							string Autokey_plain_key = m_KEY.GetBuffer(0);
							m_KEY.ReleaseBuffer();

							if(n)
							{
								autokey.file_encrypt(file_name , Autokey_plain_key);
							}
							else
							{
								autokey.file_decrypt(file_name , Autokey_plain_key);
							}

							break;
						}
					case 1028://12
						{
							Autokey_ciphertext autokey;
							string Autokey_cipher_key = m_KEY.GetBuffer(0);
							m_KEY.ReleaseBuffer();

							if(n)
							{
								autokey.file_encrypt(file_name , Autokey_cipher_key);
							}
							else
							{
								autokey.file_decrypt(file_name , Autokey_cipher_key);
							}

							break;
						}
					}





					strcpy(file_name,"EventHandle.txt");//结果
					//返回加解密信息
					/*if(n)
					{
						strcpy(file_name,"EventHandle.txt");//返回文件名
					}
					else
					{
						strcpy(file_name,"EventHandle.txt");//返回文件名
					}*/

					//////////////////////
	
					FILE *file;
					file=fopen(file_name,"rb");
					int i = GetLastError();
					int buffi = 0;
					//fseek(file, 0, SEEK_SET);
					i = GetLastError();
					if(file==NULL)
					{
						AfxMessageBox("File Not Found");
					}
					else
					{
						char buffer[BUFFER_SIZE];
						memset(buffer,0,BUFFER_SIZE);
						//int file_block_length = 0;
						while(	!feof(file) )
						{
							buffer[buffi++] = getc(file);
							if(buffi >= BUFFER_SIZE)
							{
								serverSocket.Send(buffer,BUFFER_SIZE);
								buffi = 0;
							}
						}
						if(buffi > 0)
							serverSocket.Send(buffer,buffi);
						serverSocket.Close();
						
						fclose(file);
					}
				}//2
				break;
			}//1/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			return 1;
			}//while
			serverSocket.Close();
			aSocket.Close();
			return 1;
}
