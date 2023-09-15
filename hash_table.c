#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct entry entry_t;

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t *buckets[17];
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
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  for (int i = 0; i < 17; i++) {
    result->buckets[i] = entry_create(0, NULL, NULL);
  }
  return result;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
  // TODO 
  for (int i = 0; i < 17; i++) {
    entry_destroy(ht->buckets[i]);
  }
  free(ht);
}

// vi börjar med NULL 0 så vi måste gå på först
static entry_t *find_previous_entry_for_key(entry_t **entry, int key) {
  entry_t *t1 = (*entry)->next;
  if (t1 == NULL) {
    return *entry;
  } else if (t1->key >= key) {
    return *entry;
  } else {
    return find_previous_entry_for_key(&t1, key);
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
  int bucket = key % 17;
  /// Search for an existing entry for a key
  // TODO &ht
  entry_t *entry = find_previous_entry_for_key(&((*ht).buckets[bucket]), key);
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

/*
typedef union {
  bool success;
  char *value;
} option_t;
*/

typedef struct option option_t;

struct option
{
  bool success;
  char *value;
};


option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  /// Find the previous entry for key
  entry_t *tmp = find_previous_entry_for_key(&ht->buckets[key % 17], key);
  entry_t *next = tmp->next;

  if (next && next->value)
  {
    return (option_t) { .success = true, .value = next->value };
  }
else
  {
    return (option_t) { .success = false };
  }
}


