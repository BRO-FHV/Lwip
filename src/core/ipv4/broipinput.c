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

#define MAX_DATA 1000

uint8_t data[MAX_DATA];

uint32_t isIPType(eth_header_t* header);
uint16_t convertBigToLittleEndian(uint8_t data[]);
uint32_t ipToInt(uint8_t data[]);
uint32_t isPacketForUs(ip_header_t* header, struct netif *inp);

err_t bro_ip_input(struct pbuf *p, struct netif *inp) {
	eth_header_t* ethHeader = (eth_header_t*) p->payload;

	if (isIPType(ethHeader)) {
		ip_header_t* ipHeader = (ip_header_t*) ethHeader;

		//check if packet is for us and if packet is a UDP packet
		if (isPacketForUs(ipHeader, inp) && UDP_PROT == ipHeader->protocol) {
			udp_header_t* udpHeader = (udp_header_t*) ipHeader;

			if (convertBigToLittleEndian(udpHeader->destPort) == 2000) {
				//clear data - set everything to zero
				memset(data, 0, MAX_DATA);

				//data 1 and data 2 are not aligned
				data[0] = udpHeader->data1;
				data[1] = udpHeader->data2;

				//copy rest of data aligned
				//-8 because udpHeader->len is data header + data
				//we are just interesed in data
				uint32_t dataLen = convertBigToLittleEndian(udpHeader->len)	- 8;
				memcpy(&data[2], &udpHeader->dataRestStart, dataLen - 2);

				broUdpInput(ethHeader, ipHeader, udpHeader, data, dataLen);
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
