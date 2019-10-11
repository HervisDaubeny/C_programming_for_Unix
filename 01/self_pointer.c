#include "stdio.h"

int main() {

	void *ptr;
	ptr = &ptr;

	printf("%p %p\n", ptr, &ptr);
	
	return 0;
}
