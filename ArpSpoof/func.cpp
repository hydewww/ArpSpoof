#include "init.h"

//ѡ������������
void selectAdapter(pcap_t **handle) {
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t *alldevs;
	pcap_if_t *tmp;
	int num = 0;

	//��ȡ�����б�
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	//��ӡ�����б�
	for (tmp = alldevs; tmp; tmp = tmp->next)
	{
		printf("%d. %s (%s)\n", ++num, tmp->name, tmp->description);
	}
	if (num == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		exit(1);
	}

	//ѡ������
	int no;
	printf("Enter the interface number (1-%d):", num);
	scanf("%d", &no);
	while (no < 1 || no > num)
	{
		printf("\nInterface number out of range.\n");
		printf("Enter the interface number (1-%d):", num);
		scanf("%d", &no);
	}
	int i;
	for (i = 0, tmp = alldevs; i < no - 1; tmp = tmp->next, i++);

	//������
	if ((*handle = pcap_open_live(tmp->name, 65536, PCAP_OPENFLAG_PROMISCUOUS, 1000, errbuf)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n", tmp->name);
		/* Free the device list */
		pcap_freealldevs(alldevs);
		exit(1);
	}
	printf("Successfully Open the adapter <%s> \n", tmp->description);
}

//����Mac��ַ����ת��Ϊunsigned char[]
void inputMac(unsigned char *mac) {
	char str[13];
	scanf("%s", str);
	int tmp;
	for (int i = 0; i < 6; i++) {
		sscanf(str + 2 * i, "%2x", &tmp);
		mac[i] = (unsigned char)tmp;
	}
}

//�������ݰ�
void makePkt(ARP_PKT *pkt, char *src_ip, unsigned char *src_mac, char *dst_ip, unsigned char* dst_mac) {
	pkt->eth.type = htons(ETH_TYPE);
	pkt->arp.hdw_type = htons(HDW_TYPE);
	pkt->arp.pro_type = htons(PRO_TYPE);
	pkt->arp.hdw_len = MAC_LEN;
	pkt->arp.pro_len = IP_LEN;
	pkt->arp.option = htons(ARP_REPLY);

	for (int i = 0; i < MAC_LEN; i++) {
		pkt->eth.src_mac[i] = pkt->arp.src_mac[i] = src_mac[i];
		pkt->eth.dst_mac[i] = pkt->arp.dst_mac[i] = dst_mac[i];
		pkt->arp.src_ip = inet_addr(src_ip);
		pkt->arp.dst_ip = inet_addr(dst_ip);
	}
}
