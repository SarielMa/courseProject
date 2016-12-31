
// WinpcapMFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WinpcapMFC.h"
#include "WinpcapMFCDlg.h"
#include "afxdialogex.h"
#include "Result.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWinpcapMFCDlg 对话框

CWinpcapMFCDlg * CWinpcapMFCDlg::instance = NULL;


CWinpcapMFCDlg::CWinpcapMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWinpcapMFCDlg::IDD, pParent)
	, checkIP(FALSE)
	, checkICMP(FALSE)
	, checkARP(FALSE)
	, checkTCP(FALSE)
	, checkUDP(FALSE)
	, checkHTTP(FALSE)
	, checkSMTP(FALSE)
	, checkFTP(FALSE)
	, checkDHCP(FALSE)
	, packageNum(0)
	, databaseName(_T(""))
	, filePath(_T(""))
	//, outputPackage(_T(""))
	, ethName(_T(""))
	, saveToDB(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	instance = this;
}

void CWinpcapMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CK_IP, checkIP);
	DDX_Check(pDX, IDC_CK_ICMP, checkICMP);
	DDX_Check(pDX, IDC_CK_ARP, checkARP);
	DDX_Check(pDX, IDC_CK_TCP, checkTCP);
	DDX_Check(pDX, IDC_CK_UDP, checkUDP);
	DDX_Check(pDX, IDC_CK_HTTP, checkHTTP);
	DDX_Check(pDX, IDC_CK_SMTP, checkSMTP);
	DDX_Check(pDX, IDC_CK_FTP, checkFTP);
	DDX_Check(pDX, IDC_CK_DHCP, checkDHCP);
	DDX_Text(pDX, IDC_EDIT_PACKNUM, packageNum);
	DDV_MinMaxInt(pDX, packageNum, 1, 10000);
	DDX_Text(pDX, IDC_EDIT_DB, databaseName);
	DDX_Text(pDX, IDC_EDIT_FILEPATH, filePath);
	//DDX_LBString(pDX, IDC_LIST_OUTPUT, outputPackage);
	DDX_Control(pDX, IDC_COMBO_ETH, comboBoxEth);
	DDX_CBString(pDX, IDC_COMBO_ETH, ethName);
	DDX_Check(pDX, IDC_CK_TODB, saveToDB);
	DDX_Control(pDX, IDC_PRO_BAR, proBar);
	//DDX_Control(pDX, IDC_LIST_OUTPUT, outputList);

	DDX_Control(pDX, IDC_EDIT_DB, DBEditBox);
	DDX_Control(pDX, IDC_LIST_CONTROL, resultListControl);
}

BEGIN_MESSAGE_MAP(CWinpcapMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_FILE, &CWinpcapMFCDlg::OnBnClickedBtnFile)
	ON_BN_CLICKED(IDOK, &CWinpcapMFCDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_ETH, &CWinpcapMFCDlg::OnCbnSelchangeComboEth)
	ON_CBN_SETFOCUS(IDC_COMBO_ETH, &CWinpcapMFCDlg::OnCbnSetfocusComboEth)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CWinpcapMFCDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_RESULT, &CWinpcapMFCDlg::OnBnClickedBtnResult)
	ON_BN_CLICKED(IDC_CK_TODB, &CWinpcapMFCDlg::OnBnClickedCkTodb)
	ON_EN_CHANGE(IDC_EDIT_PACKNUM, &CWinpcapMFCDlg::OnEnChangeEditPacknum)
END_MESSAGE_MAP()


// CWinpcapMFCDlg 消息处理程序

BOOL CWinpcapMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
		
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	CString str=CString("to init the eth click here..");
	comboBoxEth.AddString(str);
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWinpcapMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWinpcapMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWinpcapMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWinpcapMFCDlg::OnBnClickedBtnFile()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CFileDialog dlg(TRUE, _T("txt file (*.txt)"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,
    _T("文件类型(*.txt)|*.txt||"), this);
	if(IDOK==dlg.DoModal())
	{
		CString path=dlg.GetPathName();
		filePath=path;
		UpdateData(false);
	}
	else
	{

	}
}

