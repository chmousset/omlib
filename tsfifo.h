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

#ifndef TSFIFO_H_
#define TSFIFO_H_

#if !defined(TSFIFO_NOCHECK) || defined(__DOXYGEN__)
#define TSFIFO_NOCHECK	TRUE
#endif


struct tsfifo_t {
	void *data;						//!< pointer to the data array
	unsigned int size;				//!< size of the buffer (in elements)
	unsigned int el_size;			//!< size of the buffer elements
	unsigned int top;				//!< index of the top element of the FIFO
	unsigned int bot;				//!< index of the bottom element of the FIFO
};


/**
 * @brief init a tsfifo structure
 * @details the struct is initialized with 0 elements, 0 size and no data pointer
 * @param[in] fifo pointer to the fifo to init
 */
int tsfifo_init(struct tsfifo_t *fifo);


/**
 * @brief pop an element from the FIFO
 * @details If the size is != 0, copy an element from the fifo to element
 * @param[in] fifo pointer to the fifo
 * @param[in] element pointer to the element to which the data is copied
 * @return the number of elements present in the FIFO after the operation;
 * -1 means the FIFO was full and no element was copied. fifo are unchanged
 */
int tsfifo_pop(struct tsfifo_t *fifo, void * element);


/**
 * @brief push a new element to the FIFO
 * @details the element is copied into the FIFO, if room remains
 * @param[in] fifo pointer to the fifo
 * @param[in] element pointer to the element from which the data is copied
 * @return the number of elements present in the FIFO after the operation;
 * -1 means the FIFO was empty and no element was retreived. element and fifo are unchanged
 */
int tsfifo_push(struct tsfifo_t *fifo, void * element);


/**
 * @brief free elements in the FIFO
 * @param[in] fifo pointer to the fifo to init
 * @return the number of free elements in the FIFO
 */
int tsfifo_free(struct tsfifo_t *fifo);


/**
 * @brief elements present in the FIFO
 * @param[in] fifo pointer to the fifo to init
 * @return the number of elements present in the FIFO
 */
int tsfifo_size(struct tsfifo_t *fifo);

#endif
