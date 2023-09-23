#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "string.h"

typedef struct link ioopm_link_t;

struct link
{
    int element;
    ioopm_link_t *next;
};

struct list
{
    ioopm_link_t *first;
    ioopm_link_t *last;
    int size; // Added field to store the number of elements in the linked list.
};

ioopm_list_t *ioopm_linked_list_create(void)
{
    ioopm_list_t *new_list = calloc(1, sizeof(ioopm_list_t));
    new_list->first = NULL;
    new_list->last = NULL;
    new_list->size = 0;
    return new_list;
}

static void links_destroy(ioopm_link_t *link) {
  // Cache the next pointer
  ioopm_link_t *next = link->next;
  free(link);
  if (next != NULL) {
    links_destroy(next);
  }
}

void ioopm_linked_list_destroy(ioopm_list_t *list) {
    if (list->first == NULL && list->last == NULL) {
        free(list);
    } else {
    links_destroy(list->first);
    free(list);
    }
}

void ioopm_linked_list_append(ioopm_list_t *list, int value)
{
    ioopm_link_t *new_link = calloc(1, sizeof(ioopm_link_t));
    
    new_link->element = value;
    new_link->next = NULL;
    // Increment size by one
    list->size = list->size + 1;
    if (list->last == NULL) {
        // TODO: ska man uppdatera first också till new_link? Svar: Det hjälper att göra så när man använder list_destroy.
        list->first = new_link;
        list->last = new_link;
    } else {
        list->last->next = new_link;
        list->last = new_link;
    }
}

void ioopm_linked_list_prepend(ioopm_list_t *list, int value)
{
    ioopm_link_t *new_link = calloc(1, sizeof(ioopm_link_t));
    new_link->element = value;
    new_link->next = list->first;
    if (list->last == NULL && list->first == NULL) {
        list->first = new_link;
        list->last = new_link;
    }
    list->first = new_link;
    // Increment size by one
    list->size = list->size + 1;
}

int ioopm_linked_list_size(ioopm_list_t *list) {
    return list->size;
}

void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value) {
    int length = ioopm_linked_list_size(list);
    int counter = 1;
    // If we insert at the head of the list
    if (index == 0) {
        ioopm_linked_list_prepend(list, value);
    // If we insert at the last element
    } else if (length == index) {
        ioopm_linked_list_append(list, value);
    } else {
        ioopm_link_t *linked_link = list->first;
        while (counter != index - 1) {
            linked_link = linked_link->next;
            counter = counter + 1;
        }
        ioopm_link_t *new_link = calloc(1, sizeof(ioopm_link_t));
        new_link->element = value;
        new_link->next = linked_link->next;
        linked_link->next = new_link;
       // Increment size by one
       list->size = list->size + 1;
    }
}


