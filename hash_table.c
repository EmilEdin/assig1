#include "hash_table.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "string.h"

#define No_Buckets 17


typedef struct entry entry_t;

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t *buckets[No_Buckets];
};


static entry_t *entry_create(int key, char *value, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t)); // Allocate memory for the entry
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;
  return new_entry;
}

void entry_destroy(entry_t *entry) {
  // Cache the next pointer
  entry_t *next = entry->next;
  free(entry);
  if (next != NULL) {
    entry_destroy(next);
  }
}

ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate space for a ioopm_hash_table_t = No_Buckets pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  for (int i = 0; i < No_Buckets; i++) {
    result->buckets[i] = entry_create(0, NULL, NULL);
  }
  return result;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
  // TODO 
  for (int i = 0; i < No_Buckets; i++) {
    entry_destroy(ht->buckets[i]);
  }
  free(ht);
}

// vi börjar med NULL 0 så vi måste gå på först
static entry_t *find_previous_entry_for_key(entry_t *entry, int key) {
  entry_t *t1 = entry->next;
  if (t1 == NULL) {
    return entry;
  } else if (t1->key >= key) {
    return entry;
  } else {
    return find_previous_entry_for_key(t1, key);
  }
}

/*
static entry_t *find_previous_entry_for_key(entry_t **entry, int key) {
  entry_t *t1 = (*entry)->next;
  if (t1 == NULL) {
    return *entry;
  } else if (t1->key > key) {
    return *entry;
  } else {}
  entry_t *temp_entry = find_previous_entry_for_key(&t1, key);
  return temp_entry;
}


static entry_t *find_previous_entry_for_key(entry_t **entry, int key) {
  entry_t *t1 = (*entry)->next;
  while (t1 != NULL) {
    if (t1->key > key) {
      break;
    } else {
      t1 = t1->next;
    }
  }
  return *entry;
}
*/


void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  
  /// Calculate the bucket for this entry
  int bucket = abs(key) % No_Buckets;
  /// Search for an existing entry for a key
  // TODO &ht
  entry_t *entry = find_previous_entry_for_key((*ht).buckets[bucket], key);
  entry_t *next = entry->next;

  /// Check if the next entry should be updated or not
  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
    }
}


typedef struct option ioopm_option_t;

struct option
{
  bool success;
  char *value;
};


ioopm_option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  /// Find the previous entry for key
  entry_t *tmp = find_previous_entry_for_key(ht->buckets[abs(key) % No_Buckets], key);
  entry_t *next = tmp->next;

  if (next && next->value)
  {
    return (ioopm_option_t) { .success = true, .value = next->value };
  }
else
  {
    return (ioopm_option_t) { .success = false };
  }
}

ioopm_option_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)
{
  /// Find the previous entry for key
  entry_t *tmp = find_previous_entry_for_key(ht->buckets[abs(key) % No_Buckets], key);
  entry_t *next = tmp->next;
  ioopm_option_t options = { .success = true, .value = next->value};

  if (next && next->value)
  {
    tmp->next = next->next;
    free(next);
    return options;
  }
  else
  {
    return options;
  }
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht) {
  size_t counter = 0;
  for (int i = 0; i < No_Buckets; i++) {
    entry_t *t = ht->buckets[i];
      while (t->next != NULL) {
        counter = counter + 1;
        t = t->next;
      }
  }
  return counter;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  for (int i = 0; i < No_Buckets; i++) {
    if (ht->buckets[i]->next != NULL) {
      return false;
    }
  }
  return true;
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht) 
{
  for (int i = 0; i < No_Buckets; i++) {
    entry_t *t = ht->buckets[i]->next;
    if (t != NULL)
    {
      entry_destroy(t);
      ht->buckets[i]->next = NULL;
    }
  }
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  size_t size = ioopm_hash_table_size(ht);
  ioopm_list_t  *new_list = ioopm_linked_list_create();
  int counter = 0;
  
  for (int i = 0; i < No_Buckets; i++) {
    entry_t *t = ht->buckets[i]->next;
    while (t != NULL) {
      ioopm_linked_list_append(new_list, t->key);
      t = t->next;
    }
  }
  
  return new_list;
}


char **ioopm_hash_table_values(ioopm_hash_table_t *ht) 
{
  size_t size = ioopm_hash_table_size(ht);
  char **arr = calloc(1, (sizeof(char*)*size) + sizeof(char*));
  int counter = 0;
  for (int i = 0; i <= No_Buckets; i++) {
    entry_t *t = ht->buckets[i]->next;
    while (t != NULL) {
      arr[counter] = t->value;
      counter++;
      t = t->next;
    }
  }
  arr[counter] = NULL;
  return arr;
}



static bool key_equiv(int key, char *value_ignored, void *x)
{
  int *other_key_ptr = x;
  int other_key = *other_key_ptr;
  return key == other_key;
}

static bool value_equiv(int key_ignored, char *value, void *x)
{
  char *other_value_ptr = x;
  char *other_value = other_value_ptr;
  return strcmp(value, other_value) == 0;
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
{
  size_t size = ioopm_hash_table_size(ht);
  int *arr_k = ioopm_hash_table_keys(ht);
  char **arr_v = ioopm_hash_table_values(ht);
  for (int i = 0; i < size; i++) {
    if (!pred(arr_k[i], arr_v[i], arg)) {
      free(arr_k);
      free(arr_v);
      return false;   
    }
  } 
  free(arr_k);
  free(arr_v);
  return true;
}


bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
{
  size_t size = ioopm_hash_table_size(ht);
  int *arr_k = ioopm_hash_table_keys(ht);
  char **arr_v = ioopm_hash_table_values(ht);
  for (int i = 0; i < size; i++) {
    if (pred(arr_k[i], arr_v[i], arg)) {
      free(arr_k);
      free(arr_v);
      return true;  
    }
  } 
  free(arr_k);
  free(arr_v);
  return false;
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, int key) {
  return ioopm_hash_table_any(ht, key_equiv, &key);
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, char *value) {
  return ioopm_hash_table_any(ht, value_equiv, value);
}


void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg)
{
  size_t size = ioopm_hash_table_size(ht); 
  int *arr_k = ioopm_hash_table_keys(ht);
  char **arr_v = ioopm_hash_table_values(ht);
  for (int i = 0; i < size; i++) {
    apply_fun(arr_k[i], arr_v, arg);
  }
  free(arr_k);
  free(arr_v);
}