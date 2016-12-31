#include "stdafx.h"

void ip_protocol_packet_callback(FILE *file,const struct pcap_pkthdr* packet_header, const u_char* packet_content,struct mysqlData*sqlDataCopy )
{

	struct ip_header *ip_protocol;
	u_int header_length;
	u_int offset;
	u_char tos;
	u_int16_t checksum;
	ip_protocol=(struct ip_header*)(packet_content+14);
	checksum=ntohs(ip_protocol->ip_checksum);
	header_length=ip_protocol->ip_header_length*4;
	tos=ip_protocol->ip_tos;
	offset=ntohs(ip_protocol->ip_off);


	printf("Source address:%s\n",inet_ntoa(ip_protocol->ip_source_address));
	printf("Desination address:%s\n",inet_ntoa(ip_protocol->ip_destination_address));
	fprintf(file,"Source address:%s\n",inet_ntoa(ip_protocol->ip_source_address));
	fprintf(file,"Desination address:%s\n",inet_ntoa(ip_protocol->ip_destination_address));
	sprintf(sqlDataCopy->source_ip,"%s",inet_ntoa(ip_protocol->ip_source_address));
	sprintf(sqlDataCopy->dest_ip,"%s",inet_ntoa(ip_protocol->ip_destination_address));
	switch (ip_protocol->ip_protocol)
	{
		case 6:
			printf("The transport layer protocol is TCP..\n");
			fprintf(file,"The transport layer protocol is TCP..\n");
			sprintf(sqlDataCopy->transportLayer,"TCP");

			tcp_protocol_packet_callback(file,packet_header,packet_content,sqlDataCopy);
			break;
		case 17:
			printf("The transport layer protocol is UDP..\n");
			fprintf(file,"The transport layer protocol is UDP..\n");
			sprintf(sqlDataCopy->transportLayer,"UDP");
			udp_protocol_packet_callback(file,packet_header,packet_content,sqlDataCopy);
			break;
		case 1:
			printf("The transport layer protocol is ICMP..\n");
			fprintf(file,"The transport layer protocol is ICMP..\n");
			sprintf(sqlDataCopy->networkLayer,"ICMP");
			break;
		default:
			break;
	}


}