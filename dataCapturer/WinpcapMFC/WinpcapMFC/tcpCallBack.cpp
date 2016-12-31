#include "stdafx.h"

void tcp_protocol_packet_callback(FILE *file,const struct pcap_pkthdr* packet_header, const u_char* packet_content,struct mysqlData* sqlDataCopy)
{
	struct tcp_header *tcp_protocol;
	u_short source_port;
	u_short destination_port;
	int offset;
	tcp_protocol=(struct tcp_header*)(packet_content+14+20);
	source_port=ntohs(tcp_protocol->tcp_source_port);
	destination_port=ntohs(tcp_protocol->tcp_destination_port);
	offset=tcp_protocol->tcp_offset;
	printf("source prot:%d\n",source_port);
	printf("destination port:%d\n",destination_port);
	fprintf(file,"source prot:%d\n",source_port);
	fprintf(file,"destination port:%d\n",destination_port);
	sqlDataCopy->source_port=source_port;
	sqlDataCopy->dest_port=destination_port;

	int port;
	if(source_port<1024)
		port=source_port;
	else
		port=destination_port;

	switch(port)
	{
		case 80:
			printf("It's http package.\n");
			fprintf(file,"It's http package.\n");
			sprintf(sqlDataCopy->appLayer,"HTTP");
			break;
		case 21:
			printf("It's ftp package.\n");
			fprintf(file,"It's ftp package.\n");
			sprintf(sqlDataCopy->appLayer,"FTP");
			break;
		case 25:
			printf("It's smtp package.\n");
			fprintf(file,"It's smtp package.\n");
			sprintf(sqlDataCopy->appLayer,"SMTP");
			break;
		default:

			printf("It's another kind of package.\n");
			fprintf(file,"It's another kind of package.\n");
			break;
	}

	//printf("%d\n",offset);
	bpf_u_int32 length=packet_header->caplen;
	//printf("%d\n",length);
	const u_char *data=NULL;
	data=(packet_content+14+20+4*offset);
	int i=0;

	if(length==14+20+4*offset)
	{
		printf("It's a null packet");
		fprintf(file,"It's a null packet");
	}
	else
	{
		printf("The package cotains:\n");
		fprintf(file,"The package cotains:\n");
	}
	while(length>14+20+4*offset+i)
	{
		printf("%0.2x",*(data+i));		
		fprintf(file,"%0.2x",*(data+i));
		i++;
	}
	printf("\n");
}