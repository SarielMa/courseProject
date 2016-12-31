#include "pcap.h"
#include "memory.h"
#include <arpa/inet.h>
struct ether_header    //以太网协议格式
{
   u_int8_t ether_dhost[6];    //目的以太网地址
   u_int8_t ether_shost[6];    //源以太网地址
   u_int16_t ether_type;       //以太网类型
};
//IP地址格式ntohs
typedef u_int32_t int_addr_t;
/*struct in_addr
{
  int_addr_t s_addr;            //存放ip地址
};*/
//ARP协议格式
struct arp_header
{
  u_int16_t arp_hardware_type;      //硬件地址类型
  u_int16_t arp_protocol_type;     //协议地址类型
  u_int8_t arp_hardware_length;     //硬件地址长度
  u_int8_t arp_protocol_length;     //协议地址长度
  u_int16_t arp_operation_code;     //操作类型
  u_int8_t arp_source_ethernet_address[6];   //源以太网地址
  u_int8_t arp_source_ip_address[4];       //源ip地址
  u_int8_t arp_destination_ethernet_address[6];      //目的以太网地址
  u_int8_t arp_destination_ip_address[4];       //目的IP地址
};
//实现ARP协议分析的函数定义
void arp_protocol_packet_callback(u_char *argument,const struct pcap_pkthdr* packet_header,const u_char* packet_content)
{
  struct arp_header *arp_protocol;    //ARP协议变量
  u_short protocol_type;              //协议类型
  u_short hardware_type;              //硬件类型
  u_short operation_code;             //操作类型
  u_char *mac_string;                 //以太网地址
  struct in_addr source_ip_address;    //源IP地址
  struct in_addr destination_ip_address;    //目的IP地址
  u_char hardware_length;             //硬件地址长度
  u_char protocol_length;             //协议地址长度
  printf("ARP(网络层)\n");
  arp_protocol=(struct arp_header *)(packet_content+14);//要跳过以太网的数据部分，注意类型转换
  hardware_type=ntohs(arp_protocol->arp_hardware_type);     //获得硬件类型
  protocol_type=ntohs(arp_protocol->arp_protocol_type);      //获得协议类型
  operation_code=ntohs(arp_protocol->arp_operation_code);    //获得操作码
  hardware_length=arp_protocol->arp_hardware_length;       //获得硬件地址长度
  protocol_length=arp_protocol->arp_protocol_length; //获得协议地址长度

  printf("ARP 硬件类型 :%d\n",hardware_type);
  printf("ARP协议类型 :%d\n",protocol_type);
  printf("ARP 硬件地址长度: %d\n",hardware_length);
  printf("ARP 协议地址长度 :%d\n ",protocol_length);
  printf("ARP 操作码: %d\n",operation_code);
  switch(operation_code)
  {
     case 1:printf("ARP查询协议\n");break;     //ARP查询协议
     case 2:printf("ARP应答协议\n");break;      //ARP应答协议
     case 3:printf("RARP查询协议\n");break;    //RARP查询协议
     case 4:printf("RARP应答协议\n");break;      //RARP应答协议
	 default: break;
  }
  printf("以太网源地址 :\n");
  mac_string=arp_protocol->arp_source_ethernet_address;
  printf("%02x:%02x:%02x:%02x:%02x:%02x\n",*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));//获得源以太网地址
  memcpy((void *) &source_ip_address,(void *) &arp_protocol->arp_source_ip_address,sizeof(struct in_addr));
  printf("源IP地址:%s\n",inet_ntoa(source_ip_address));
   printf("以太网目的地址:\n");
      mac_string=arp_protocol->arp_destination_ethernet_address;
  printf("%02x:%02x:%02x:%02x:%02x:%02x\n",*mac_string,*(mac_string+1),*  (mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
  
memcpy((void *)&destination_ip_address,(void *) &arp_protocol->arp_destination_ip_address,sizeof(struct in_addr));
  printf("目的IP地址:%s\n",inet_ntoa(destination_ip_address));
}
void ethernet_protocol_packet_callback(u_char *argument,const struct pcap_pkthdr *packet_header,const u_char* packet_content)
{
   u_short ethernet_type;      //以太网类型
    struct ether_header *ethernet_protocol;      //以太网协议变量
   u_char *mac_string;      //以太网地址
   static int packet_number=1;
    printf("第 %d ARP包被捕获.\n",packet_number);
   printf("以太网(数据链路层)");
   ethernet_protocol=(struct ether_header *)packet_content;
   //获得以太网协议数据
   printf("以太网类型 :\n");
     ethernet_type=ntohs(ethernet_protocol->ether_type);  //获得以太网类型
    printf("%04x\n",ethernet_type); 
   switch(ethernet_type)      //根据以太网类型判断上层协议类型
{
   case 0x0800: printf("上层协议是 ip\n");break;
   case 0x0806: printf("上层协议是 ARP\n");break;
   case 0x8035: printf("上层协议是RARP\n");break;
   default: break;
}
printf("Mac源地址 :\n");
mac_string=ethernet_protocol->ether_shost;
printf("%02x:%02x:%02x:%02x:%02x:%02x\n",*mac_string,*(mac_string+1),*  (mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
//获得源以太网地址
printf("Mac 目的地址:\n");
mac_string=ethernet_protocol->ether_dhost;
printf("%02x:%02x:%02x:%02x:%02x:%02x\n",*mac_string,*(mac_string+1),*  (mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
//获得目的以太网地址
switch(ethernet_type)
{
  case 0x0806: 
//cout<<"this protocal is arp"<<endl;
arp_protocol_packet_callback(argument,packet_header,packet_content);break;
    default: break;
}
packet_number++;
}
int main()
{
  pcap_t* pcap_handle;                //Libpcap句柄
   char error_content[PCAP_ERRBUF_SIZE];     //错误信息
  char *net_interface;       //网络接口
  struct bpf_program bpf_filter;       //BPF过滤规则
  //char bpf_filter_string[]="arp";    //表示只捕获arp协议的网络数据包
  bpf_u_int32 net_mask;         //网络掩码
   bpf_u_int32 net_ip;          //网络地址
   net_interface=pcap_lookupdev(error_content);     //获得网络接口
   //获得网络地址和网络掩码
   pcap_lookupnet(net_interface,&net_ip,&net_mask,error_content);
   //打开网络接口
  pcap_handle=pcap_open_live(net_interface,BUFSIZ,1,0,error_content);
  //编辑过滤规则
   pcap_compile(pcap_handle,&bpf_filter,"arp",0,net_ip);
   //设置过滤规则
pcap_setfilter(pcap_handle,&bpf_filter);
if(pcap_datalink(pcap_handle)!=DLT_EN10MB)//返回链路层类型，10m以太网
   return 1;
//注册回调函数，循环捕获数据包
pcap_loop(pcap_handle,-1,ethernet_protocol_packet_callback,NULL);//永远调用
pcap_close(pcap_handle);
return 0;
}

