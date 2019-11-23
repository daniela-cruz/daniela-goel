#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* printf */

#include "avl.h" /* avl_node_t, avl_t */

typedef enum child_t {BEFORE, AFTER} child_t;

typedef struct avl_node
{
    size_t height;
    void *data;
    struct avl_node *child[2];
} avl_node_t;

struct avl 
{
    avl_node_t *root;
    avl_is_before_t is_before;
    void *param;
};

/*---------------------------Forward declarations-----------------------------*/
/*****UTILITIES******/
avl_node_t *TraverseTreeInOrder(avl_node_t *head, avl_t *tree);
static int IsMatch(const avl_t *tree ,const void *data1, const void *data2);

static avl_node_t *InsertRec(avl_node_t *head, avl_t *tree, void *data, avl_node_t *new_node);
static avl_node_t *RemoveNode(avl_node_t *head, avl_t *tree, void *data);

static avl_node_t *FindAndFixRotation(avl_node_t *head, avl_t *tree);
static void UpdateHeight(avl_node_t *head);
static size_t Counter(avl_node_t *head, size_t counter);
static int ForEachRecursive(avl_node_t *head, avl_action_func_t func, void *param);
static void *FindElement(avl_node_t *head, avl_is_before_t func, const void *data);

void NodeDataSwap(avl_node_t *node1, avl_node_t *node2);
static avl_node_t *NodeCreate(void *data);
static void NodeFree(avl_node_t *head);
static avl_node_t *GetMaxNode(avl_t *tree);
static avl_node_t *GetMinNode(avl_t *tree);
static avl_node_t *GetLOCALMaxNode(avl_node_t *head);
static avl_node_t *GetLOCALMinNode(avl_node_t *head);

/*****ROTATORS******/
static avl_node_t *BalanceSubTree(avl_node_t *node);
static avl_node_t* RightRotate(avl_node_t *node);
static avl_node_t* LeftRotate(avl_node_t *node);

static size_t GetHeight(avl_node_t *node);

/*-------------------------------AVL functions--------------------------------*/
/**********************
 *  FUNCTIONS         *
**********************/
avl_t *AVLCreate(avl_is_before_t func, void *param)
{
    avl_t *tree = NULL;

    tree = malloc(sizeof(*tree));
    if (NULL == tree)
    {
        return NULL;
    }

    tree->root = NULL;
    tree->is_before = func;
    tree->param = param;

    return tree; 
}
 
void AVLDestroy(avl_t *tree)
{
    NodeFree(tree->root);
    free(tree); tree = NULL;
}

int AVLInsert(avl_t *tree, void *data)
{
    avl_node_t  *new_node ={NULL};

    new_node = NodeCreate(data);
    if(new_node == NULL)
    {
        return 1;
    }

    tree->root = InsertRec(tree->root, tree , data, new_node);
    
    return 0;
}

void AVLRemove(avl_t *tree, const void *data)
{
    avl_node_t *parent = NULL;

    parent = RemoveNode(tree->root, tree, (void *)data);
    FindAndFixRotation(parent, tree);
}

int AVLIsEmpty(const avl_t *tree)
{
    return (NULL == tree->root);
}

size_t AVLHeight(const avl_t *tree)
{
    return (NULL == tree->root) ? 0 : tree->root->height;
}

size_t AVLSize(const avl_t *tree)
{ 
    return Counter(tree->root, 0);
}

int AVLForEach(avl_t *tree, avl_action_func_t func, void *param)
{
    return ForEachRecursive(tree->root, func, param);
}

void *AVLFind(const avl_t *tree, const void *data)
{
   return FindElement(tree->root, tree->is_before, data);
}

/*-----------------------------Internal functions-----------------------------*/
/**********************
 *  Utilities         *
**********************/
static avl_node_t *InsertRec(avl_node_t *head, avl_t *tree, void *data, avl_node_t *new_node)
{
    int idx = 0;

    if (NULL == head)
    {
        return new_node;
    }

    idx = tree->is_before(head->data, data,tree->param);
    head->child[idx] = InsertRec(head->child[idx], tree, data, new_node);
    UpdateHeight(head);
    
    return FindAndFixRotation(head, tree);
}

static void ReplaceData(avl_node_t *node1, avl_node_t *node2)
{
    void *tmp = NULL;

    tmp = node1->data;
    node1->data = node2->data;
    node2->data = tmp;
}

avl_node_t *FindAndFixRotation(avl_node_t *head, avl_t *tree)
{
    int balance_factor = 0;

    if (NULL == head)
    {
        return NULL;
    }
    
    balance_factor = GetBalanceFactor(head);
    if (1 < balance_factor)
    {
        if ((NULL == head->child[BEFORE]) && (NULL != head->child[AFTER]))
        {
            head->child[BEFORE]->height -= 1;
            head->child[BEFORE]->child[AFTER] += 1;
            head->child[BEFORE] = LeftRotate(head->child[BEFORE]);
        }

        head->height -= 2;
        
        return RightRotate(head);
    }
    else if (-1 > balance_factor)
    {
        if (0 < GetBalanceFactor(head->child[AFTER]))
        {
           head->child[AFTER]->height -= 1;
            head->child[AFTER]->child[BEFORE] += 1;
            head->child[AFTER] = RightRotate(head->child[AFTER]); 
        }
        head->height -= 2;

        return LeftRotate(head);
    }
    
    return head;
}

