#include <stdio.h>

void func (char **);

int main(int argc, const char *argv[]) {

	/* for cycle based print */
	for (int i = 0; i < argc; i++)
		printf("%s ", argv[i]);

	printf("\n");

	/* while based print */
	int i = 0;
	
	while (i < argc) {

		printf("%s ", argv[i]);
		i++;
	}

	printf("\n");

	/* recursive print */
	func((char **)argv);

	printf("\n");

	return 0;
}

void func (char **argv) {

	if (*argv != NULL) {

		printf("%s ", *argv);
		func((char **)++argv);
	}
}
