

#include <math.h>
#include <stdio.h>
#include "bezier.h"

#if !defined(PI)
#define PI (3.141592653589793)
#endif

//gcc bezier_test.c bezier.c -o bezier_test -I ./ -lm

int main()
{
	struct bezier_t line1 = { .x={
		{0,0},
		{0.5,0.5},
		{0.5,0.5},
		{1,1}}
	};
	struct bezier_t curve1 = { .x={
		{0,0},
		{0.55228475,0},
		{1,1-0.55228475},
		{1,1}}
	};
	
	tlookup_t lookup;
	float lenght;
	
	int i;
	
	// TEST1 : straight line lenght
	b_calc_cparams(&line1);
	lenght = b_create_lookup_table(&line1, &lookup);
	
	printf("The lenght of the line (0,0,1,1) is %f and the lookup table is the following:\r\n", lenght);
	printf("Exact lenght is %f ; error is %f%%\r\n", sqrtf(2.0), (100 * (lenght-sqrtf(2.0)) / sqrtf(2.0) ) );
	for(i=0; i<T_LOOKUP_DEPTH; i++)
		printf("t: %f  l: %f\r\n", lookup.dat[i][0], lookup.dat[i][1]);
	
	
	// TEST2 : Quart circle approximation
	b_calc_cparams(&curve1);
	lenght = b_create_lookup_table(&curve1, &lookup);
	
	printf("The lenght of the 1/4 circle (0,0,1,1) is %f and the lookup table is the following:\r\n", lenght);
	printf("Exact lenght is %f; error is %f%%\r\n", PI / 2, (200 * (lenght - (PI/2))/PI ) );
	for(i=0; i<T_LOOKUP_DEPTH; i++)
		printf("t: %f  l: %f\r\n", lookup.dat[i][0], lookup.dat[i][1]);
	
	// TEST3: split quart circle; process the two new polys lenghts
	struct bezier_t curve_out[2];
	tlookup_t lookup2;
	float lenght1, lenght2;
	int ret;
	
	printf("divide curve\r\n");
	ret = b_divide(curve_out, &curve1);
	b_calc_cparams(&curve_out[0]);
	b_calc_cparams(&curve_out[1]);
	
	lenght1 = b_create_lookup_table(&curve_out[0], &lookup);
	lenght2 = b_create_lookup_table(&curve_out[1], &lookup2);
	
	printf("The lenght of the 1st 1/8 circles (0,0,1,1) is %f and the lookup table is the following:\r\n", lenght1);
	for(i=0; i<T_LOOKUP_DEPTH; i++)
		printf("t: %f  l: %f\r\n", lookup.dat[i][0], lookup.dat[i][1]);
	
	printf("The lenght of the 1st 1/8 circles (0,0,1,1) is %f and the lookup table is the following:\r\n", lenght2);
	for(i=0; i<T_LOOKUP_DEPTH; i++)
		printf("t: %f  l: %f\r\n", lookup2.dat[i][0], lookup2.dat[i][1]);
	
	printf("Exact lenght is %f; error is %f%%\r\n", PI / 2, (200 * ((lenght1+lenght2) - (PI/2))/PI ) );
	
	return 0;
}
