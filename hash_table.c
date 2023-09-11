#include "hash_table.h"
#include <stdio.h>

ioopm_hash_table_t *ioopm_hash_table_create(void) {
 // TODO: Stub
  return NULL;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
  // TODO: Stub
 return;
}

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

ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to entry_t's
  ioopm_hash_table_t *result = malloc(sizeof(ioopm_hash_table_t));
  /// Initialise the entry_t pointers to NULL
  for (int i = 0; i < 17; ++i)
    {
      result->buckets[i] = NULL;
    }
  return result;
}