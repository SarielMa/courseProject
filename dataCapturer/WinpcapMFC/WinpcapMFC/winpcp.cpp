#include "stdafx.h"

int count=0;
FILE *file;
struct mysqlData * sqlData;
struct mysqlData * sqlDataCopy;


pcap_t *adhandle;

int winpcpCatch()
{ 
        pcap_if_t *alldevs; 
        pcap_if_t *d; 
        int inum; 
        int i=0; 
		
        char errbuf[PCAP_ERRBUF_SIZE]; 

		/* ��ȡ�����б� */ 
        if(pcap_findalldevs(&alldevs, errbuf) == -1) 
        { 
			//fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf); 
			exit(1); 
        } 

		/* �����б� */ 
        for(d=alldevs; d; d=d->next) 
        {
				printf("%d. %s", ++i, d->name); 
				if(d->description) 
					printf(" (%s)\n", d->description); 
				else 
					printf(" (No description available)\n"); 
        } 

        if(i==0) 
        { 
                printf("\nNo interfaces found! Make sure WinPcap is installed.\n"); 
                return -1; 
        } 

        printf("Enter the interface number (1-%d):",i); 
        scanf("%d", &inum); 

        if(inum < 1 || inum > i) 
        { 
                printf("\nInterface number out of range.\n"); 
                /* �ͷ������б� */ 
                pcap_freealldevs(alldevs); 
                return -1; 
        } 
	/* ת��ѡ������� */ 
	for(d=alldevs, i=0; i< inum-1;d=d->next, i++);

	//int choose;
	//printf("select which package you want to catch\n");
	//printf("1:Catch  Ethernet packets\n");
	//printf("2:Catch IP packets\n");
	//printf("3:Catch ARP packets\n");
	//printf("Enter the filter type (1-3):");
	//scanf("%d",&choose);

	int catchNum;
	catchNum=packageNum;
	//printf("Input how many packages you want to catch:"); 
 //   scanf("%d", &catchNum); 


	sqlData=(struct mysqlData*)calloc(catchNum,sizeof(struct mysqlData));
	sqlDataCopy=sqlData;
	char bpf_filter_string[10]="";
	switch(choose)
	{
		case 1:
			strcpy(bpf_filter_string,"");
			break;
		case 2:
			strcpy(bpf_filter_string,"ip");
			break;
		case 3:
			strcpy(bpf_filter_string,"arp");
			break;
		default:
			printf("Input error, app halt.\n");
			exit(-1);
			break;
	}

		/* ������ */ 
	if( (adhandle= pcap_open_live(d->name, //�豸�� 
                65535, // ��׽���������ݰ� 
                1, // ����ģʽ 
                1000, // ���볬ʱ 
                errbuf // ���󻺳� 
                ) ) == NULL) 
	{ 
		/* Y- ��ʧ��*/ 
		fprintf(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n"); 
		/* �ͷ��б� */ 
		pcap_freealldevs(alldevs); 
		return -1; 
	}
	struct bpf_program bpf_filter;
	u_int32_t netmask = 0xffffffff;
	pcap_compile(adhandle,
			&bpf_filter,
			bpf_filter_string,
			0,
			netmask
		);
	pcap_setfilter(adhandle,	&bpf_filter);


	printf("\nlistening on %s...\n", d->description); 
	/* �����Ѿ�����Ҫ�����б���, �ͷ��� */ 
	pcap_freealldevs(alldevs);
	/* ��ʼ�������ݰ� */


	
	file=fopen("catch.txt","w");
	pcap_loop(adhandle, catchNum, packet_handler, NULL); 
	pcap_close(adhandle);
	fclose(file);
	printf("\nSave the output to file \"catch.txt\" you may read it..\n\n");

	char saveOrNot;
	printf("Do you want to save your package s into MySQL(Y/N)?:");
	getchar();
	scanf("%c", &saveOrNot); 
	if(saveOrNot=='y'||saveOrNot=='Y')
	{
		sqlDataCopy=sqlData;
		connectToMySQL(sqlDataCopy,catchNum);
	}

	free(sqlData);


	return 0; 
} 