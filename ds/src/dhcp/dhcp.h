#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t */

typedef struct dhcp dhcp_t;

/****************** API ************************/

dhcp_t* DHCPCreate(char *net_add, size_t net_mask);

int DHCPAllocIp(dhcp_t *dhcp, uint32_t *addr);

void DHCPRelease(dhcp_t *dhcp, uint32_t addr);

void DHCPDestroy(dhcp_t *dhcp);

#endif /* __DHCP_H__ */