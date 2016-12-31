#include "stdafx.h"
void udp_protocol_packet_callback(FILE *file,const struct pcap_pkthdr* packet_header,const u_char* packet_content,struct mysqlData*sqlDataCopy){
	struct udp_header *udp_protocol;//UDPЭ�����ݱ���
	u_short source_port;//Դ�˿�
	u_short destination_port;//Ŀ�Ķ˿�
	u_short length;//����
	udp_protocol=(struct udp_header*)(packet_content+14+20);//UDPЭ����������
	source_port=ntohs(udp_protocol->udp_source_port);//��ȡԴ�˿�
	destination_port=ntohs(udp_protocol->udp_destination_port);//��ȡĿ�Ķ˿� 
	length=ntohs(udp_protocol->udp_length);//��ȡ����
	/*printf("------UDP-------\n");*/
	printf("source prot:%d\n",source_port);
	printf("destination port:%d\n",destination_port);
	fprintf(file,"source prot:%d\n",source_port);
	fprintf(file,"destination port:%d\n",destination_port);
	sqlDataCopy->source_port=source_port;
	sqlDataCopy->dest_port=destination_port;


	switch(destination_port){//���ݶ˿ں��ж�Ӧ�ò�Э������
		case 17:
			printf("DHCP\n");
			fprintf(file,"DHCP\n");
			sprintf(sqlDataCopy->appLayer,"DHCP");
			break;
		case 18 :
			printf("DHCP\n");
			fprintf(file,"DHCP\n");
			sprintf(sqlDataCopy->appLayer,"DHCP");
			break;
		case 138:
			printf("NETBIOS Datagram Service\n");
			fprintf(file,"NETBIOS Datagram Service\n");
			sprintf(sqlDataCopy->appLayer,"NETNS");
			break;
		case 137:
			printf("NETBIOS Name Service\n");
			fprintf(file,"NETBIOS Name Service\n");
			sprintf(sqlDataCopy->appLayer,"NETNS");
			break;
		case 139:
			printf("NETBIOS session service\n");
			fprintf(file,"NETBIOS session service\n");
			sprintf(sqlDataCopy->appLayer,"NETSS");
			break;
		case 53:
			printf("Name-Domain server\n");
			fprintf(file,"Name-Domain server\n");
			sprintf(sqlDataCopy->appLayer,"NDS");
			break;
		default:
			break;
	}
	//printf("Length:%d\n",length);
	//printf("Checksum:%d\n",ntohs(udp_protocol->udp_checksum));
	for(int i=14+20+8;i<packet_header->len;i++){
		printf("%0.2x",packet_content[i]);
		fprintf(file,"%0.2x",packet_content[i]);
	}
	printf("\n");
}