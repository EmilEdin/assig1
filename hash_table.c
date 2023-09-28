#include "hash_table.h"
#include "common.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "string.h"
#include <stdio.h>
#define No_Buckets 17


typedef struct entry entry_t;

struct entry
{
  elem_t key;       // holds the key
  elem_t value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t *buckets[No_Buckets];
  hash_function hash_fun;
  ioopm_eq_function equal_fun;
};

 typedef struct option ioopm_option_t;

 struct option
 {
   bool success;
   elem_t value;
 };


static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
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

ioopm_hash_table_t *ioopm_hash_table_create(hash_function hash_fun, ioopm_eq_function equal_fun)
{
  /// Allocate space for a ioopm_hash_table_t = No_Buckets pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  for (int i = 0; i < No_Buckets; i++) {
    result->buckets[i] = entry_create(int_elem(0), ptr_elem(NULL), NULL);
  }
  result->hash_fun = hash_fun;
  result->equal_fun = equal_fun;
  return result;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
  // TODO 
  for (int i = 0; i < No_Buckets; i++) {
    entry_destroy(ht->buckets[i]);
  }
  free(ht);
}

// 
// static entry_t *find_previous_entry_for_key(entry_t **entry, int key) {
//   entry_t *t1 = (*entry)->next;
//   if (t1 == NULL) {
//     return *entry;
//   } else if (t1->key > key) {
//     return *entry;
//   } else {}
//   entry_t *temp_entry = find_previous_entry_for_key(&t1, key);
//   return temp_entry;
// }


// static entry_t *find_previous_entry_for_key(entry_t **entry, int key) {
//   entry_t *t1 = (*entry)->next;
//   while (t1 != NULL) {
//     if (t1->key > key) {
//       break;
//     } else {
//       t1 = t1->next;
//     }
//   }
//   return *entry;
// }
// */


// vi börjar med NULL 0 så vi måste gå på först
static entry_t *find_previous_entry_for_key(entry_t *entry, int key, hash_function hash) {
  if (hash == NULL) {
    entry_t *t1 = entry->next;
    if (t1 == NULL) {
      return entry;
    } else if (t1->key.int_value >= key) {
      return entry;
    } else {
      return find_previous_entry_for_key(t1, key, hash);
    }
  } else {
  entry_t *t1 = entry->next;
  if (t1 == NULL) {
    return entry;
  } else if (hash(t1->key) >= key) {
    return entry;
  } else {
    return find_previous_entry_for_key(t1, key, hash);
  }
  }
}
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
  int bucket;
  int int_key;
  int next_key;
  entry_t *entry;
  entry_t *next;
  /// Search for an existing entry for a key
  // TODO &ht
  if (ht->hash_fun == NULL)
  {
    // treat keys as integers
    int_key = key.int_value; // .i reads the integer part of the elem_t
    bucket = abs(int_key % No_Buckets);
    entry = find_previous_entry_for_key((*ht).buckets[bucket], int_key, ht->hash_fun);
    next = entry->next;
    next_key = next->key.int_value;
  }
else
  {
    int_key = ht->hash_fun(key);
    bucket = abs(int_key % No_Buckets);
    entry = find_previous_entry_for_key((*ht).buckets[bucket], int_key, ht->hash_fun);
    next = entry->next;
    next_key = ht->hash_fun(next->key);
  }

  /// Check if the next entry should be updated or not
  if (next != NULL && next_key == int_key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
    }
}




ioopm_option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key)
 {
  int bucket;
  int int_key;
  entry_t *entry;
  entry_t *next;
  /// Search for an existing entry for a key
  // TODO &ht
  if (ht->hash_fun == NULL)
  {
    // treat keys as integers
    int_key = key.int_value; // .i reads the integer part of the elem_t
    bucket = abs(int_key % No_Buckets);
    entry = find_previous_entry_for_key((*ht).buckets[bucket], int_key, ht->hash_fun);
    next = entry->next;
  }
else
  {
    int_key = ht->hash_fun(key);
    bucket = abs(int_key % No_Buckets);
    entry = find_previous_entry_for_key((*ht).buckets[bucket], int_key, ht->hash_fun);
    next = entry->next;
  }
  
  // Den innan var (next && next-> value)
   if (next != NULL)
   {
     return (ioopm_option_t) { .success = true, .value = next->value };
   }
  else
   {
     return (ioopm_option_t) { .success = false };
   }
}

