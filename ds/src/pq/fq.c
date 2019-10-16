#include <stdio.h>  /* perror */
#include <stdlib.h> /* malloc, free */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "fq.h"

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
	queue_t *new_queue = NULL;
	
	new_queue  = malloc(sizeof(*new_queue));
	if (NULL == new_queue)
	{
		perror("QueueCreate, new queue ");
		return NULL;
	}
	
	new_queue->front  = malloc(sizeof(*new_queue->front));
	if (NULL == new_queue->front)
	{
		perror("QueueCreate, front node ");
		free(new_queue);
		return NULL;
	}
	
	new_queue->back = malloc(sizeof(*new_queue->back));
	if (NULL == new_queue->back)
	{
		perror("QueueCreate, back node ");
		free(new_queue); free(new_queue->front);
		return NULL;
	}
	
	new_queue->size = 0;
	new_queue->front->next = new_queue->back;
	new_queue->back->next = new_queue->front;
	
	return new_queue;
}

void QueueDestroy(queue_t *queue)
{
	assert(NULL != queue);
	
	for (; 	0 < queue->size; )
	{
		QueueDequeue(queue);
	}
	
	free(queue->front);
	free(queue->back);
	
	free(queue);
}

int QueueEnqueue(queue_t *queue, void *data)
{
	q_node_t *new_node = NULL;
	q_node_t *temp = NULL;
	
	assert(NULL != queue); 
	assert(NULL != data);
	
	new_node = malloc(sizeof(* temp));
	
	if (NULL == new_node)
	{
		perror("QueueEnqueue, new node ");
		
		return FAILURE;
	}
	
	queue->back->next->next = new_node;
	new_node->data = data;
	new_node->next = queue->back;
	queue->back->next = new_node;
	queue->size++;
	
	return SUCCESS;
}

void *QueueDequeue(queue_t *queue)
{
	q_node_t *temp = NULL;
	void *temp2 = NULL;
	
	assert(NULL != queue);
	
	temp2 = queue->front->next->data;
	temp = queue->front->next;
	queue->front->next = temp->next;
	free(temp); 
	queue->size--;
	
	if (queue->front->next == queue->back)
	{
		queue->back->next = queue->front;
	}
	
	return temp2;
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
	
	return 0 == queue->size;
}

void *QueuePeek(const queue_t *queue)
{
	assert(NULL != queue);
	
	return queue->front->next->data;
}

size_t QueueCount(const queue_t *queue)
{
	assert(NULL != queue);
	
	return queue->size;
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	/* append src queue to back of dest */
	dest->back->next->next = src->front->next;
	dest->size += src->size; 
	
	/* nullify appended src queue container */
	src->back->next = src->front;
	src->front->next = src->back;
	src->size = 0;
	
	return dest;
}

