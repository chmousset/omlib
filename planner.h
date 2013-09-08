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

#endif
