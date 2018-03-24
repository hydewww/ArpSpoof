#ifndef _STRUCT_
#define _STRUCT_

#define HDW_TYPE    0x0001          //硬件类型：Ethernet网接口类型为1
#define PRO_TYPE    0x0800          //协议类型：IP协议类型为0x0800
#define ETH_TYPE    0x0806			//Ethernet网类型
#define ARP_REQUEST 0x0001          //arp请求
#define ARP_REPLY   0x0002          //arp应答
#define MAC_LEN     6               //MAC地址长度
#define IP_LEN      4               //IP地址长度

#pragma pack (1)					//设置让结构体以一个字节对齐

struct eth_header {					//Ethernet网头部
	unsigned char dst_mac[MAC_LEN];
	unsigned char src_mac[MAC_LEN];
	unsigned short type;			//Ethernet网类型
};
struct arp_head {                   //Arp头部
	unsigned short hdw_type;		//硬件类型：Ethernet网接口类型为1
	unsigned short pro_type;		//协议类型：IP协议类型为0x0800
	unsigned char hdw_len;          //硬件地址长度：MAC地址长度为6B
	unsigned char pro_len;          //协议地址长度：IP地址长度为4B
	unsigned short option;          //Arp请求为1，Arp应答为2
	unsigned char src_mac[MAC_LEN];
	unsigned long src_ip;
	unsigned char dst_mac[MAC_LEN];	//ARP请求中没有意义，响应中为接收方MAC
	unsigned long dst_ip;			//ARP请求中为请求解析的IP，ARP响应中为接收方IP
};
typedef struct arp_packet {
	struct eth_header eth;      //Ethernet网头部
	struct arp_head arp;        //ARP头部
}ARP_PKT;

#endif
