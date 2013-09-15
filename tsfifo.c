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

#include <stdlib.h>
#include <string.h>
#include "tsfifo.h"

int tsfifo_init(struct tsfifo_t *fifo)
{
	#if TSFIFO_NOCHECK == FALSE
	if(fifo->data == NULL)
		return -1;
	#endif
	fifo->top = 0;
	fifo->bot = 0;
	fifo->data = NULL;
	
	return 0;
}

int tsfifo_pop(struct tsfifo_t *fifo, void * element)
{
#if TSFIFO_NOCHECK == FALSE
	if(fifo->data == NULL)
		return -1;
#endif
	if( (fifo->top == fifo->bot) )
		return -1;
	
	memcpy(element, fifo->data + fifo->el_size * fifo->bot, fifo->el_size);
	fifo->bot++;
	fifo->bot %= fifo->size;
	
	return ( (fifo->top - fifo->bot) % fifo->size);
}

int tsfifo_push(struct tsfifo_t *fifo, void * element)
{
	#if TSFIFO_NOCHECK == FALSE
	if(fifo->data == NULL)
		return -1;
	#endif
	if( (fifo->bot - fifo->top) % fifo->size == 1)
		return -1;
	
	memcpy((void*)(fifo->data + fifo->el_size * fifo->top), element, fifo->el_size);
	fifo->top++;
	fifo->top %= fifo->size;
	
	return ( (fifo->top - fifo->bot) % fifo->size);
}

int tsfifo_free(struct tsfifo_t *fifo)
{
	#if TSFIFO_NOCHECK == FALSE
	if(fifo->data == NULL)
		return -1;
	#endif
	return ( (fifo->bot - fifo->top - 1) % fifo->size);
}

int tsfifo_size(struct tsfifo_t *fifo)
{
	#if TSFIFO_NOCHECK == FALSE
	if(fifo->data == NULL)
		return -1;
	#endif
	return ( (fifo->top - fifo->bot) % fifo->size);
}
