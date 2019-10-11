#define _GNU_SOURCE
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

int main() {

    char *curr = NULL;
    char *prev = NULL;
    char *buff = NULL;
    size_t line_size = 0;

    while (1) {
        
        size_t check = getline(&buff, &line_size, stdin);

        if (check == (size_t) -1) {

            break;
        }

	    free(prev);

        if (curr != NULL) {

            prev = strdup(curr);
        }
        free(curr);
        curr = strdup(buff);
    }

    if (prev == NULL) {

        printf("Ill formated / empty input.");
    }
    else {

        printf("%s\n", (char*)prev);
    }

    return 0;
}