DWORD CWinpcapMFCDlg::ThreadProc (LPVOID lpdwThreadParam )
{
		if(instance!=NULL)
			instance->winpcpCatch();
		return 0;
}

DWORD CWinpcapMFCDlg::ThreadProcInsert (LPVOID lpdwThreadParam )
{
		if(instance!=NULL)
			instance->insertForm();
		return 0;
}

int status=FIN;
int statusShow=FIN;
int proNum=0;
int count=0;
FILE *file;
struct mysqlData * sqlData;
struct mysqlData * sqlDataCopy;


void CWinpcapMFCDlg::OnBnClickedOk()
{
	if(status==FIN&&statusShow==FIN)//判断状态
	{
		UpdateData(true);
		resultListControl.DeleteAllItems();
		if(ethName=="")
		{
			MessageBox(_T("请选择所需网卡"));
			return;
		}
		if(filePath=="")
		{
			MessageBox(_T("请选择输出文件"));
			return;
		}

		if(saveToDB==true)
		{
			if(databaseName=="")
			{
				MessageBox(_T("请选择输出数据库表名"));
				return;
			}
		}

		proBar.SetRange(0,packageNum);
		proBar.SetPos(0);
		SetCtrlStyle(resultListControl.m_hWnd,LVS_REPORT);
		resultListControl.InsertColumn(0,_T("输出内容"),LVCFMT_LEFT,1800);
		UpdateData(false);
		count=0;
		proNum=0;
		DWORD dwThreadId;
		DWORD dwThreadIdShow;
		int i, nThreads = 5;
		int j, tThreads=100;
		HANDLE hThrd = NULL;
		HANDLE thThrd = NULL;
		//开启两个线程
		//第一个为同步抓包线程
		//第二个为同步抓包显示线程
		if((hThrd=(HANDLE)CreateThread(NULL,0,	(LPTHREAD_START_ROUTINE)&ThreadProc,
									(LPVOID) &i,0,&dwThreadId) )!= NULL)
		{
			status=RUNNING;
		}
		if((thThrd=(HANDLE)CreateThread(NULL,0,	(LPTHREAD_START_ROUTINE)&ThreadProcInsert,
									(LPVOID) &j,0,&dwThreadIdShow) )!= NULL)
		{
			statusShow=RUNNING;
		}
		SetTimer(1,100,NULL);

	}
	else
	{
		MessageBox(_T("已有线程在运行请等待其结束。"));
	}

	

}




pcap_t *adhandle;

const char* CStrToChar(CString strSrc)
{
    #ifdef UNICODE
        DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, strSrc.GetBuffer(0), -1, NULL, 0, NULL, FALSE);
        char *psText;
        psText = new char[dwNum];
        if (!psText)
            delete []psText;
        WideCharToMultiByte(CP_OEMCP, NULL, strSrc.GetBuffer(0), -1, psText, dwNum, NULL, FALSE);
        return (const char*)psText;
    #else
        return (LPCTSRT)strSrc;
    #endif
}



