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

#include "omconf.h"

#ifndef PLANNER_H__
#define PLANNER_H__

/**
 * @brief size of the data payload of a job element
 */
#if !defined(JOB_DATA_SIZE) || defined(__DOXYGEN__)
#define JOB_DATA_SIZE		256
#endif


/**
 * @brief Dynamic queue size
 * if TRUE, the queue memory association is dynamic.
 * It then uses chained lists and mallocs/free to push/pop jobs
 */
#if !defined(DYNAMIC_QUEUE_SIZE) || defined(__DOXYGEN__)
#define DYNAMIC_QUEUE_SIZE	TRUE
#endif


/**
 * @brief Queue size
 * if DYNAMIC_QUEU_SIZE is FALSE, determines the queue size in bytes.
 * Else, this is ignored.
 */
#if !defined(QUEUE_SIZE) || defined(__DOXYGEN__)
#define QUEUE_SIZE			1024
#endif


/**
 * @brief allocate memory from heap
 * By default, planner uses C standard malloc()
 */
#if !defined(MEM_ALLOC) || defined(__DOXYGEN__)
#define MEM_ALLOC(a)		malloc(a)
#endif


/**
 * @brief free memory from heap
 * By default, planner uses C standard free()
 */
#if !defined(MEM_FREE) || defined(__DOXYGEN__)
#define MEM_FREE(a)			free(a)
#endif


/**
 * @brief job element
 * holds the data (and its size) of the job
 */
struct job_t
{
	struct job_t *next;				//!< Next job in the cained list
	unsigned char size;				//!< Size in bytes of the data
	char type;						//!< type of job
#if defined(DYNAMIC_QUEUE_SIZE)
	char *data;
#else
	char data[JOB_DATA_SIZE];
#endif
};

struct queue_t
{
	struct job_t *first;
	struct job_t *last;
	int size;
	
#if (!DYNAMIC_QUEUE_SIZE)
	char data[QUEUE_SIZE];
#endif
};


void queue_init(struct queue_t *queue);
#if (DYNAMIC_QUEUE_SIZE == TRUE) || defined(__DOXYGEN__)
/** @ingroup planner
* @brief push a job to the top of the stack
* @details no copy version. the pointer to the job is directly saved in the queue. available in dynamic queue only.
* @param[in] *job job you want to push
* @param[in] *queue queue in which the job is added
* @return number of job in the list
*/
int queue_push_nocopy(struct job_t *job, struct queue_t *queue);


/** @ingroup planner
 * @brief push a job to the top of the stack
 * @details copies job and data in newly allocated memory
 * @param[in] *job job you want to push
 * @param[in] *queue queue in which the job is added
 * @return number of job in the list
 */
int queue_push(struct job_t *job, struct queue_t *queue);


/** @ingroup planner
 * @brief pop a job from the bottom of the stack
 * @details no copy version. passes directly the pointer to the job in the queue
 * @param[in] *queue queue in which the job is taken
 * @return pointer to the job. NULL if the queue is empty
 */
struct job_t * queue_pop_nocopy(struct queue_t *queue);


/** @ingroup planner
 * @brief pop a job from the bottom of the stack
 * @details copies the job, and the pointer to the data (data is not copied). Frees the job from the queue (but not it's data as it's used by job)
 * @param[in] *job job in which you want to copy the bottom job
 * @param[in] *queue queue in which the job is taken
 * @return size of the queue after the operation. -1 if queue is (was) empty and the operation is 	aborted
 */
int queue_pop(struct job_t *job, struct queue_t *queue);

#else // (DYNAMIC_QUEUE_SIZE == TRUE) || defined(__DOXYGEN__)

int queue_push(struct job_t *job, struct queue_t *queue);
struct job_t * queue_pop_nocopy(struct queue_t *queue);
int queue_pop(struct job_t *job, struct queue_t *queue);

#endif // (DYNAMIC_QUEUE_SIZE == TRUE) || defined(__DOXYGEN__)

#endif // PLANNER_H__