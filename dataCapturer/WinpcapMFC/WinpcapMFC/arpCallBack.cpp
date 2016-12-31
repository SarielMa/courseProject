#include "stdafx.h"

void arp_protocol_packet_callback(FILE *file,const struct pcap_pkthdr* packet_header, const u_char* packet_content,struct mysqlData* sqlDataCopy)
{
	struct arp_header * arp_protocol;
	u_short protocol_type;
	u_short hardware_type;
	u_short operation_code;
	u_char * mac_string;
	struct in_addr source_ip_address;
	struct in_addr destination_ip_address;
	u_char hardware_length;
	u_char protocol_length;
	
	arp_protocol=(struct arp_header*)(packet_content+14);
	hardware_type=ntohs(arp_protocol->arp_hardware_type);
	protocol_type=ntohs(arp_protocol->arp_protocol_type);
	operation_code=ntohs(arp_protocol->arp_operation_code);
	hardware_length=arp_protocol->arp_hardware_length;
	protocol_length=arp_protocol->arp_protocol_length;


	memcpy((void*)&source_ip_address,(void*)&arp_protocol->arp_source_ip_address,sizeof(source_ip_address));
	printf("Source IP address:%s\n",inet_ntoa(source_ip_address));
	fprintf(file,"Source IP address:%s\n",inet_ntoa(source_ip_address));
	sprintf(sqlDataCopy->source_ip,"%s",inet_ntoa(source_ip_address));

	memcpy((void*)&destination_ip_address,(void*)&arp_protocol->arp_destination_ip_address,sizeof(struct in_addr));
	printf("Destination IP Address :%s\n",inet_ntoa(destination_ip_address));
	fprintf(file,"Destination IP Address :%s\n",inet_ntoa(destination_ip_address));
	sprintf(sqlDataCopy->source_ip,"%s",inet_ntoa(destination_ip_address));
}

