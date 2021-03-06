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

#ifndef BEZIER_H
#define BEZIER_H


#include "omconf.h"

/**
 * @brief   t-lenght lookup table depth
 * @details Depth of the lookup table that contains lenght of the bezier curve
 */
#if !defined(T_LOOKUP_DEPTH) || defined(__DOXYGEN__)
#define T_LOOKUP_DEPTH			8
#endif

/**
 * @brief   Max number of axis
 * @details The bezier curves will have MAX_AXIS polynomes of degree 3
 */
#if !defined(MAX_AXIS) || defined(__DOXYGEN__)
#define MAX_AXIS				2			//<! maximum number of axis a bezier can have
#endif

/**
 * @brief   supersampling of the curve's lenght
 * @details The lenght is integrated over LOOKUP_OVERSAMPLING*T_LOOKUP_DEPTH samples.
 * This increases the precision of the t-lenght table's values
 */
#if !defined(LOOKUP_OVERSAMPLING) || defined(__DOXYGEN__)
#define LOOKUP_OVERSAMPLING		8
#endif

// defines for vectors
#define VEC_TAN					0
#define VEC_ACC					1

#if !defined(max)
#define max(a,b) ( a > b ? a : b )
#endif

/**
 * @brief   single axis Bezier curve parameters
 * @details A multi-axis curve parameter structure is splitted into multiple 
 * ::bezierx_t for dispatching.
 * This gives one of the coordinate of a point of the curve.
 */
struct bezierx_t {
	float x[4];
	float cc[4];
	float speed_in;
	float speed_out;
};

/**
 * @brief   multi axis Bezier curve parameters
 * @details x[][] contains the polynimial coefficients; and cc[][] contains the 
 * coefficients in another form, more practical for efficient calculation of the
 * coordinates of the points of the curve.
 */
struct bezier_t {
	float x[4][MAX_AXIS];
	float cc[4][MAX_AXIS];
	float speed_max;
	float acc_max;
};


/**
 * @brief   t-lenght lookup table
 * @details dat[i][1] contains the lenght of the curve at (t = dat[i][0])
 */
typedef struct tlookup_t{
	float dat[T_LOOKUP_DEPTH][2];
} tlookup_t;


typedef float vector_t[MAX_AXIS];
typedef float point_t[MAX_AXIS];





/**
 * @brief   Calculate ab vector
 * @details @param[in] a is the first point
 * @param[in] b is the final point
 * @param[out] c is the output vector from a to b
 */
void vector_from_points(float *c, float *a, float *b);


/**
 * @brief complexity of a bezier curve
 * @details compute the complexity criteria. It is simply the sum of dot-products.
 * This value is meant to determine if a curve must be subdivided or not.
 * The higher the value, the more the curve has potentially sharp turns and 
 * multiple cusps
 */
float b_complexity(struct bezier_t *c);


/**
 * @brief Cut a bezier curve in two smaller pieces.
 * @details The resulting bezier curve feature simplified shape, much easier to process
 * The initial curve is not modified
 * out_l[0] is followed by out_l[1], so out_l[0] is the starting curve
 * NOTE: c-params have to be calculated prior to use this function!
 */
int b_divide(struct bezier_t *out_l, struct bezier_t *in);


/**
 * @brief calculate the c-params that are used for the curve points calculation
 */
void b_calc_cparams(struct bezier_t *c);


/**
 * @brief calculate a point's position at t on bezier curve
 */
void b_calc_point(float *coord, struct bezier_t *c, float t);


/**
 * @brief calculate a point's position at t on bezier curve (single axis version)
 */
void b_calc_point_single(float *coord, struct bezierx_t *c, float t);


/**
 * @brief calculate the tangent vector to the curve at t, and the acceleration vector
 */
void b_calc_vectors(float *tan, float *acc, struct bezier_t *c, float t);


/**
 * @brief calculate a vector's lenght
 */
float b_calc_vector_lenght(float *vec);


float b_create_lookup_table(struct bezier_t *curve, tlookup_t *l);


/**
 * @brief split a struct bezier_t in a struct bezierx_t
 * @param[in] axis axis number, 0 to (MAX_AXIS-1)
 * @param[in] in multi-axis curve data structure
 * @param[in] out single-axis curve data structure
 */
void b_split(int axis, struct bezierx_t *out, struct bezier_t *in);


/**
 * @brief split a struct bezier_t in a multiple struct bezierx_t
 * @param[in] in multi-axis curve data structure
 * @param[in] out single-axis curve data structure array, MAX_AXIS elements
 */
void b_split_all(struct bezierx_t *out, struct bezier_t *in);



void mp_calc_vector_max_speed(struct bezier_t * curve, float max_speed, float max_acc);

#endif