int CWinpcapMFCDlg::winpcpCatch()
{ 
    pcap_if_t *alldevs; 
    pcap_if_t *d; 
    int inum; 
    int i=0;	
	int catchNum=packageNum;

    char errbuf[PCAP_ERRBUF_SIZE]; 


	sqlData=(struct mysqlData*)calloc(catchNum+1,sizeof(struct mysqlData));
	sqlDataCopy=sqlData;
	char bpf_filter_string[50]="";
	if(checkIP&&checkARP&&checkICMP&&checkTCP&&checkUDP&&checkHTTP&&checkSMTP&&checkFTP &&checkDHCP)
	{
			;
	}
	else
	{
		if(checkIP)
		{
			sprintf(bpf_filter_string,"ip ");
		}
		if(checkARP)
		{
			if(strcmp( bpf_filter_string,"")==0)
				sprintf(bpf_filter_string,"arp ");
			else
				sprintf(bpf_filter_string,"%sor arp",bpf_filter_string);
		}
		if(checkICMP)
		{
			if(strcmp( bpf_filter_string,"")==0)
				sprintf(bpf_filter_string,"icmp ");
			else
				sprintf(bpf_filter_string,"%sor icmp",bpf_filter_string);
		}
		if(checkTCP)
		{
			if(strcmp( bpf_filter_string,"")==0)
				sprintf(bpf_filter_string,"tcp ");
			else
				sprintf(bpf_filter_string,"%sor tcp",bpf_filter_string);
		}
		if(checkUDP)
		{
			if(strcmp( bpf_filter_string,"")==0)
				sprintf(bpf_filter_string,"udp ");
			else
				sprintf(bpf_filter_string,"%sor udp",bpf_filter_string);
		}
		if(checkHTTP)
		{
			if(strcmp( bpf_filter_string,"")==0)
				sprintf(bpf_filter_string,"port 80 ");
			else
				sprintf(bpf_filter_string,"%sor port 80 ",bpf_filter_string);
		}
		if(checkSMTP)
		{
			if(strcmp( bpf_filter_string,"")==0)
				sprintf(bpf_filter_string,"port 25 ");
			else
				sprintf(bpf_filter_string,"%sor port 25",bpf_filter_string);
		}
		if(checkFTP)
		{
			if(strcmp( bpf_filter_string,"")==0)
				sprintf(bpf_filter_string,"port 21 ");
			else
				sprintf(bpf_filter_string,"%sor port 21 ",bpf_filter_string);
		}
		if(checkDHCP)
		{
			if(strcmp( bpf_filter_string,"")==0)
				sprintf(bpf_filter_string,"port 17 port 18");
			else
				sprintf(bpf_filter_string,"%sor port 17 port 18",bpf_filter_string);
		}
	}

	

	inum= comboBoxEth.GetCurSel();


	if(pcap_findalldevs(&alldevs, errbuf) == -1) 
	{ 
		return -1;
    }
	for(d=alldevs, i=0; i< inum;d=d->next, i++);

	/* 打开网卡 */ 

	if( (adhandle= pcap_open_live(d->name, //设备名 
            65535, // 捕捉完整的数据包 
            1, // 混在模式 
            1000, // 读入超时 
            errbuf // 错误缓冲 
            ) ) == NULL) 
	{	 
		return -1;
	}
	struct bpf_program bpf_filter;
	u_int32_t netmask = 0xffffffff;
	pcap_compile(adhandle,
			&bpf_filter,
			bpf_filter_string,
			0,
			netmask
		);
	pcap_setfilter(adhandle,	&bpf_filter);	


	/* 我们已经不需要网卡列表了, 释放它 */ 
	pcap_freealldevs(alldevs);
	/* 开始捕获数据包 */
	
	CString path=filePath;

	file=fopen(CStrToChar(path),"w");

	pcap_loop(adhandle, catchNum, packet_handler, NULL); 


	pcap_close(adhandle);
	fclose(file);

	if(saveToDB==true)
	{
		sqlDataCopy=sqlData;
		CString dbName=databaseName;
		connectToMySQL(sqlDataCopy,catchNum,CStrToChar(dbName));
	}


	//CStdioFile   file; 
	//CString   strLine   =   filePath; 
	//if(file.Open(strLine,CFile::modeRead)) 
	//{ 

	//	while(file.ReadString(strLine)) 
	//	{  				
	//		resultListControl.InsertItem(resultListControl.GetItemCount(),strLine);
	//		if(strLine=="###################################")
	//		{
	//				proNum++;
	//		}
	//	} 
	//}

	status=FIN;
	return 0; 
} 

