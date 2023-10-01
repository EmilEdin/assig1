#include "hash_table.h"
#include "common.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "linked_list.c"
#define No_Buckets 17


static bool int_compare(elem_t a, elem_t b) { return a.int_value == b.int_value;}

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
  ioopm_predicate eq_fun;
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
    entry_destroy(next); // Destroy every link recursively untill we hit next == NULL
  }
}

ioopm_hash_table_t *ioopm_hash_table_create(hash_function hash_fun, ioopm_predicate eq_fun)
{
  // Allocate space for a ioopm_hash_table_t = No_Buckets pointers to
  // entry_t's, which will be set to NULL
  // Must be free:d at later stages
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  for (int i = 0; i < No_Buckets; i++) {
    result->buckets[i] = entry_create(int_elem(0), ptr_elem(NULL), NULL);
  }
  result->hash_fun = hash_fun;
  result->eq_fun = eq_fun;
  return result;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
  // TODO 
  for (int i = 0; i < No_Buckets; i++) {
    entry_destroy(ht->buckets[i]);
  }
  free(ht);
}


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
    //  Treat keys as integers                          
    entry_t *t1 = entry->next;
    if (t1 == NULL) {                                       //  We can't go any futher down the list
      return entry;
    } else if (abs(t1->key.int_value) >= key) {             //  We found the right place to insert a new entry
      return entry;
    } else {
      return find_previous_entry_for_key(t1, key, hash);    //  Search recursively until satisfied
    }
  } else {
    //  Treat keys as strings
    entry_t *t1 = entry->next;
    if (t1 == NULL) {
      return entry;
    } else if (abs(hash(t1->key)) >= key) {
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
  elem_t next_key;
  entry_t *entry;
  entry_t *next;

  // Search for an existing entry for a key
  if (ht->hash_fun == NULL)
  {
    //  treat keys as integers
    int_key = abs(key.int_value);                     //  .int_value reads the integer part of the elem_t
    bucket = int_key % No_Buckets;                    //  find the right bucket
    entry = find_previous_entry_for_key((*ht).buckets[bucket], int_key, ht->hash_fun);
    next = entry->next;
    if (next != NULL) {  
      next_key.int_value = abs(next->key.int_value);  
    } 
  }
  else
    {
      //  Treat keys as string
      int_key = abs(ht->hash_fun(key));
      bucket = int_key % No_Buckets;
      entry = find_previous_entry_for_key((*ht).buckets[bucket], int_key, ht->hash_fun);
      next = entry->next;
      if (next != NULL) {
        next_key.int_value = abs(ht->hash_fun(next->key));     
      }
    }
    
  if (next != NULL) {                       
    if (next_key.int_value == int_key) {               // Check if next has our key, if not create and entry
      next->value = value;
    } else {
      key.int_value = abs(key.int_value);
      entry->next = entry_create(key, value, next);
    }
  } else {
    if (ht->hash_fun == NULL) {                          // Next is null => if key type is int, abs negative key to store as positive
      key.int_value = abs(key.int_value);
    }
    entry->next = entry_create(key, value, next);
  }
}




ioopm_option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key)
 {
  int bucket;
  int int_key;
  entry_t *entry;
  entry_t *next;

  //  Search for an existing entry for a key
  if (ht->hash_fun == NULL)
  {
    //  Treat keys as integers
    int_key = abs(key.int_value);                           //  .i reads the integer part of the elem_t
    bucket = int_key % No_Buckets;                          //  Find the right bucket
    entry = find_previous_entry_for_key((*ht).buckets[bucket], int_key, ht->hash_fun);
    next = entry->next;
  }
else
  {
    //  Treat keys as strings
    int_key = ht->hash_fun(key);
    bucket = abs(int_key % No_Buckets);
    entry = find_previous_entry_for_key((*ht).buckets[bucket], int_key, ht->hash_fun);
    next = entry->next;
  }
  
   if (next != NULL) {                                                        
     if (ht->hash_fun == NULL) {                                                      // Check if key type is int
        if (next->key.int_value == int_key) {                                         // Check if keys as string are equal
          return (ioopm_option_t) { .success = true, .value = next->value };
        } else {
          return (ioopm_option_t) { .success = false};
        }
     } else if (ht->hash_fun(next->key) == ht->hash_fun(key)) {                       // Check if keys as string are equal
          return (ioopm_option_t) { .success = true, .value = next->value };
      } else {
        return (ioopm_option_t) { .success = false};
     }
    } else {                                                                          // If next == NULL, we did not find key
     return (ioopm_option_t) { .success = false};
   }
}

