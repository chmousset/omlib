

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "planner.h"

void queue_init(struct queue_t *queue)
{
	queue->first = NULL;
	queue->last = NULL;
	queue->size = 0;
}

#if (DYNAMIC_QUEUE_SIZE == TRUE)
int queue_push_nocopy(struct job_t *job, struct queue_t *queue)
{	
	if(queue->last)
		queue->last->next = job;
	queue->last = job;
	queue->last->next = NULL;
	
	if(queue->first == NULL)
		queue->first = queue->last;
	
	++(queue->size);
	return queue->size;
}

int queue_push(struct job_t *job, struct queue_t *queue)
{
	void *data;
	int size = sizeof(struct job_t) + job->size;
	data = MEM_ALLOC(size);
	
	if (data == NULL)
		return -1;
	
	memcpy ((void *)data, (void *)job, sizeof(struct job_t));
	memcpy ((void *)data + sizeof(struct job_t), (void *)job->data, job->size);
	
	return queue_push_nocopy(data, queue);
}

struct job_t * queue_pop_nocopy(struct queue_t *queue)
{
	struct job_t * ptr;
	ptr = queue->first;
	if(ptr)
	{
		queue->first = queue->first->next;
		--(queue->size);
	}
	return ptr;
}

int queue_pop(struct job_t *job, struct queue_t *queue)
{
	struct job_t * ptr;
	
	ptr = queue_pop_nocopy(queue);
	
	if(ptr)
	{
		// by copying the job struct, we keep the original data location (as we copy it's pointer)
		memcpy((void*) job, ptr, sizeof(struct job_t));
		MEM_FREE(ptr);
		return queue->size;
	}
	return -1;
}

#else

int queue_push(struct job_t *job, struct queue_t *queue)
{
	// check if there is enough room for the job
	if ((queue->size + job->size + sizeof(struct job_t)) > QUEUE_SIZE)
		return -1;
	
	
}


struct job_t * queue_pop_nocopy(struct queue_t *queue)
{
	struct job_t *ptr;
	
	if (queue->first == NULL)
		return NULL;
	
	ptr = queue->first;
	if(queue->first != queue->last)
		queue->first = queue->first->next;
	else
		queue->first = NULL;
	return ptr;
}


int queue_pop(struct job_t *job, struct queue_t *queue)
{
	
}
#endif