void packet_handler(u_char *param,  const struct pcap_pkthdr *header, const u_char *pkt_data)
{ 

	sprintf(sqlDataCopy->appLayer,"");
	sprintf((sqlDataCopy->networkLayer),"");
	sprintf((sqlDataCopy->transportLayer),"");

	
	if(file==NULL)
	{
		exit(-1);
	}
	fprintf(file,"No.%d \n",++count);
	sqlDataCopy->count=count;

	u_short ethernet_type;
	struct ether_header* ethernet_protocol;
	u_char *mac_string;

	ethernet_protocol=(struct ether_header *)pkt_data;

	fprintf(file,"Ethernet type is: ");
	ethernet_type=ntohs(ethernet_protocol->ether_type);

	fprintf(file,"%04x\n",ethernet_type);

	printf("Mac Source address is: ");
	fprintf(file,"Mac Source address is: ");

	mac_string=ethernet_protocol->ether_shost;
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
		*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),
		*(mac_string+4),*(mac_string+5));
	fprintf(file,"%02x:%02x:%02x:%02x:%02x:%02x\n",
		*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),
		*(mac_string+4),*(mac_string+5));
	sprintf(sqlDataCopy->source_mac,"%02x:%02x:%02x:%02x:%02x:%02x\n",
		*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),
		*(mac_string+4),*(mac_string+5));

	printf("Mac Dest address is: ");
	fprintf(file,"Mac Dest address is: ");
	mac_string=ethernet_protocol->ether_dhost;
	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
		*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),
		*(mac_string+4),*(mac_string+5));
	fprintf(file,"%02x:%02x:%02x:%02x:%02x:%02x\n",
		*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),
		*(mac_string+4),*(mac_string+5));
	sprintf(sqlDataCopy->dest_mac,"%02x:%02x:%02x:%02x:%02x:%02x\n",
		*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),
		*(mac_string+4),*(mac_string+5));

	switch(ethernet_type)
	{
		case 0x0800:
			printf("The network layer is IP protocol.\n");
			fprintf(file,"The network layer is IP protocol.\n");
			sprintf(sqlDataCopy->networkLayer,"IP");
			ip_protocol_packet_callback(file,header,pkt_data,sqlDataCopy);
			break;
		case 0x0806:
			printf("The network layer is ARP protocol.\n");
			fprintf(file,"The network layer is ARP protocol.\n");
			sprintf(sqlDataCopy->networkLayer,"ARP");
			arp_protocol_packet_callback(file,header,pkt_data,sqlDataCopy);
			break;
		default:
			printf("The network layer is Another protocol.\n");
			fprintf(file,"The network layer is Another protocol.\n");
			sprintf(sqlDataCopy->networkLayer,"");
			break;
	}
	sqlDataCopy++;
	fprintf(file,"\n###################################\n");
	proNum++;
}



void CWinpcapMFCDlg::OnCbnSelchangeComboEth()
{
	//UpdateData(false);

}


void CWinpcapMFCDlg::OnCbnSetfocusComboEth()
{
	// TODO: 在此添加控件通知处理程序代码
		char eth[100];
		comboBoxEth.ResetContent();

		pcap_if_t *alldevs; 
        pcap_if_t *d; 

        int i=0; 
		
        char errbuf[PCAP_ERRBUF_SIZE]; 

		/* 获取网卡列表 */ 
        if(pcap_findalldevs(&alldevs, errbuf) == -1) 
        { 
			sprintf(eth,"Error in pcap_findalldevs: %s\n", errbuf); 
			CString str((char*)eth); 
			comboBoxEth.AddString(str);
			UpdateData(false);
			return;
        } 

		
		/* 数据列表 */ 


		int count=0;
        for(d=alldevs; d; d=d->next) 
        {
				if(d->description) 
				{
					sprintf(eth," %s (%s)",  d->name ,d->description);
					//sprintf(eth,"%s",  d->name);
					CString str((char*)eth); 
					//comboBoxEth.AddString(str);
					comboBoxEth.InsertString(count,str);
				}
				else 
				{
					sprintf(eth,"%s(No description available)",d->name); 
					CString str((char*)eth); 
					comboBoxEth.AddString(str);
				}
				count++;
        } 
		UpdateData(false);
		/* 我们已经不需要网卡列表了, 释放它 */ 
		pcap_freealldevs(alldevs);
		
}


void CWinpcapMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	proBar.SetPos(proNum);

	if(status==FIN&&statusShow==FIN)
	{
		KillTimer(1);
		free(sqlData);
	}
	UpdateData(false);
}


void CWinpcapMFCDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();

}


void CWinpcapMFCDlg::OnBnClickedBtnResult()
{
	// TODO: 在此添加控件通知处理程序代码
	CResult dlg=new CResult(); 
	dlg.DoModal();
}


