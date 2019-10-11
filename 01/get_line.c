#include <stdio.h>
#include <stdlib.h>

/*
 * Program meant to demonstrate correct usage of function getline.
 */

int main() {

    char * input = NULL;
    size_t buffer = 0;

    getline(&input, &buffer, stdin);

    printf("%s on %p\n", (char *)input, input);

    return 0;
}