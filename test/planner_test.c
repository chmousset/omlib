/**
 * OMLib, Open Motion Library
 * 
 * Copyright (C) 2013 Charles-Henri Mousset
 * 
 * This file is part of OMLib.
 * 
 * OMLib is free software: you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * OMLib is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * See the GNU Lesser General Public License for more details. You should have received a copy of the GNU
 * General Public License along with OMLib. If not, see <http://www.gnu.org/licenses/>.
 * 
 * Authors: Charles-Henri Mousset
 */

#include <stdio.h>
#include <stdlib.h>
#include "planner.h"

// gcc planner_test.c planner.c -o planner_test -I ./

int main()
{
	struct queue_t queue1;
	
	queue_init(&queue1);
	
	char str1[] = "string1", str2[] = "string2", str3[] = "string3";
	struct job_t job1 = { .next = NULL, .size=8, .type=1, .data = str1};
	struct job_t job2 = { .next = NULL, .size=8, .type=2, .data = str2};
	struct job_t job3 = { .next = NULL, .size=8, .type=3, .data = str3};
	
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
	r = queue_push(&job3, &queue1);
	printf("pushed job 3; return %i\r\n", r);
	queue_pop(job, &queue1);
	printf("queue has %i items, popped '%s' from address %p\r\n",	 queue1.size ,job->data, job);
	
	return 0;
}
