
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持









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
	u_int16_t udp_source_port;//源端口
	u_int16_t udp_destination_port;//目的端口
	u_int16_t udp_length;//长度
	u_int16_t udp_checksum;//校验和
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

// TODO: 在此处引用程序需要的其他头文件
