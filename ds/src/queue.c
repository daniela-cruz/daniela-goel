#include <stdio.h> /* perror */
#include <stdlib.h> /* malloc, realloc */
#include <stddef.h> /* size_t */

#include "queue.h" /* queue_t */

typedef struct node q_node_t;

struct node
{
	void *data ;
	q_node_t *next;
};

struct queue
{
	size_t size;
	q_node_t *front;
	q_node_t *back;
} q;

queue_t *QueueCreate()
{
	queue_t *new_queue = NULL;
	q_node_t *n_front = NULL, *n_back = NULL;
	
	new_queue = malloc(sizeof(q_node_t *));
	
	if (!new_queue)
	{
		perror("QueueCreate ");
		return NULL;
	}
	
	n_front = malloc(sizeof(q_node_t *));
	
	if (!n_front)
	{
		perror("QueueCreate ");
		return NULL;
	}
	
	n_front->next = NULL;
	n_front->data = NULL;
    new_queue->front = n_front;
    
	n_back = malloc(sizeof(q_node_t *));
	
	if (!n_back)
	{
		perror("QueueCreate ");
		return NULL;
	}
	
	n_back->data = NULL;
    new_queue->back = n_back; 
    new_queue->size = 0;
	
	return new_queue;
}

void QueueDestroy(queue_t *element)
{
	free(element);
}

int QueueEnqueue(queue_t *queue_1, void *new_data)
{
	q_node_t *temp = malloc(sizeof(q_node_t));
	q_node_t *back_cpy = queue_1->back->next;
	
    if (!temp)
	{
		return FAILURE;
	}
	
	if (NULL == queue_1->front)
	{
		queue_1->front->next = temp;
	}
	
    temp->data = new_data; 
    temp->next = back_cpy;
	queue_1->back = temp;
    queue_1->size++;
    
    return SUCCESS;
}

queue_t *QueueDequeue(queue_t *element)
{
	q_node_t *temp = NULL;
	
	temp = element->front->next->next;
	free(element->front->next); element->front->next = NULL;
	element->size--;
	element->front = temp;
	
	return element;
}

int QueueIsEmpty(const queue_t *element)
{
	return element->size == 0;
}

queue_t *QueuePeek(const queue_t *element)
{
	return (queue_t *)element->front->next;
}

size_t QueueCount(const queue_t *first);

queue_t *QueueAppend(queue_t *queue1, queue_t *queue2);
