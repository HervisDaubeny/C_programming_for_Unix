#include <stdio.h>
#include <stdlib.h>

typedef struct list_elements {
    
    char *value;
    struct list_elements *next;
} list_element;

list_element * add_item(list_element *, char *);
void print_list(list_element *);
void free_list(list_element *);

int main(int argc, char **argv) {

    list_element * head = NULL;

    for (size_t i = 1; i < (size_t)argc; i++) {

        head = add_item(head, argv[i]);
    }

    print_list(head);

    free_list(head);

    return 0;
}

list_element * add_item(list_element *head, char *arg_value) {

    list_element *trailing = malloc(sizeof(list_element));
    list_element *new = malloc(sizeof(list_element));
    new ->value = arg_value;
    new ->next = NULL;

    /*
     * The function checks the value passed in head.
     *      If == NULL, it knows that there the head does not exist, so it
     * creates and returns it.
     */
    if (head == NULL) {

        free(trailing);

        return new;
    }
    
    /*
     * The function acceses the last item following the head and adds new item.
     */
    trailing = (list_element*)head;
    
    while (trailing ->next != NULL) {

        trailing = trailing ->next;
    }
    
    trailing ->next = (list_element*)new;

    return head;
}

void print_list(list_element * head) {

    list_element * trailing = malloc(sizeof(list_element));

    trailing = (list_element *)head;

    while (trailing != NULL) {

        printf("%s\n", trailing ->value);

        trailing = (list_element *)trailing ->next;
    }
}
void free_list(list_element * head) {

    list_element * trailing = malloc(sizeof(list_element));
    list_element * new_head = malloc(sizeof(list_element));

    trailing = (list_element *)head;

    while (trailing != NULL) {

        new_head = (list_element *) trailing -> next;
        
        free(trailing);
        trailing = (list_element *)new_head;
    }
}