static avl_node_t *RemoveNode(avl_node_t *head, avl_t *tree, void *data)
{
    avl_node_t *found_node = NULL;
    int idx = 0;

    if (!IsMatch(tree, head->data, data))
    {
        head->child[idx] = RemoveNode(head->child[idx], tree, data);
        UpdateHeight(head);

        return head;
    }

    if ((NULL == head->child[AFTER]) && (NULL == head->child[BEFORE]))
    {
        found_node = NULL; free(head);
    }
    else if ((NULL != head->child[BEFORE]) && (NULL != head->child[AFTER]))
    {
        avl_node_t *min_node = GetLOCALMinNode(head->child[AFTER]);

        NodeDataSwap(min_node, head);
        head->child[AFTER] = RemoveNode(head->child[AFTER], tree, min_node->data);
        found_node = head;
        head = min_node;
    }
    else
    {
        found_node = (NULL != head->child[BEFORE]) ? head->child[BEFORE] : head->child[AFTER];
        free(head);
    }

    return found_node;
}

static size_t Counter(avl_node_t *head, size_t counter)
{
    if (NULL == head)
    {
        return 0;
    }

    return Counter(head->child[BEFORE], counter) + 
        Counter(head->child[AFTER], counter) + 1; 
}

int ForEachRecursive(avl_node_t *head, avl_action_func_t func, void *param)
{
    int status = 0;

    if (NULL == head)
    {
        return 0;
    }
    
    status = ForEachRecursive(head->child[BEFORE], func, param);
    status += func(head->data, param);
    status += ForEachRecursive(head->child[AFTER], func, param);

    return status;
}

void *FindElement(avl_node_t *head, avl_is_before_t func, const void *data)
{
    if (NULL == head)
    {
        return NULL;
    }
    
    if (1 == func(data, head->data, NULL))
    {
         return FindElement(head->child[BEFORE], func, data);
    }
    else if (1 == func(head->data, data, NULL))
    {
        return FindElement(head->child[AFTER], func, data);
    }
    
    return head->data;
}

/*-----------------------------Balance tree funcs-----------------------------*/
/**********************
 *  Balance funcs     *
**********************/
int GetBalanceFactor(avl_node_t *root)
{
    int before_height = 0;
    int after_height = 0;

    if (NULL == root)
    {
        return 0;
    }

    before_height = (NULL == root->child[BEFORE]) ? 0 : root->child[BEFORE]->height;
    after_height = (NULL == root->child[AFTER]) ? 0 : root->child[AFTER]->height;

    return before_height - after_height;
}

static void UpdateHeight(avl_node_t *head)
{
    size_t bef_ht = 0, aft_height = 0;

    if (NULL == head)
    {
        return;
    }
    
    bef_ht = (NULL != head->child[BEFORE]) ? head->child[BEFORE]->height : 0;
    aft_height = (NULL != head->child[AFTER]) ? head->child[AFTER]->height : 0;
    
    head->height = (bef_ht < aft_height) ? 1 + aft_height : 1 + bef_ht;
}

avl_node_t *GetMaxNode(avl_t *tree)
{
    if (AVLIsEmpty(tree))
    {
        return NULL;
    }
    
    return GetLOCALMaxNode(tree->root);
}

avl_node_t *GetMinNode(avl_t *tree)
{
    if (AVLIsEmpty(tree))
    {
        return NULL;
    }
    
    return GetLOCALMinNode(tree->root);
}

avl_node_t *GetLOCALMaxNode(avl_node_t *head)
{
    if (NULL == head->child[AFTER])
    {
        return NULL;
    }
    
    return GetLOCALMaxNode(head->child[AFTER]);
}

avl_node_t *GetLOCALMinNode(avl_node_t *head)
{
    if (NULL == head->child[BEFORE])
    {
        return NULL;
    }
    
    return GetLOCALMinNode(head->child[BEFORE]);
}

static int IsMatch(const avl_t *tree ,const void *data1, const void *data2)
{
    return (!tree->is_before(data1, data2, tree->param)) && 
        (!tree->is_before(data2, data1, tree->param));
}

/**********************
 *  ROTATORS          *
**********************/
static avl_node_t* RightRotate(avl_node_t *node)
{
    avl_node_t *parent = NULL;

    parent = node->child[BEFORE];
    node->child[BEFORE] = parent->child[AFTER];
    parent->child[AFTER] = node;
/* 
    UpdateHeight(node);
    UpdateHeight(parent); */
  
    return parent; 
}

static avl_node_t* LeftRotate(avl_node_t *node)
{
    avl_node_t *parent = NULL;

    parent = node->child[AFTER];
    node->child[AFTER] = parent->child[BEFORE];
    parent->child[BEFORE] = node;
    
   /*  UpdateHeight(node);
    UpdateHeight(parent); */
  
    return parent; 
}

/*--------------------------------Node module---------------------------------*/
/**********************
 *  Node funcs        *
**********************/
static avl_node_t *NodeCreate(void *data)
{
    avl_node_t *node = NULL;

    node = malloc(sizeof(*node));
    if (NULL == node)
    {
        return NULL;
    }
    
    node->child[0] = NULL;
    node->child[1] = NULL;
    node->data = data;
    node->height = 1;

    return node; 
}

void NodeFree(avl_node_t *head)
{
    if(NULL == head)
    {
        return;
    }

    NodeFree(head->child[BEFORE]);
    NodeFree(head->child[AFTER]);
    free(head);
}

void NodeDataSwap(avl_node_t *node1, avl_node_t *node2)
{
    void *temp = NULL;
    
    temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}