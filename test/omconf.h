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

#ifndef OMCONF_H_
#define OMCONF_H_

/** 4 gives good results, straight lines are 0.23% too small and half-circle are 0.02% too small.
 * As it is only used for speed control, this is largely sufficient.
 */
#define LOOKUP_OVERSAMPLING		4


#endif /* OMCONF_H_ */
