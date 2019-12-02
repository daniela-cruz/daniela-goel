#include <stdlib.h>     /* malloc, free */

#include "dhcp.h"       /* all below */
#include "trie.h"       /* binary trie type */

struct dhcp
{
    uint32_t net_add;
    uint32_t net_mask;
    trie_t *trie;
};

static size_t GetHeightFromNetMask(uint32_t net_mask);
uint32_t GenerateIp(uint32_t net_add, uint32_t end);

dhcp_t *DHCPCreate(uint32_t net_add, uint32_t net_mask)
{
    int status = 0;
    dhcp_t *dhcp = NULL;

    dhcp = malloc(sizeof(*dhcp));
    if (NULL == dhcp)
    {
        return NULL;
    }

    dhcp->trie = TrieCreate(GetHeightFromNetMask(net_mask));
    if (NULL == dhcp->trie)
    {
        free(dhcp);

        return NULL;
    }
    dhcp->net_add = net_add;
    dhcp->net_mask = net_mask;

    status |= TrieInsert(dhcp->trie, net_mask, NULL);
    status |= TrieInsert(dhcp->trie, ~net_mask, NULL);
    status |= TrieInsert(dhcp->trie, (~net_mask) - 1, NULL);

    if (1 == status)
    {
        TrieDestroy(dhcp->trie);
        
        free(dhcp);
        dhcp = NULL;
    }

    return dhcp;
}

void DHCPDestroy(dhcp_t *dhcp)
{
    TrieDestroy(dhcp->trie);

    free(dhcp); dhcp = NULL;
}

int DHCPAllocIp(dhcp_t *dhcp, uint32_t *ip, void *data)
{
    int status = 1;

    if (!TrieFindNextFree(dhcp->trie, ip))
    {
        status = TrieInsert(dhcp->trie, *ip, data);
    }

    if(0 == status)
    {
        *ip = GenerateIp(dhcp->net_add, *ip);
    }

    return status;
}

void DHCPRelease(dhcp_t *dhcp, uint32_t ip)
{
    ip -= dhcp->net_add;

    TrieRemove(dhcp->trie, ip);

    ip = 0;
}

static size_t GetHeightFromNetMask(uint32_t net_mask)
{
    size_t count = 0;

    for(net_mask = ~net_mask, count = 0; net_mask != 0; count++)
    {
        net_mask >>= 1;
    }

    return count;
}

uint32_t GenerateIp(uint32_t net_add, uint32_t end)
{
    return net_add | end;
}
