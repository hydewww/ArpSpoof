#ifndef _INIT_
#define _INIT_

#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>

#include "struct.h"

void selectAdapter(pcap_t **handle);	//选择网络适配器
void inputMac(unsigned char * mac);		//输入Mac地址，并转换为unsigned char[]
void makePkt(ARP_PKT *pkt, char *src_ip, unsigned char *src_mac, char *dst_ip, unsigned char* dst_mac);	//构造数据包

#endif
