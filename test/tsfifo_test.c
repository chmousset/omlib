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
#include <stdio.h>
#include "tsfifo.h"

int main()
{
	char buffer[32] = "hello";
	struct tsfifo_t fifo1;
	int i=0;
	
	tsfifo_init(&fifo1);
	
	fifo1.size = 16;			// 16 elements can be stored
	fifo1.el_size = 32;			// elements are 32 byte wide
	fifo1.data = malloc(fifo1.size * fifo1.el_size);	// create the data array
	
	printf("FIFO : size %d, %d used, %d free\n", fifo1.size, tsfifo_size(&fifo1), tsfifo_free(&fifo1));
	
	while (tsfifo_pop(&fifo1, (void*) buffer) > 0)
		printf("popping element from FIFO, stored %d, available %d, data popped: %s\n", tsfifo_size(&fifo1), tsfifo_free(&fifo1), buffer);
	
	while (tsfifo_free(&fifo1) > 0)
	{
		sprintf(buffer, "string %d", i);
		printf("push element into FIFO, stored %d, available %d, data pushed: \"%s\" \n",
			   tsfifo_size(&fifo1),
			   tsfifo_free(&fifo1),
			   buffer);
		tsfifo_push(&fifo1, buffer);
		i++;
	}
	
	while (tsfifo_pop(&fifo1, (void*) buffer) >= 0)
		printf("popping element from FIFO, stored %d, available %d, data popped: \"%s\"\n",
			   tsfifo_size(&fifo1),
			   tsfifo_free(&fifo1),
			   buffer);
	
	return 0;
}