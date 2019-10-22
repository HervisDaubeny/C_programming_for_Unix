#include <stdio.h>
#include "libpwr.h"

void print_powers(int range) {

	for (size_t s = 1; s < (size_t) range + 1; s++) {

		printf("%d ", (int)(s * s));                                
	}                                                            

	printf("\n");
}   
