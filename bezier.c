
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "bezier.h"

void vector_from_points(float *c, float *a, float *b)
{
	int i;
	for(i=0; i< MAX_AXIS; i++)
		c[i] = b[i] - a[i];
}


float b_complexity(struct bezier_t *c)
{
	float la03, criteria;
	vector_t a03_v, v;
	int i;
	
	vector_from_points(a03_v, c->x[3], c->x[0]);	// create vector a0a1
	la03 = b_calc_vector_lenght(a03_v);				// lenght of vector a0a3
	
}


int b_divide(struct bezier_t *out_l, struct bezier_t *in)
{
	int i;
	float a12[MAX_AXIS];
	
	for(i=0; i < MAX_AXIS; i++)
	{
		a12[i] = (in->x[1][i] + in->x[2][i]) / 2;			// a12 = av(a1,a2)
		out_l[0].x[1][i] = (in->x[0][i] + in->x[1][i]) / 2;	// b1 = av(a0,a1)
		out_l[0].x[2][i] = (a12[i] + out_l[0].x[1][i]) / 2;	// b2 = av(a12,b1)
		out_l[1].x[2][i] = (in->x[2][i] + in->x[3][i]) / 2;	// c2 = av(a2,a3)
		out_l[1].x[1][i] = (a12[i] + out_l[1].x[2][i]) / 2;	// c1 = av(a12,c2)
		out_l[0].x[3][i] = (out_l[0].x[2][i] + out_l[1].x[1][i]) / 2;	// b3 = av(b2,c1)
		out_l[1].x[0][i] = out_l[0].x[3][i];	// b3
		out_l[0].x[0][i] = in->x[0][i];			// a0
		out_l[1].x[3][i] = in->x[3][i];			// a3
	}
	return 2;
}


void b_calc_cparams(struct bezier_t *c)
{
	int i;
	for (i=0; i< MAX_AXIS; i++)
	{
		c->cc[0][i] = c->x[0][i];
		c->cc[1][i] = -3*c->x[0][i]+3*c->x[1][i];
		c->cc[2][i] =  3*c->x[0][i]-6*c->x[1][i]+3*c->x[2][i];
		c->cc[3][i] = -1*c->x[0][i]+3*c->x[1][i]-3*c->x[2][i]+c->x[3][i];
	}
}


void b_calc_point(float *coord, struct bezier_t *c, float t)
{
	int i;
	for (i=0; i< MAX_AXIS; i++)
	{
		coord[i] = ((c->cc[3][i] * t +c->cc[2][i])*t + c->cc[1][i]) * t + c->cc[0][i];
	}
}


void b_calc_point_single(float *coord, struct bezierx_t *c, float t)
{
	*coord = ((c->cc[3] * t +c->cc[2])*t + c->cc[1]) * t + c->cc[0];
}


void b_calc_vectors(float *tan, float *acc, struct bezier_t *c, float t)
{
	int i;
	for (i=0; i< MAX_AXIS; i++)
	{
		tan[i] = (3 * c->cc[3][i] * t + 2 * c->cc[2][i])*t + c->cc[1][i];
		acc[i] = (6 * c->cc[3][i] * t + 2 * c->cc[2][i]);
	}
}


float b_calc_vector_lenght(float *vec)
{
	int i;
	float lenght = 0.0;
	
	for(i=0; i<MAX_AXIS; i++)
		lenght += vec[i] * vec[i];
	
	return sqrtf(lenght);
}


float b_create_lookup_table(struct bezier_t *curve, tlookup_t *l)
{
	vector_t tan_v;			// t-speed (tangent) vector
	vector_t acc_v;			// t-acceleration vector
	float lenght=0.0;		// lenght of the curve, 
	float increment=0.0;	// t increment
	float step;				// t increment
	float t=0;				// t value
	float amax=0;			// maximum acceleration
	float vec_l[2];			// t-speed and t-acceleration
	int i;					// iterator integer
	float acc_max;			// maximum acceleration
	
	step = 1.0/(T_LOOKUP_DEPTH * LOOKUP_OVERSAMPLING);
	
	for (i=0; i<LOOKUP_OVERSAMPLING*T_LOOKUP_DEPTH-1; i++)
	{
#if defined(LOOKUP_OVERSAMPLING)		
		if((i % LOOKUP_OVERSAMPLING==0) && (i != 0))
		{
			l->dat[(i/LOOKUP_OVERSAMPLING) - 1][1] = lenght * step;
			l->dat[(i/LOOKUP_OVERSAMPLING) - 1][0] = t;
		}
#else
	l->dat[i] = lenght * step;
#endif
		t += step;
		b_calc_vectors(tan_v, acc_v, curve, t);
		vec_l[0] = b_calc_vector_lenght(tan_v);
		vec_l[1] = b_calc_vector_lenght(acc_v);
		acc_max = max(acc_max, abs(vec_l[1]));
		lenght += vec_l[0];
		printf("t %f tangent=[%f,%f] lenght %f\r\n", t, tan_v[0], tan_v[1], lenght * step);
		
	}
	
	// we process the last lookup value outside of the loop to execute the calculation at precisely t=1
	b_calc_vectors(tan_v, acc_v, curve, 1.0 - step);
	lenght += b_calc_vector_lenght(tan_v);
	l->dat[T_LOOKUP_DEPTH-1][1] = lenght * step;
	l->dat[T_LOOKUP_DEPTH-1][0] = 1.0;
	printf("t 1.0 tangent=[%f,%f] lenght %f\r\n", tan_v[0], tan_v[1], lenght * step);
	return lenght*step;
}


void mp_calc_vector_max_speed(struct bezier_t *curve, float max_speed, float max_acc)
{
	curve->speed_max = max_speed;
	
	// if the acceleration is superior to the maximum, then clip the speed to respect the maximum acceleration.
	if(curve->acc_max > max_acc)
	{
		curve->speed_max = curve->speed_max * max_acc / curve->acc_max; 
		curve->acc_max = max_acc;
	}
}


void b_split(int axis, struct bezierx_t *out, struct bezier_t *in)
{
	int i;
	for (i=0; i<4; i++)
	{
		out->x[i] = in->x[1][axis];
		out->cc[i] = in->cc[1][axis];
	}
}

void b_split_all(struct bezierx_t *out, struct bezier_t *in)
{
	int i;
	for (i=0; i< MAX_AXIS; i++)
		b_split(i, &out[i], in);
}


