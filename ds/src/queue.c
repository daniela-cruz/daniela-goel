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
	queue_t *new_queue = NULL;
	
	if (NULL == (new_queue  = malloc(sizeof(*new_queue))))
	{
		perror("QueueCreate, new queue ");
	}
	
	if (NULL == (new_queue->front  = malloc(sizeof(*new_queue->front))))
	{
		perror("QueueCreate, front node ");
	}
	
	if (NULL == (new_queue->back = malloc(sizeof(*new_queue->back))))
	{
		perror("QueueCreate, back node ");
	}
	
	new_queue->size = 0;
	new_queue->front->next = new_queue->back;
	new_queue->back->next = new_queue->front;
	
	return new_queue;
}

void QueueDestroy(queue_t *q_element)
{
	for (; 	0 < q_element->size; )
	{
		QueueDequeue(q_element);
	}
	
	free(q_element->front);
	free(q_element->back);
	
	free(q_element); q_element = NULL;
}

int QueueEnqueue(queue_t *q_element, void *data)
{
	q_node_t *new_node = NULL;
	q_node_t *temp = NULL;
	
	new_node = malloc(sizeof(* temp));
	
	if (NULL == new_node)
	{
		perror("QueueEnqueue, new node ");
		
		return FAILURE;
	}
	
	q_element->back->next->next = new_node;
	new_node->data = data;
	new_node->next = q_element->back;
	q_element->back->next = new_node;
	q_element->size++;
	
	return SUCCESS;
}

queue_t *QueueDequeue(queue_t *q_element)
{
	q_node_t *temp = NULL;
	
	if (1 == q_element->size)
	{
		free(q_element->front->next); q_element->front->next = NULL;
		q_element->front->next = q_element->back; 
		q_element->back->next = q_element->front;
		q_element->size = 0;
	}
	
	else if (0 == q_element->size)
	{
	}
	
	else
	{
		temp = q_element->front->next;
		q_element->front->next = temp->next;
		free(temp); temp = NULL;
		q_element->size--;
	}
	
	return q_element;
}

int QueueIsEmpty(const queue_t *q_element)
{
	return 0 == q_element->size;
}

void *QueuePeek(const queue_t *q_element)
{
	return q_element->front->next->data;
}

size_t QueueCount(const queue_t *q_element)
{
	return q_element->size;
}

queue_t *QueueAppend(queue_t *dest, queue_t *src)
{
	q_node_t *temp = NULL;
	
	/* append src queue to back of dest */
	temp = dest->back->next;
	temp->next = src->front->next;
	src->back->next->next = dest->back;
	dest->size += src->size; 
	
	/* nullify appended src queue container */
	src->back->next = src->front;
	src->front->next = src->back;
	src->size = 0;
	
	return dest;
}

