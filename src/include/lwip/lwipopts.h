/*
 * Driver: lwipopts.h
 * Part of BRO Project, 2014 <<https://github.com/BRO-FHV>>
 *
 * Created on: 04.04.2014
 * Description: 
 * TODO
 */

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

/*****************************************************************************
**                           CONFIGURATIONS
*****************************************************************************/

/*
** The macro CPSW_DUAL_MAC_MODE shall be defined for using CPSW ports in
** Dual MAC mode.
*/
#define CPSW_DUAL_MAC_MODE

/*
** The below macro should be defined for using lwIP with cache. For cache
** enabling, pbuf pool shall be cache line aligned. This is done by using
** separate pool for each memory. The alignment of pbuf pool to cache line
** size is done in /ports/cpsw/include/arch/cc.h.
*/

#define SOC_CACHELINE_SIZE_BYTES        64            /* Number of bytes in
                                                         a cache line */

/*
** The number of times DHCP is attempted. Each time, the library will wait
** for (LWIP_DHCP_TIMEOUT / 100) seconds for DHCP completion.
*/
#define NUM_DHCP_TRIES                  10

/*****************************************************************************
**            lwIP SPECIFIC DEFINITIONS - To be used by lwIP stack
*****************************************************************************/
#define HOST_TMR_INTERVAL               0
#define DYNAMIC_HTTP_HEADERS

/*****************************************************************************
**                    Platform specific locking
*****************************************************************************/
#define SYS_LIGHTWEIGHT_PROT            1
#define NO_SYS                          1
#define NO_SYS_NO_TIMERS                1

/*****************************************************************************
**                          Memory Options
*****************************************************************************/
/**
 * MEM_ALIGNMENT: should be set to the alignment of the CPU
 *    4 byte alignment -> #define MEM_ALIGNMENT 4
 *    2 byte alignment -> #define MEM_ALIGNMENT 2
 */
#define MEM_ALIGNMENT                   4
/**
 * MEM_SIZE: the size of the heap memory. If the application will send
 * a lot of data that needs to be copied, this should be set high.
 */
#define MEM_SIZE                        (128 * 1024) /* 128K */

#define MEMP_NUM_PBUF                   96
#define MEMP_NUM_TCP_PCB                32
#define PBUF_POOL_SIZE                  210

#define MEM_LIBC_MALLOC                 1
#define MEMP_MEM_MALLOC                 1

//#define LWIP_CACHE_ENABLED

#ifdef LWIP_CACHE_ENABLED
#define MEMP_SEPARATE_POOLS             1            /* We want the pbuf
                                                        pool cache line
                                                        aligned*/
#endif

/*****************************************************************************
**                           IP Options
*****************************************************************************/
#define IP_REASSEMBLY                   0
#define IP_FRAG                         0

/*****************************************************************************
**                           DHCP Options
*****************************************************************************/
#define LWIP_DHCP                       1	//enable DHCP
#define DHCP_DOES_ARP_CHECK             1
/*
** The timeout for DHCP completion. lwIP library will wait for DHCP
** completion for (LWIP_DHCP_TIMEOUT / 100) seconds.
*/
#define LWIP_DHCP_TIMEOUT               500

/*****************************************************************************
**                           Auto IP  Options
*****************************************************************************/
#define LWIP_AUTOIP                     0
#define LWIP_DHCP_AUTOIP_COOP           ((LWIP_DHCP) && (LWIP_AUTOIP))

/*****************************************************************************
**                           TCP  Options
*****************************************************************************/
#define TCP_MSS                         1500
#define TCP_WND                         (8 * TCP_MSS)
#define TCP_SND_BUF                     (8 * TCP_MSS)
#define TCP_OVERSIZE                    TCP_MSS

/*****************************************************************************
**                           PBUF  Options
*****************************************************************************/
#define PBUF_LINK_HLEN                  14
#define PBUF_POOL_BUFSIZE               1520         /* + size of struct pbuf
                                                        shall be cache line
                                                        aligned be enabled */
#define ETH_PAD_SIZE                    0
#define LWIP_NETCONN                    0

/*****************************************************************************
**                           Socket  Options
*****************************************************************************/
#define LWIP_SOCKET                     0

/*****************************************************************************
**                          Debugging options
*****************************************************************************/
#define LWIP_DBG_MIN_LEVEL              LWIP_DBG_LEVEL_OFF
#define LWIP_DBG_TYPES_ON               (LWIP_DBG_ON | LWIP_DBG_TRACE \
                                         |LWIP_DBG_STATE | LWIP_DBG_FRESH)
#endif /* __LWIPOPTS_H__ */
