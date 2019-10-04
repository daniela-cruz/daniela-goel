#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */

#include "queue.h"

typedef struct node q_node_t;

struct node
{
	void *data;
	q_node_t *next;
};

struct queue
{
	q_node_t *front;
	q_node_t *back;
	size_t size;
};

queue_t *QueueCreate()
{
	queue_t *new_queue = malloc(sizeof(queue_t *));
	
	if (NULL == new_queue)
	{
		perror("QueueCreate, new queue ");
	}
	
	new_queue->front = malloc(sizeof(q_node_t *));
	
	if (NULL == new_queue->front)
	{
		perror("QueueCreate, front node ");
	}
	
	new_queue->back = malloc(sizeof(*(new_queue->back)));
	
	if (NULL == new_queue->back)
	{
		perror("QueueCreate, back node ");
	}
	
	new_queue->size = 0;
	(new_queue->front)->next = new_queue->back;
	(new_queue->back)->next = new_queue->front;
	
	return new_queue;
}

int QueueEnqueue(queue_t *queue, void *data)
{
	q_node_t *new_node = NULL;
	q_node_t *temp = NULL;
	
	new_node = malloc(sizeof(q_node_t *));
	
	if (NULL == new_node)
	{
		perror("QueueEnqueue, new node ");
		
		return FAILURE;
	}
	
	temp = queue->back->next;
	temp->next = new_node;
	new_node->data = data;
	new_node->next = queue->back;
	queue->back->next = new_node;
	queue->size++;
	
	return SUCCESS;
}

void *QueueDequeue(queue_t *queue)
{
	q_node_t *temp = (queue->front)->next;
	void *data = temp->data;
	
	(queue->front)->next = temp->next;
	
	free(temp);
	queue->size--;
	
	return data;
}

int QueueIsEmpty(const queue_t *queue)
{
	return queue->size == 0;
}

void *QueuePeek(const queue_t *queue)
{
	return ((queue->front)->next)->data;
}

size_t QueueCount(const queue_t *queue)
{
	return queue->size;
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	q_node_t *temp = (dest->back)->next;
	
	temp->next = (src->front)->next;
	((src->back)->next)->next = dest->back;
	dest->size += src->size; 
	
	(src->back)->next = src->front;
	(src->front)->next = src->back;
	src->size = 0;
	
	return dest;
}

void QueueDestroy(queue_t *queue)
{
	while((queue->front)->next != queue->back)
	{
		QueueDequeue(queue);
	}
	
	free(queue->front);
	free(queue->back);
	
	free(queue);
}

