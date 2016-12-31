
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include "pcap.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include<mysql.h> 
#include<string> 
#include<iostream>
#include <process.h>


struct ether_header
{
	u_int8_t ether_dhost[6];
	u_int8_t ether_shost[6];
	u_int16_t ether_type;
};

struct ip_header
{
	#ifdef WORDS_BIGENDIAN
	u_int8_t ip_version:4;
	ip_header_length:4;
	#else
	u_int8_t ip_header_length:4;
	u_int8_t ip_version:4;
	#endif
	u_int8_t ip_tos;
	u_int16_t ip_length;
	u_int16_t ip_id;
	u_int16_t ip_off;
	u_int8_t ip_ttl;
	u_int8_t ip_protocol;
	u_int8_t ip_checksum;
	struct in_addr ip_source_address;
	struct in_addr ip_destination_address;
};


struct arp_header
{
	u_int16_t arp_hardware_type;
	u_int16_t arp_protocol_type;
	u_int8_t arp_hardware_length;
	u_int8_t arp_protocol_length;
	u_int16_t arp_operation_code;
	u_int8_t arp_source_ethernet_address[6];
	u_int8_t arp_source_ip_address[4];
	u_int8_t arp_destination_ethernet_address[6];
	u_int8_t arp_destination_ip_address[4];
};


struct tcp_header
{
	u_int16_t tcp_source_port;
	u_int16_t tcp_destination_port;
	u_int32_t tcp_acknowledgement;
	u_int32_t tcp_ack;
	#ifdef WORDS_BIGENDIAN
	u_int8_t tcp_offset:4,
				tcp_reserved:4;
	#else
	u_int8_t tcp_reserved:4,
					tcp_offset:4;
	#endif
	u_int8_t tcp_flags;
	u_int16_t tcp_windows;
	u_int16_t tcp_checksum;
	u_int16_t tcp_urgent_pinter;

};

struct udp_header{
	u_int16_t udp_source_port;//Դ�˿�
	u_int16_t udp_destination_port;//Ŀ�Ķ˿�
	u_int16_t udp_length;//����
	u_int16_t udp_checksum;//У���
};


struct mysqlData
{
	int count;
	char networkLayer[5];
	char transportLayer[5];
	char appLayer[6];
	char source_mac[20] ;
	char dest_mac[20];
	char source_ip[18];
	char dest_ip[18];
	int source_port;
	int dest_port;
};


int connectToMySQL(struct mysqlData*,int,const char*);

void ip_protocol_packet_callback(FILE *argument,const struct pcap_pkthdr* packet_header, const u_char* packet_content,struct mysqlData*);
void arp_protocol_packet_callback(FILE *argument,const struct pcap_pkthdr* packet_header, const u_char* packet_content,struct mysqlData*);
void tcp_protocol_packet_callback(FILE *argument,const struct pcap_pkthdr* packet_header, const u_char* packet_content,struct mysqlData*);
void udp_protocol_packet_callback(FILE *file,const struct pcap_pkthdr* packet_header,const u_char* packet_content,struct mysqlData*);
void packet_handler(u_char *param, const struct pcap_pkthdr *header,const u_char *pkt_data);

DWORD ThreadProc (LPVOID lpdwThreadParam );
//int winpcpCatch();

#define RUNNING 1
#define FIN 0

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
