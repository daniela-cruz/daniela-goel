#include <stdlib.h> /* malloc */

#include "trie.h"

enum child_t {OFF, ON};

typedef struct trie_node
{
    void *data;
    size_t unused_branches;
    struct trie_node_t *child[2];
}trie_node_t;

struct trie
{
    size_t height;
    trie_node_t *root;
};

trie_t *TrieCreate(size_t height)
{
    trie_t *trie = NULL;

    do
    {
        trie = malloc(sizeof(*trie));
        if (NULL == trie)
        {
            return NULL;
        }
        
        trie->height = height;
        trie->root = NodeCreate(trie->height, NULL);
        if (NULL == trie->root)
        {
            break;
        }
    } while (0);
    
    /* cleanup: */
    (NULL == trie->root) ? free(trie) : trie;

    return trie;
}

int TrieInsert(trie_t *trie, uint32_t path, void *data)
{
    int status = 0;

    trie->root = InsertRec(trie->root, trie->height, path, data, &status);

    return status;
}

void TrieRemove(trie_t *trie, uint32_t path)
{
    RemoveRec(trie->root, trie->height, path);
}

void *TrieFind(trie_t *trie, uint32_t path)
{
    return FindRec(trie->root, trie->height, path);
}

int TrieFindNextFree(trie_t *trie, uint32_t *path)
{
    uint32_t ip_path = 0;
    int status = 0;
    
    status = FindNextFreeRec(trie->root, trie->height, &ip_path);
    *path = ip_path;

    return status;
}

void TrieDestroy(trie_t *trie)
{
    CleanTreePaths(trie->root);
    free(trie); trie = NULL;
}

static void *InsertRec(trie_node_t *root, size_t height, uint32_t path, void *data, int *status)
{
    uint32_t idx = 0;
    
    if (0 == height)
    {
        root = NodeCreate(0, data);
        if(NULL == root)
        {
            *status = 1;
        }

        return root;
    }

    if (NULL == root)
    {
        root = NodeCreate(height, NULL);
        if(NULL == root)
        {
            *status = 1;
            return root;
        }
    }

    idx = (!!1) & (path >> (height - 1));
    root->child[idx] = InsertRec(root->child[idx], height - 1, path, data, status);

    RefreshUnused(root, height);

    return root;
}

static void *RemoveRec(trie_node_t *root, size_t height, uint32_t path)
{
    uint32_t idx = 0;
    
    if (0 == height)
    {
        free(root); root = NULL;
        return NULL;
    }

    idx = (!!1) & (path >> (height - 1));
    root->child[idx] = RemoveRec(root->child[idx], height - 1, path);
    root->unused_branches++;

    return root;
}

static void *FindRec(trie_node_t *root, size_t height, uint32_t path)
{
    uint32_t idx = 0;

    if (0 == height)
    {
        return root->data;
    }

    idx = (!!1) & (path >> (height - 1));

    return FindRec(root->child[idx], height - 1, path >> 1);
}

static int FindNextFreeRec(trie_node_t *root, size_t height, uint32_t *path)
{
    int status = 0;
    uint32_t mask = 0;
    
    if (NULL == root)
    {
        return 0;
    }

    if ((0 == root->unused_branches) || (0 == height))
    {
        return 1;
    }    

    status = FindNextFreeRec(root->child[OFF], height - 1, path);
    
    if (1 == status)
    {
        mask = 1 << (height - 1);
        *path |= mask;

        return FindNextFreeRec(root->child[ON], height - 1, path);
    }

    return status;
}

static void CleanTreePaths(trie_node_t *root)
{
    if (NULL == root)
    {
        return;
    }

    CleanTreePaths(root->child[OFF]);
    CleanTreePaths(root->child[ON]);
    free(root); root = NULL;
}

static void RefreshUnused(trie_node_t *root, size_t height)
{
    int r_unused = 0, l_unused = 0;

    if (NULL != root->child[OFF])
    {
        l_unused = root->child[OFF]->unused_branches;
    }
    else
    {
        l_unused = (1 << height) - 1;
    }
    

    if (NULL != root->child[ON])
    {
        r_unused = root->child[ON]->unused_branches;
    }
    else
    {
        r_unused = (1 << height) - 1;
    }
    

    root->unused_branches = r_unused + l_unused;
}

static trie_node_t *NodeCreate(size_t height, void *data)
{
    trie_node_t *node = NULL;
    
    node = malloc(sizeof(*node));
    if (NULL == node)
    {
        return NULL;
    }
    
    node->data = data;
    node->unused_branches = (1 << (height + 1)) - 2;
    node->child[OFF] = NULL;
    node->child[ON] = NULL;

    return node;
}