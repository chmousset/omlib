
#include <stdio.h>
#include "planner.h"

// gcc planner_test.c planner.c -o planner_test -I ./

int main()
{
	struct queue_t queue1;
	
	queue_init(&queue1);
	
	char str1[] = "string1", str2[] = "string2", str3[] = "string3";
	struct job_t job1 = { .header = {.next = NULL, .size=8, .type=1}, .data = str1};
	struct job_t job2 = { .header = {.next = NULL, .size=8, .type=2}, .data = str2};
	struct job_t job3 = { .header = {.next = NULL, .size=8, .type=3}, .data = str3};
	
	int r = queue_push(&job1, &queue1);
	printf("pushed job 1; return %i\r\n", r);
	
	r = queue_push(&job2, &queue1);
	printf("pushed job 2; return %i\r\n", r);
	
	struct job_t *job = queue_pop_nocopy(&queue1);
	while ( job != NULL)
	{
		printf("queue has %i items, popped '%s' from address %p\r\n", queue1.size ,job->data, job);
		job = queue_pop_nocopy(&queue1);
	}
	
	job = (struct job_t *) malloc(256);
	queue_push(&job3, &queue1);
	queue_pop(job, &queue1);
	printf("queue has %i items, popped '%s' from address %p\r\n",	 queue1.size ,job->data, job);
	
	return 0;
}