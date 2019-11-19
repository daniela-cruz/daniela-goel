#include "avl.h" /* avl_node_t, avl_t */

typedef struct  
{
    void *data;
    avl_node_t *before, *after;
    int balance;
}avl_node_t;

struct avl 
{
    void *tree;
    avl_is_before_func_t is_before;
    void *param;
};

/**********************
 *  FUNCTIONS         *
**********************/

/**********************
 *  ROTATORS          *
**********************/
avl_node_t *RotateLeftLeft(avl_node_t *head);
avl_node_t *RotateLeftRight(avl_node_t *head);
avl_node_t *RotateRightLeft(avl_node_t *head);
avl_node_t *RotateRightRight(avl_node_t *head);

/**********************
 *  Utilities         *
**********************/
void *GetMaxNode(avl_node_t *head);
void *GetMinNode(avl_node_t *head);
void *GetLOCALMaxNode(avl_node_t *head);
void *GetLOCALMinNode(avl_node_t *head);