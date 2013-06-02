

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
	
	b_calc_cparams(&line1);
	lenght = b_create_lookup_table(&line1, &lookup);
	
	printf("the lenght is %f and the lookup table is the following:\r\n", lenght);
	int i;
	for(i=1; i<T_LOOKUP_DEPTH; i++)
		printf("t: %f  l: %f\r\n", lookup.dat[i][0], lookup.dat[i][1]);
	
	return 0;
}
