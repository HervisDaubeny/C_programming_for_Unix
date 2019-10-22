#include <stdio.h>
#include "libfac.h"

void print_factorials(int range) {

	int value = 1;

	for (size_t s = 1; s < (size_t) range + 1; s++) {

		value *= s;

		printf("%d ", value);                                
	}                                                            

	printf("\n");
}   
