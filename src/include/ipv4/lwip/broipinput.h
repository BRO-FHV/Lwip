/*
 * Lwip: ipinput.h
 * Part of BRO Project, 2014 <<https://github.com/BRO-FHV>>
 *
 * Created on: 13.06.2014
 * Description: 
 * TODO
 */

#ifndef IPINPUT_H_
#define IPINPUT_H_

#include <inttypes.h>
#include "lwip/netif.h"

#define IP_ADDR_LENGTH		4
#define MAC_ADDR_LENGTH 	6
#define TYPE_LENGTH 		2
#define IP_V4_TYPE			0x0800
#define ARP_TYPE			0x0806
#define UDP_PROT			17
#define TCP_PROT			6
#define BROADCAST_ADDR		4294967295
#define ANY_ADDR			0

typedef struct {
	uint8_t destMacAddr[MAC_ADDR_LENGTH];
	uint8_t srcMacAddr[MAC_ADDR_LENGTH];
	uint8_t type[TYPE_LENGTH];
} eth_header_t;

typedef struct {
	uint8_t ethHeader[14];

	unsigned version :4;
	unsigned ihl :4;
	uint8_t tos;
	uint16_t tot_len;
	uint16_t ident;
	uint16_t flags_offset;
	uint8_t ttl;
	uint8_t protocol;
	uint16_t checksum;
	uint8_t srcIp[IP_ADDR_LENGTH];
	uint8_t destIp[IP_ADDR_LENGTH];
} ip_header_t;

typedef struct {
	uint8_t ethHeader[14];
	uint8_t ipHeader[20];

	uint8_t srcPort[2];
	uint8_t destPort[2];
	uint8_t len[2];
	uint8_t checksum[2];

	uint8_t data1;
	uint8_t data2;

	uint8_t dataRestStart;
} udp_header_t;

typedef struct {
	uint8_t ethHeader[14];
	uint8_t ipHeader[20];

	uint8_t srcPort[2];
	uint8_t destPort[2];

	uint8_t seqNr[4];
	uint8_t ackNr[4];

	uint8_t dataOffset; //data offset = 4 bit + 4 bit reserved
	uint8_t controlFlags; //first 2 bit reserved, rest control flags

	uint8_t window[2];
	uint8_t checksum[2];
	uint8_t urgentPtr[2];

	uint8_t dataStart;
} tcp_header_t;

extern void BroUdpInput(eth_header_t* ethHeader, ip_header_t* ipHeader, udp_header_t* udpHeader, uint8_t data[], uint32_t dataLen);
extern void BroTcpInput(eth_header_t* ethHeader, ip_header_t* ipHeader, tcp_header_t* tcpheader, uint8_t data[], uint32_t dataLen);

err_t BroIpInput(struct pbuf *p, struct netif *inp);

uint16_t ConvertBigToLittleEndian(uint8_t data[]);
uint32_t IpToInt(uint8_t data[]);

#endif /* IPINPUT_H_ */
