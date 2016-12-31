#include "pcap.h"
#include <netinet/in.h>
#include <arpa/inet.h>
/*以太网协议格式的定义*/
struct ether_header
{
        u_int8_t ether_dhost[6];        /*目的以太网地址*/
        u_int8_t ether_shost[6];        /*原以太网地址*/
        u_int16_t ether_type;           /*以太网类型*/
};

/*IP地址格式的定义*/
/*struct  in_addr
{
        u_int32_t  s_addr;
};*/

/*IP协议格式的定义*/
struct ip_header/*ip首部*/
{
       
                u_int8_t ip_header_length:4,  /*首部长度*/
                         ip_version:4;
    
        u_int8_t ip_tos_taowenliu;              /*服务质量*/
        u_int16_t ip_length;                    /*总长度*/
        u_int16_t ip_id;                        /*标识*/
        u_int16_t ip_off;                       /*埔移*/
        u_int8_t ip_ttl;                        /*生存时间*/
        u_int8_t ip_protocol;                   /*协议类型*/
        u_int16_t ip_checksum;                  /*校验和*/
        struct in_addr ip_source_address;       /*源IP地址*/
        struct in_addr ip_destination_address;  /*目的IP地址*/
};
/*TCP协议格式的定义*/
struct tcp_header
{
        u_int16_t tcp_source_port;              /*源端口*/
        u_int16_t tcp_destination_port;         /*目的端口*/
        u_int32_t tcp_acknowledgement;          /*序列号*/
        u_int32_t tcp_ack;                      /*确认号*/
    
            u_int8_t tcp_reserved:4,        /*保留*/
                         tcp_offset:4;          /*偏移*/
    
        u_int8_t tcp_flags;                     /*标志*/
        u_int16_t tcp_windows;                  /*窗口大小*/
        u_int16_t tcp_checksum;                 /*校验和*/
        u_int16_t tcp_urgent_pointer;           /*紧急指针*/
};


/*TCP协议的回调函数*/
void tcp_protocol_packet_callback(u_char *argument,const struct pcap_pkthdr * packet_header,const u_char * packet_content)
{
        struct tcp_header *tcp_protocol;
        u_char flags;                           /*标志*/
        int header_length;                      /*首部长度*/
        u_short source_port;                    /*源端口号*/
        u_short destination_port;               /*目的端口号*/
        u_short windows;                        /*窗口大小*/
        u_short urgent_pointer;                 /*紧急指针*/
        u_int sequence;                         /*序列号*/
        u_int acknowledgement;                  /*确认号*/
        u_int16_t checksum;                     /*校验和*/

        //获得TCP协议数据内容,应该跳过以太网头和IP头部分
        tcp_protocol = (struct tcp_header*)(packet_content+14+20);
        source_port = ntohs(tcp_protocol->tcp_source_port);
        destination_port = ntohs(tcp_protocol->tcp_destination_port);
        header_length = tcp_protocol->tcp_offset*4;
        sequence = ntohl(tcp_protocol->tcp_acknowledgement);
        acknowledgement = ntohl(tcp_protocol->tcp_ack);
        windows = ntohs(tcp_protocol->tcp_windows);
        urgent_pointer = ntohs(tcp_protocol->tcp_urgent_pointer);
        flags = tcp_protocol->tcp_flags;
        checksum = ntohs(tcp_protocol->tcp_checksum);

        printf("*********************TCP (传输层)*******************\n");
        printf("源端口号:%d\n",source_port);
        printf("目的端口号:%d\n",destination_port);
        switch(destination_port)        //判断上层应用层协议类型
        {
                case 80:printf("HTTP 协议\n");break;
                case 21:printf("FTP 协议\n");break;
                case 23:printf("TELNET 协议\n");break;
                case 25:printf("SMTP 协议\n");break;
                case 110:printf("POP3 协议\n");break;
                default:break;
        }
        printf("序列号:%u\n",sequence);
        printf("确认号:%u\n",acknowledgement);
        printf("首部长:%d\n",header_length);
        //printf("保留:%d\n",tcp_protocol->tcp_reserved);
       
        printf("滑动窗口大小:%d\n",windows);
        printf("校验和:%d\n",checksum);
        printf("紧急指针:%d\n",urgent_pointer);
}