ioopm_option_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
 {
   int bucket;
  int int_key;
  entry_t *entry;
  entry_t *next;
  /// Search for an existing entry for a key
  // TODO &ht
  if (ht->hash_fun == NULL)
  {
    // treat keys as integers
    int_key = key.int_value; // .i reads the integer part of the elem_t
    bucket = abs(int_key % No_Buckets);
    entry = find_previous_entry_for_key((*ht).buckets[bucket], int_key, ht->hash_fun);
    next = entry->next;
  }
else
  {
    int_key = ht->hash_fun(key);
    bucket = abs(int_key % No_Buckets);
    entry = find_previous_entry_for_key((*ht).buckets[bucket], int_key, ht->hash_fun);
    next = entry->next;
  }
   ioopm_option_t options = { .success = true, .value = next->value};

   if (next != NULL)
   {
     entry->next = next->next;
     free(next);
     return options;
   }
   else
   {
     return options;
   }
 }

// size_t ioopm_hash_table_size(ioopm_hash_table_t *ht) {
//   size_t counter = 0;
//   for (int i = 0; i < No_Buckets; i++) {
//     entry_t *t = ht->buckets[i];
//       while (t->next != NULL) {
//         counter = counter + 1;
//         t = t->next;
//       }
//   }
//   return counter;
// }

// bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
// {
//   for (int i = 0; i < No_Buckets; i++) {
//     if (ht->buckets[i]->next != NULL) {
//       return false;
//     }
//   }
//   return true;
// }

// void ioopm_hash_table_clear(ioopm_hash_table_t *ht) 
// {
//   for (int i = 0; i < No_Buckets; i++) {
//     entry_t *t = ht->buckets[i]->next;
//     if (t != NULL)
//     {
//       entry_destroy(t);
//       ht->buckets[i]->next = NULL;
//     }
//   }
// }

// ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
// {
//   ioopm_list_t  *new_list = ioopm_linked_list_create();
  
//   for (int i = 0; i < No_Buckets; i++) {
//     entry_t *t = ht->buckets[i]->next;
//     while (t != NULL) {
//       ioopm_linked_list_append(new_list, t->key);
//       t = t->next;
//     }
//   }
//   return new_list;
// }


// char **ioopm_hash_table_values(ioopm_hash_table_t *ht) 
// {
//   size_t size = ioopm_hash_table_size(ht);
//   int size_int = size;
//   char **arr = calloc(1, (sizeof(char*)*size_int) + sizeof(char*));
//   int counter = 0;
//   for (int i = 0; i < No_Buckets; i++) {
//     entry_t *t = ht->buckets[i]->next;
//     while (t != NULL) {
//       arr[counter] = t->value;
//       counter++;
//       t = t->next;
//     }
//   }
//   arr[counter] = NULL;
//   return arr;
// }



// static bool key_equiv(int key, char *value_ignored, void *x)
// {
//   int *other_key_ptr = x;
//   int other_key = *other_key_ptr;
//   return key == other_key;
// }

// static bool value_equiv(int key_ignored, char *value, void *x)
// {
//   char *other_value_ptr = x;
//   char *other_value = other_value_ptr;
//   return strcmp(value, other_value) == 0;
// }

// bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
// {
//   size_t size = ioopm_hash_table_size(ht);
//   ioopm_list_t *linked_list = ioopm_hash_table_keys(ht);
//   ioopm_link_t *link = linked_list->first;

//   char **arr_v = ioopm_hash_table_values(ht);
//   for (int i = 0; i < size; link = link->next, i++) {
//     if (!pred(link->element, arr_v[i], arg)) {
//       ioopm_linked_list_destroy(linked_list);
//       free(arr_v);
//       return false;   
//     }
//   } 
//   ioopm_linked_list_destroy(linked_list);
//   free(arr_v);
//   return true;
// }


// bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
// {
//   size_t size = ioopm_hash_table_size(ht);
//   ioopm_list_t *linked_list = ioopm_hash_table_keys(ht);
//   ioopm_link_t *link = linked_list->first;

//   char **arr_v = ioopm_hash_table_values(ht);
//   for (int i = 0; i < size; link = link->next, i++) {
//     if (pred(link->element, arr_v[i], arg)) {
//       ioopm_linked_list_destroy(linked_list);
//       free(arr_v);
//       return true;  
//     }
//   } 
//   ioopm_linked_list_destroy(linked_list);
//   free(arr_v);
//   return false;
// }

// bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, int key) {
//   return ioopm_hash_table_any(ht, key_equiv, &key);
// }

// bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, char *value) {
//   return ioopm_hash_table_any(ht, value_equiv, value);
// }


// void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg)
// {
//   size_t size = ioopm_hash_table_size(ht); 
//   ioopm_list_t *linked_list = ioopm_hash_table_keys(ht);
//   ioopm_link_t *link = linked_list->first;

//   char **arr_v = ioopm_hash_table_values(ht);
//   for (int i = 0; i < size; link = link->next, i++) {
//     apply_fun(link->element, arr_v, arg);
//   }
//   ioopm_linked_list_destroy(linked_list);
//   free(arr_v);
// }