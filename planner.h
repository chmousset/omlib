

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