/*IP协议的回调函数*/
void ip_protocol_packet_callback(u_char *argument,const struct pcap_pkthdr * packet_header,const u_char * packet_content)
{
        struct ip_header * ip_protocol;
        u_int header_length;                            /*首部长度*/
        u_int offset;                                   /*偏移*/
        u_char tos;                                     /*服务质量*/
        u_int16_t checksum;                             /*校验和*/
        printf("******************************* IP  (网络层) *********************\n");
        //获得IP协议数据内容,应该跳过以太网协议头
        ip_protocol = (struct ip_header *)(packet_content+14);
        checksum = ntohs(ip_protocol->ip_checksum);
        header_length = ip_protocol->ip_header_length*4;
        tos = ip_protocol->ip_tos_taowenliu;
        offset = ntohs(ip_protocol->ip_off);

        printf("IP 版本号:%d\n",ip_protocol->ip_version);
        printf("首部长:%d\n",header_length);
        printf("服务质量:%d\n",tos);
        printf("总长:%d\n",ntohs(ip_protocol->ip_length));
        printf("标识:%d\n",ntohs(ip_protocol->ip_id));
        printf("偏移:%d\n",(offset & 0x1fff)*8);
        printf("生存时间:%d\n",ip_protocol->ip_ttl);
        printf("协议:%d\n",ip_protocol->ip_protocol);
        switch(ip_protocol->ip_protocol)
        {
                case 6:printf("对应传输层协议TCP\n");break;
                case 17:printf("对应传输层协议UDP\n");break;
                case 1:printf("对应传输层协议ICMP\n");break;
                default:break;
        }


 printf("Header checksum:%d\n",checksum);
        printf("源IP地址:%s\n",inet_ntoa(ip_protocol->ip_source_address));       
 printf("目的IP地址:%s\n",inet_ntoa(ip_protocol->ip_destination_address));
        switch(ip_protocol->ip_protocol)//如果是6就调用tcp回调函数
        {
                case 6:tcp_protocol_packet_callback(argument,packet_header,packet_content);break;
                default:break;
        }
}

/*以太网协议的回调函数*/
void ethernet_protocol_packet_callback(u_char *argument,const struct pcap_pkthdr * packet_header,const u_char * packet_content)
{
        u_short ethernet_type;
        struct ether_header * ethernet_protocol;
        u_char * mac_string;
        static int packet_number = 1;
        printf("***********************************************\n");
        printf("第 %d 包被抓到.\n",packet_number);
        printf("******* 以太网协议 (数据链路层)***************\n");

        ethernet_protocol = (struct ether_header *)packet_content;//。。。。
       
	 printf("以太网类型 : ");

        ethernet_type = ntohs(ethernet_protocol->ether_type);
        printf("%04x\n",ethernet_type);//必须填充够四位
        switch(ethernet_type)
        {
                case 0x0800:printf("对应网络层协议是 IP\n");break;
                case 0x0806:printf("对应网络层协议是 ARP \n");break;
                case 0x0835:printf("对应网络层协议是 RARP \n");break;
                default:break;
        }
        printf("源MAC地址:");
        mac_string=ethernet_protocol->ether_shost;
        printf("%02x:%02x%02x:%02x:%02x:%02x\n",*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
        printf("目的MAC地址:");
        mac_string=ethernet_protocol->ether_dhost;
        printf("%02x:%02x%02x:%02x:%02x:%02x\n",*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));


        switch(ethernet_type)//这种情况下是IP
        {
                case 0x0800:ip_protocol_packet_callback(argument,packet_header,packet_content);
                break;
                default:break;
        }
        printf("********************************\n");
        packet_number++;
}

int main()
{
        pcap_t * pcap_handle;

        char error_content[PCAP_ERRBUF_SIZE];

        char * net_interface;
        struct bpf_program bpf_filter;
      
        bpf_u_int32 net_mask;
        bpf_u_int32 net_ip;

        net_interface = pcap_lookupdev(error_content);
        pcap_lookupnet(net_interface,&net_ip,&net_mask,error_content);
        pcap_handle = pcap_open_live(net_interface,BUFSIZ,1,0,error_content);
        pcap_compile(pcap_handle,&bpf_filter,"tcp",0,net_ip);
        pcap_setfilter(pcap_handle,&bpf_filter);

       
        pcap_loop(pcap_handle,1,ethernet_protocol_packet_callback,NULL);
        pcap_close(pcap_handle);
return 0;
}