ioopm_option_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
 {
  int bucket;
  int int_key;
  entry_t *entry;
  entry_t *next;

  // Search for an existing entry for a key
  if (ht->hash_fun == NULL)
  {
    // treat keys as integers
    int_key = abs(key.int_value);                   //  .i reads the integer part of the elem_t
    bucket = int_key % No_Buckets;                  //  Find the right bucket
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
   
  
   if (next != NULL) {                                                      
    if (ht->hash_fun == NULL) {
      if (next->key.int_value == int_key) {                               // Keys as ints
        ioopm_option_t options = { .success = true, .value = next->value};
        entry->next = next->next;
        free(next);                                                     
        return options;
      } else {
        ioopm_option_t options = { .success = false};
        return options;
      }
    } else if (ht->hash_fun(next->key) == ht->hash_fun(key)) {            // Keys as strings
      ioopm_option_t options = { .success = true, .value = next->value};
      entry->next = next->next;
      free(next);
      return options;
   } else {
    ioopm_option_t options = { .success = false};
    return options;
   }
} else {                                                                  //  If next == NULL, we did not find the element to be removed
    ioopm_option_t options = { .success = false};
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
      entry_destroy(t);                                  // Destroys the whole link recursively at bucket i
      ht->buckets[i]->next = NULL;
    }
  }
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  ioopm_list_t *new_list = ioopm_linked_list_create(int_compare);  // Needs to be freed at later stages when the function is used
  
  for (int i = 0; i < No_Buckets; i++) {
    entry_t *t = ht->buckets[i]->next;
    while (t != NULL) {
      ioopm_linked_list_append(new_list, t->key);
      t = t->next;
    }
  }
  return new_list;
}


ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht) 
{
  ioopm_list_t *new_list = ioopm_linked_list_create(int_compare);     // Needs to be freed at later stages when the function is used
  
  for (int i = 0; i < No_Buckets; i++) {
    entry_t *t = ht->buckets[i]->next;
    while (t != NULL) {
      ioopm_linked_list_append(new_list, t->value);
      t = t->next;
    }
  }
  return new_list;
}




static bool key_equiv(elem_t key, elem_t value_ignored, void *arg, bool x)
{
   // If x == True, keys are strings, else keys are ints
  bool int_or_str = x;

  if(int_or_str) {
    elem_t *other_key_ptr = arg;
    char *other_key = other_key_ptr->string_value;
    return key.string_value == other_key; 
  } else {
    elem_t *other_key_ptr = arg;
    int other_key = other_key_ptr->int_value;
    return key.int_value == other_key;
  }
}


static bool value_int_equiv(elem_t value_ignored, elem_t value, void *arg, bool x)
{
  int *other_key_ptr = arg;
  int other_key = *other_key_ptr;
  return value.int_value == other_key;
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
{
  size_t size = ioopm_hash_table_size(ht);
  ioopm_list_t *linked_list = ioopm_hash_table_keys(ht);      // Gives a linked list with all keys in ht
  ioopm_link_t *link = linked_list->first;

  ioopm_list_t *list_v = ioopm_hash_table_values(ht);          // Gives a linked list with all values in ht
  ioopm_link_t *link_itr = list_v->first;
  bool *extra = false;
  for (int i = 0; i < size; link = link->next, link_itr = link_itr->next, i++) { // Goes through the whole list
    if (!pred(link->element, link_itr->element, arg, extra)) {     // If pred does not satisfy for some key/value pair => return false
      ioopm_linked_list_destroy(linked_list);
      ioopm_linked_list_destroy(list_v);
      return false;   
    }
  } 
  ioopm_linked_list_destroy(linked_list);
  ioopm_linked_list_destroy(list_v);
  return true;
}


bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
{
  size_t size = ioopm_hash_table_size(ht);
  ioopm_list_t *linked_list = ioopm_hash_table_keys(ht);        // Gives a linked list with all keys in ht
  ioopm_link_t *link = linked_list->first;

  ioopm_list_t *list_v = ioopm_hash_table_values(ht);            // Gives a linked list with all values in ht
  ioopm_link_t *link_itr = list_v->first;
  bool extra = false;
  extra = (ht->eq_fun != NULL);

  for (int i = 0; i < size; link = link->next, link_itr = link_itr->next, i++) {  // Goes through the whole list
    if (pred(link->element, link_itr->element, arg, extra)) {  // If pred does satisfy for some key/value pair => return true
      ioopm_linked_list_destroy(linked_list);
      ioopm_linked_list_destroy(list_v);
      return true;  
    }
  } 
  ioopm_linked_list_destroy(linked_list);
  ioopm_linked_list_destroy(list_v);
  return false;
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key) {
  return ioopm_hash_table_any(ht, key_equiv, &key);
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value) {
  // Values are strings
  if (ht->eq_fun != NULL) {
    return ioopm_hash_table_any(ht, ht->eq_fun, &value);
  }
  // Values are ints
  return ioopm_hash_table_any(ht, value_int_equiv, &value);
}


void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg)
{
  size_t size = ioopm_hash_table_size(ht); 
  ioopm_list_t *linked_list = ioopm_hash_table_keys(ht);        // Gives a linked list with all keys from ht
  ioopm_link_t *link = linked_list->first;

  ioopm_list_t *list_v = ioopm_hash_table_values(ht);           // Gives a linked list with all values from ht
  ioopm_link_t *link_itr = list_v->first;
  for (int i = 0; i < size; link = link->next, link_itr = link_itr->next, i++) { // Goes through the whole list
    apply_fun(link->element, link_itr->element, arg);           //  Apply function on every key/value pair
  }
  ioopm_linked_list_destroy(linked_list);
  ioopm_linked_list_destroy(list_v);
}