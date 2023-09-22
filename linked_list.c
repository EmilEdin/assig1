#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "string.h"
typedef int elem_t;

struct list 
{
  elem_t element;
  ioopm_list_t *next;
};


ioopm_list_t *ioopm_linked_list_create(void)
{
    ioopm_list_t *new_link = calloc(1, sizeof(ioopm_list_t));
    new_link->element = 0;
    new_link->next = NULL;
    return new_link;
}

<<<<<<< HEAD
void ioopm_linked_list_destroy(ioopm_list_t *list)
{
=======

void ioopm_linked_list_destroy(ioopm_list_t *list) {
>>>>>>> dba00205790e0526a78b8f6a47ae36bf2b06e6e9
    ioopm_list_t *next = list->next;
    free(list);
    if (next != NULL) {
        ioopm_linked_list_destroy(next);
    }
}
void ioopm_linked_list_append(ioopm_list_t *list, int value)
{
    ioopm_list_t *new_link = ioopm_linked_list_create();
    new_link->element = value;
    new_link->next = NULL;
    ioopm_list_t *next_l = list;

    // Byt till size of list senare
    while (next_l->next != NULL) {
        next_l = next_l->next;
    }
    next_l->next = new_link;
}

void ioopm_linked_list_prepend(ioopm_list_t **list, int value)
{
    ioopm_list_t *new_link = ioopm_linked_list_create();
    new_link->element = value;
    new_link->next = *list; 
    *list = new_link;
}
<<<<<<< HEAD
=======

>>>>>>> dba00205790e0526a78b8f6a47ae36bf2b06e6e9
/*
void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value)
{
    ioopm_list_t *new_link = ioopm_linked_list_create();
    new_link->element = value;
    ioopm_list_t *next_l = list;
    if (index == 0) {
        new_link->next = next_l;
    } else if (index )
    
    }else {
        do {
            next_l = next_l->next;
        }
        while(index != 0);
        new_link->next = next_l;
    }
}
*/