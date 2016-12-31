#include "pcap.h"
char * net_interface;
/*回调函数*/
void packet_callback(u_char *argument,const struct pcap_pkthdr * packet_header,const u_char * packet_content)
{
        static int packet_number = 1; /*静态局部变量,用来存放捕获包的个数*/
        printf("The %d packet is captured.\n",packet_number);
	printf("Capture a packet from : %s\n",net_interface);   //输出网络接口名字
 	printf("The packet length is : %d\n",packet_header->len);//输出捕获的数据包的长度
        packet_number++;
}

int main()
{
        pcap_t * pcap_handle;
        char error_content[PCAP_ERRBUF_SIZE];
        
        struct bpf_program bpf_filter;
        char bpf_filter_string[]="ip";
        bpf_u_int32 net_mask;
        bpf_u_int32 net_ip;

        /*获得网络接口*/
        net_interface = pcap_lookupdev(error_content);
        /*获得网络地址and mask */
        pcap_lookupnet(net_interface,&net_ip,&net_mask,error_content);
        /*打开网络接口*/
        pcap_handle = pcap_open_live(net_interface,BUFSIZ,1,0,error_content);
        /*提供过滤规则*/
        pcap_compile(pcap_handle,&bpf_filter,bpf_filter_string,0,net_ip);
        /*设置过滤规则*/
        pcap_setfilter(pcap_handle,&bpf_filter);
        /*注册回调函数,第二个参数是设置捕获数据包的个数,如果设置为-1就表示无限循环*/
        pcap_loop(pcap_handle,10,packet_callback,NULL);
        pcap_close(pcap_handle);
return 0;
}