void CWinpcapMFCDlg::OnBnClickedCkTodb()
{
	// TODO: 在此添加控件通知处理程序代码
	if(saveToDB==true)
	{
		saveToDB=false;
		DBEditBox.EnableWindow(false);
	}
	else
	{
		saveToDB=true;
		DBEditBox.EnableWindow(true);
	}
	UpdateData(false);
}
void CWinpcapMFCDlg::SetCtrlStyle(HWND hWnd, DWORD dwNewStyle)
{
	DWORD dwOldStyle;
	dwOldStyle = GetWindowLong(hWnd, GWL_STYLE);
	if ((dwOldStyle&LVS_TYPEMASK) != dwNewStyle)
	{
		dwOldStyle &= ~LVS_TYPEMASK;
		dwNewStyle |= dwOldStyle;
		SetWindowLong(hWnd, GWL_STYLE, dwNewStyle);
	}
}

void CWinpcapMFCDlg::OnEnChangeEditPacknum()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
void CWinpcapMFCDlg::insertForm()
{
	//CStdioFile   file; 
	CString   strLine;
	char temp[1000];
	int showNum=0;
	struct mysqlData * sqlDataDisplay=sqlData;


	while(1) 
	{
		if(showNum<proNum)
		{
			sqlDataDisplay=sqlData;

			strLine.Format(_T("No. %d"),(sqlDataDisplay+showNum)->count);
			resultListControl.InsertItem(resultListControl.GetItemCount(),strLine);

			strLine.Format(_T("Ethernet type is:  %s"),CString((sqlDataDisplay+showNum)->networkLayer));
			resultListControl.InsertItem(resultListControl.GetItemCount(),strLine);

			strLine.Format(_T("Mac Source address is:  %s"),CString((sqlDataDisplay+showNum)->source_mac));
			resultListControl.InsertItem(resultListControl.GetItemCount(),strLine);

		
			strLine.Format(_T("Mac Dest address is:  %s"),CString((sqlDataDisplay+showNum)->dest_mac));
			resultListControl.InsertItem(resultListControl.GetItemCount(),strLine);
			showNum++;

			if(strcmp((sqlDataDisplay+showNum)->networkLayer,"")!=0)
			{
				strLine.Format(_T("The network layer is %s"),CString((sqlDataDisplay+showNum)->networkLayer));
				resultListControl.InsertItem(resultListControl.GetItemCount(),strLine);
				strLine.Format(_T("Source address: %s"),CString((sqlDataDisplay+showNum)->source_ip));
				resultListControl.InsertItem(resultListControl.GetItemCount(),strLine);
				strLine.Format(_T("Desination  address: %s"),CString((sqlDataDisplay+showNum)->dest_ip));
				resultListControl.InsertItem(resultListControl.GetItemCount(),strLine);
			}

			if(strcmp((sqlDataDisplay+showNum)->transportLayer,"")!=0)
			{
				strLine.Format(_T("The transport layer protocol is %s"),CString((sqlDataDisplay+showNum)->transportLayer));
				resultListControl.InsertItem(resultListControl.GetItemCount(),strLine);
				
				strLine.Format(_T("The source prot: %d"),(sqlDataDisplay+showNum)->source_port);
				resultListControl.InsertItem(resultListControl.GetItemCount(),strLine);

				strLine.Format(_T("The destination  prot: %d"),(sqlDataDisplay+showNum)->dest_port);
				resultListControl.InsertItem(resultListControl.GetItemCount(),strLine);
				if(strcmp((sqlDataDisplay+showNum)->appLayer,"")!=0)
				{
					strLine.Format(_T("It's %s package."),CString((sqlDataDisplay+showNum)->appLayer));
					resultListControl.InsertItem(resultListControl.GetItemCount(),strLine);
				}

			}

			strLine.Format(_T("###################################"));
			resultListControl.InsertItem(resultListControl.GetItemCount(),strLine);
		}
		else
		{
			Sleep(200);
			
		}
		if(showNum==packageNum)
		{
			statusShow=FIN;
			//free(sqlData);
			break;
		}
	} 
	
}