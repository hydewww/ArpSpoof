#ifndef _INIT_
#define _INIT_

#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>

#include "struct.h"

void selectAdapter(pcap_t **handle);	//ѡ������������
void inputMac(unsigned char * mac);		//����Mac��ַ����ת��Ϊunsigned char[]
void makePkt(ARP_PKT *pkt, char *src_ip, unsigned char *src_mac, char *dst_ip, unsigned char* dst_mac);	//�������ݰ�

#endif
