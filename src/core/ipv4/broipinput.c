/*
 * Lwip: broipinput.c
 * Part of BRO Project, 2014 <<https://github.com/BRO-FHV>>
 *
 * Created on: 13.06.2014
 * Description: 
 * TODO
 */

#include <Syscall/lib_syscall.h>
#include <inttypes.h>
#include <string.h>
#include "lwip/broipinput.h"
#include "lwip/netif.h"

// max payload size in bytes
#define UDP_MAX_DATA 1000
#define TCP_MAX_DATA 1460


uint8_t udpData[UDP_MAX_DATA];
uint8_t tcpData[TCP_MAX_DATA];

uint32_t isIPType(eth_header_t* header);
uint16_t convertBigToLittleEndian(uint8_t data[]);
uint32_t ipToInt(uint8_t data[]);
uint32_t isPacketForUs(ip_header_t* header, struct netif *inp);

err_t BroIpInput(struct pbuf *p, struct netif *inp) {
	eth_header_t* ethHeader = (eth_header_t*) p->payload;

	if (isIPType(ethHeader)) {
		ip_header_t* ipHeader = (ip_header_t*) ethHeader;

		//check if packet is for us and if packet is a UDP packet
		if (isPacketForUs(ipHeader, inp)) {
			if (UDP_PROT == ipHeader->protocol) {
				udp_header_t* udpHeader = (udp_header_t*) ipHeader;

				//clear data - set everything to zero
				memset(udpData, 0, UDP_MAX_DATA);

				//data 1 and data 2 are not aligned
				udpData[0] = udpHeader->data1;
				udpData[1] = udpHeader->data2;

				//copy rest of data aligned
				//-8 because udpHeader->len is data header + data
				//we are just interesed in data
				uint32_t dataLen = convertBigToLittleEndian(udpHeader->len) - 8;
				memcpy(&udpData[2], &udpHeader->dataRestStart, dataLen - 2);

				BroUdpInput(ethHeader, ipHeader, udpHeader, udpData, dataLen);
			} else if (TCP_PROT == ipHeader->protocol) {
				tcp_header_t* tcpHeader = (tcp_header_t*) ipHeader;
			}
		}
	}

	return ERR_OK;
}

uint32_t isIPType(eth_header_t* header) {
	return header->type[0] == 0x08 && header->type[1] == 0x00;
}

uint16_t convertBigToLittleEndian(uint8_t data[]) {
	return data[1] + (data[0] << 8);
}

uint32_t ipToInt(uint8_t data[]) {
	return data[0] + (data[1] << 8) + (data[2] << 16) + (data[3] << 24);
}

uint32_t isPacketForUs(ip_header_t* header, struct netif *inp) {
	uint32_t dest = ipToInt(header->destIp);

	return BROADCAST_ADDR == dest || ANY_ADDR == dest
			|| ((ip_addr_t) inp->ip_addr).addr == dest;
}
