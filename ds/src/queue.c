#include <stdio.h> /* malloc, realloc */
#include <stddef.h> /* size_t */

#include "queue.h" /* queue_t */

struct queue
{
	size_t size;
	void *front;
	void *back;
};

typedef struct node q_node_t;
struct node
{
	void *item ;
	q_node_t *prev_;
	q_node_t *next;
} node_t;

queue_t *QueueCreate()
queue_t *new_queue = NULL;
{
	sll_node_t *new_node = NULL;
	
	new_node = malloc(sizeof(sll_node_t *));
	
	if (!new_node)
	{
		perror("QueueCreate ");
		return NULL;
	}
	
	
	
	return new_queue;
}

void QueueDestroy(queue_t *element)
{
	free();
}

queue_t *QueueEnqueue(queue_t *first, void *data);

queue_t *QueueDenqueue(queue_t *element);

int QueueIsEmpty(queue_t *element);

queue_t *QueuePeek(queue_t *element, size_t n);

size_t QueueCount(queue_t *first);

queue_t *QueueAppend(queue_t *queue1, queue_t *queue2);
