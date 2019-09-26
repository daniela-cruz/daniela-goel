#ifndef __SLL_H__
#define __SLL_H__

typedef struct node node_t; /* void * node_t * */
typedef enum status status_t;

/* the user provides data and the function returns a pointer to the new root */
node_t *SLLCreateNode(void *data, node_t *next);

/* the user should provide a pointer to the first node (the root) of the list */
void SLLFreeAll(node_t *root);

void SLLRemove(node_t *removable_node);

void SLLRemoveAfter(node_t *removable_node);

node_t *SLLInsert(node_t *insertable_node, void *data);

node_t *SLLInsertAfter(node_t *target_node, node_t *new_node, void *data);

size_t SLLCount(const node_t *root);

status_t SLLForEach(node_t *root, /*func*/);

node_t *SLLFind(node_t *root, /*func*/);

/* returns new root ptr after flip*/
node_t *SLLFlip(node_t *root);

size_t SLLHasLoop(node_t *root);

node_t *SLLFindIntersection(node_t *root_1, node_t *root_2);


#endif /*__SLL_H__*/
