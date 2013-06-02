
#ifndef BEZIER_H
#define BEZIER_H

#define T_LOOKUP_DEPTH			5			//<! t-lenght lookup table
#define MAX_AXIS				2			//<! maximum number of axis a bezier can have

/**
 * supersampling of the curve's lenght. The lenght is integrated over LOOKUP_OVERSAMPLING*T_LOOKUP_DEPTH samples.
 * Undefine to disable supersampling.
 */
#define LOOKUP_OVERSAMPLING		10

// defines for vectors
#define VEC_TAN					0
#define VEC_ACC					1

#if !defined(max)
#define max(a,b) ( a > b ? a : b )
#endif

/**
 * single axis Bezier curve parameters
 */
struct bezierx_t {
	float x[4];
	float cc[4];
	float speed_in;
	float speed_out;
};

/**
 * multi axis Bezier curve parameters
 */
struct bezier_t {
	float x[4][MAX_AXIS];
	float cc[4][MAX_AXIS];
	float speed_max;
	float acc_max;
};


typedef struct tlookup_t{
	float dat[T_LOOKUP_DEPTH][2];		// table containing the actual data
} tlookup_t;

typedef float vector_t[MAX_AXIS];
typedef float point_t[MAX_AXIS];





void vector_from_points(float *c, float *a, float *b);


/**
 * compute the complexity criteria. It is simply the sum of dot-products.
 * This value is meant to determine if a curve must be subdivided or not
 */
float b_complexity(struct bezier_t *c);


/**
 * Cut a bezier curve in two smaller pieces.
 * The resulting bezier curve feature simplified shape, much easier to process
 * The initial curve is not modified
 * out_l[0] is followed by out_l[1], so out_l[0] is the starting curve
 * NOTE: c-params have to be calculated!
 */
int b_divide(struct bezier_t *out_l, struct bezier_t *in);


/**
 * calculate the c-params that are used for the curve points calculation
 */
void b_calc_cparams(struct bezier_t *c);


/**
 * calculate a point's position at t on bezier curve
 */
void b_calc_point(float *coord, struct bezier_t *c, float t);


/**
 * calculate a point's position at t on bezier curve (single axis version)
 */
void b_calc_point_single(float *coord, struct bezierx_t *c, float t);


/**
 * calculate the tangent vector to the curve at t, and the acceleration vector
 */
void b_calc_vectors(float *tan, float *acc, struct bezier_t *c, float t);


/**
 * calculate a vector's lenght
 */
float b_calc_vector_lenght(float *vec);


float b_create_lookup_table(struct bezier_t *curve, tlookup_t *l);



void mp_calc_vector_max_speed(struct bezier_t * curve, float max_speed, float max_acc);

#endif