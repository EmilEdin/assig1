#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "string.h"

struct list {
    int value;
    ioopm_list_t *next;
};

ioopm_list_t *ioopm_linked_list_create(void) {
    ioopm_list_t *new_list = calloc(1, sizeof(ioopm_list_t));
    return new_list;
}

void ioopm_linked_list_destroy(ioopm_list_t *list) {
    ioopm_list_t *next = list->next;
    free(list);
    if (next != NULL) {
        ioopm_linked_list_destroy(next);
    }
}

void ioopm_linked_list_append(ioopm_list_t *list, int value) {
    
}