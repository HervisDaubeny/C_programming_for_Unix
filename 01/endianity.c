#include <stdio.h>

int main() {

	int i = 1;
	char * ptr = (char *)&i;

	for (int i = 0; i < 4; i++) {

		printf("%x\n", (int)*ptr++);
	}

	printf("%s\n", "\nIf the output is equal to:\n1\n0\n0\n0\nthen your system uses little endianity. Big endianity in opossite case.");
	return 0;
}
