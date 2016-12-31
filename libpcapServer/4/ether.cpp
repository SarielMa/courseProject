#include<pcap.h>
#include<time.h>
#include <netinet/in.h>
struct ether_header    //以太网协议的数据结构
{
  u_int8_t ether_dhost[6];      //目的以太网地址
  u_int8_t ether_shost[6];      //源以太网地址
  u_int16_t ether_type;         //以太网类型
};
int main()
{
  char error_content[PCAP_ERRBUF_SIZE];  //错误信息
  pcap_t* pcap_handle;        //libpcap句柄
  const u_char *packet_content;    //数据包缓存
  u_char *mac_string;       //以太网地址
  int ethernet_type;    //以太网类型
  bpf_u_int32 net_mask;      //网络掩码
  bpf_u_int32 net_ip;       //网络地址
  char *net_interface;      //网络接口
  struct pcap_pkthdr protocol_header;   //数据包信息
  struct bpf_program bpf_filter;       //BPF过滤规则
  struct ether_header *ethernet_protocol;    //以太网协议变量
  char bpf_filter_string[]= "ip";      //过滤规则
  net_interface=pcap_lookupdev(error_content);  //获得网络接口
  pcap_lookupnet(net_interface,//网络接口
	            &net_ip,&net_mask,error_content);
  //获得网络地址和掩码地址
  pcap_handle=pcap_open_live(net_interface,BUFSIZ,1,0,error_content);
  //打开网络接口
  pcap_compile(pcap_handle,&bpf_filter,bpf_filter_string,0,net_ip);
  pcap_setfilter(pcap_handle,&bpf_filter);
 //设置过滤规则
  if(pcap_datalink(pcap_handle)!=DLT_EN10MB)
     return 1;
  packet_content=pcap_next(pcap_handle,&protocol_header);
  printf("Capture a Packet from net_interface :\n");
  printf("%s\n",net_interface);
  printf("Capture Time is: \n");
  printf("%s",ctime((const time_t *)&protocol_header.ts.tv_sec));
  printf("Packet Length is :\n");
  printf("%d\n",protocol_header.len);
  ethernet_protocol=(struct ether_header *)packet_content;
  //对此数据包缓存进行类型的强制转换，使它变成以太网格式的数据类型
  printf("Ethernet type is : \n");
  ethernet_type=ntohs(ethernet_protocol->ether_type);//获得以太网的类型，它表示上层网络层协议的类型，
  printf("%04x\n",ethernet_type);
  switch(ethernet_type)
 {
    case 0x0800: printf("the network layer is IP protocol\n");break;
    case 0x0806: printf("the network layer is ARP protocol\n");break;
    case 0x8035: printf("the network layer is RARP protocol\n");break;
    default: break;
 }
 printf("Mac Source Address is : \n");
 mac_string=ethernet_protocol->ether_shost;   //获得源以太网地址
 printf("%02x:%02x:%02x:%02x:%02x:%02x\n",*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
 printf("Mac Desination Address is : \n");
 mac_string=ethernet_protocol->ether_dhost;
 printf("%02x:%02x:%02x:%02x:%02x:%02x\n",*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
 pcap_close(pcap_handle);
return 0;
}

