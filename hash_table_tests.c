#include "hash_table.h"
#include "linked_list.h"
#include "common.h"
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct entry entry_t;

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

#define No_Buckets 17

struct hash_table
{
  entry_t *buckets[No_Buckets];
};

typedef struct option ioopm_option_t;

struct option
{
  bool success;
  char *value;
};

struct link
{
    int element;
    ioopm_link_t *next;
};

struct list
{
    ioopm_link_t *first;
    ioopm_link_t *last;
    size_t size; // Added field to store the number of elements in the linked list.
};


int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

void test_create_destroy(void)
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int i = 0; i <= 16; ++i) {
    ioopm_option_t answer = ioopm_hash_table_lookup(ht, i);
    char *struct_value = answer.value;
    CU_ASSERT_PTR_NULL(struct_value);
  }
  // TODO: Test when insert and lookup are given a negative integer.
  
  // Checks that insert works combined with lookup.
  ioopm_int_str_ht_insert(ht, 6, "Hej");
  ioopm_option_t struct_test = ioopm_hash_table_lookup(ht, 6);
  char *struct_value_of_test = struct_test.value;
  CU_ASSERT_PTR_NOT_NULL(struct_value_of_test);
  // Checks that remove function works combined with lookup.
  ioopm_option_t remove_test = ioopm_hash_table_remove(ht, 6);
  char *remove = remove_test.value;
  // Remove will return the value string if remove was a success.
  CU_ASSERT_PTR_NOT_NULL(remove);
  // Checks that we removed the entry struct.
  ioopm_option_t removed_struct = ioopm_hash_table_lookup(ht, 6);
  char *struct_value_of_removed_struct = removed_struct.value;
  CU_ASSERT_PTR_NULL(struct_value_of_removed_struct);
  // Checks that inserts works for negative integer values for key.
  ioopm_int_str_ht_insert(ht, -1, "Hej");
  ioopm_option_t negative_test = ioopm_hash_table_lookup(ht, -1);
  char *test_negative_key = negative_test.value;
  CU_ASSERT_PTR_NOT_NULL(test_negative_key);
  ioopm_hash_table_remove(ht, -1);
  // Checks that inserts works for zero key
  ioopm_int_str_ht_insert(ht, 0, "ju8emjihuj766hui");
  ioopm_option_t zero_test = ioopm_hash_table_lookup(ht, 0);
  char *test_zero_key = zero_test.value;
  CU_ASSERT_PTR_NOT_NULL(test_zero_key);

 ioopm_hash_table_destroy(ht);
}

void test_hash_table_size(void)
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
  // Checks that size of empty hashtable is 0.
   int empty_hash_table = ioopm_hash_table_size(ht);
   CU_ASSERT_EQUAL(0, empty_hash_table);

  // Checks that size of hashtable is one.
  ioopm_int_str_ht_insert(ht, -6, "Hej");
  int one_entry = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(1, one_entry);
  ioopm_hash_table_remove(ht, -6);

  // Checks that size of hashtable is the_size
  int the_size = 5;
  for (int i = 1; i <= 5; i++) {
    ioopm_int_str_ht_insert(ht, i, "Hello");
  }
  int five_entries = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(the_size, five_entries);

  ioopm_hash_table_destroy(ht);
}

void test_hash_table_empty(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  // Check if hashtable without entries is empty
  bool empty = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_TRUE(empty);

  // Check if hashtable with one entry is not empty
  ioopm_int_str_ht_insert(ht, 6, "Hej");
  bool one_element = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_FALSE(one_element);

  ioopm_hash_table_destroy(ht);
}

void test_hash_table_clear(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  ioopm_int_str_ht_insert(ht, 6, "Hej");
  ioopm_hash_table_clear(ht);
  entry_t *t = ht->buckets[6]->next;
  CU_ASSERT_PTR_NULL(t);

  ioopm_hash_table_destroy(ht);
}

void test_hash_table_keys(void) {
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  int keys[5] = {1, 2, 3, 4, 5};
  bool found[5] = {false, false, false, false, false};
  for (int i = 1; i <= 5; i++) {
    ioopm_int_str_ht_insert(ht, i, "Hej");
  }
  ioopm_list_t *linked_list = ioopm_hash_table_keys(ht);
  ioopm_link_t *link = linked_list->first;
  for (int index = 0; index < 5; index++) {
    for (int j = 0; j < 5; j++) {
      if (link->element == keys[index]) {
        found[j] = true;
        link = linked_list->first;
        break;
      } else if (j == 4) {
        CU_FAIL("Found a key that was never inserted!");
      } else {
        link = link->next;
      }
    }
  }
  
  for (int i = 0; i < 5; i++) {
      CU_ASSERT_TRUE(found[i]);
  }
  ioopm_linked_list_destroy(linked_list);
  ioopm_hash_table_destroy(ht);
}

void test_hash_table_values(void) {
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  int keys[5] = {3, 10, 42, 1, 99};
  char *values[5] = {"three", "ten", "fortytwo", "zero", "ninetynine"};

  ioopm_int_str_ht_insert(ht, 3, "three");
  ioopm_int_str_ht_insert(ht, 10, "ten");
  ioopm_int_str_ht_insert(ht, 42, "fortytwo");
  ioopm_int_str_ht_insert(ht, 1, "zero");
  ioopm_int_str_ht_insert(ht, 99, "ninetynine");

  ioopm_list_t *linked_list = ioopm_hash_table_keys(ht);
  ioopm_link_t *link = linked_list->first;
  char **v = ioopm_hash_table_values(ht);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (link->element == keys[j]) {
        CU_ASSERT_FALSE(strcmp(v[i], values[j]));
        }
      }
    link = link->next;
    }
  
  free(v);
  ioopm_linked_list_destroy(linked_list);
  ioopm_hash_table_destroy(ht);
}

void test_hash_table_has_key(void) {
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  
  ioopm_int_str_ht_insert(ht, 3, "three");
  ioopm_int_str_ht_insert(ht, 10, "ten");
  ioopm_int_str_ht_insert(ht, 42, "fortytwo");
  ioopm_int_str_ht_insert(ht, 1, "zero");
  ioopm_int_str_ht_insert(ht, 99, "ninetynine");

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, 3));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, 10));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, 42));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, 1));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, 99));

  ioopm_hash_table_destroy(ht);
}

void test_hash_table_has_value(void) {
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  
  ioopm_int_str_ht_insert(ht, 3, "three");
  ioopm_int_str_ht_insert(ht, 10, "ten");
  ioopm_int_str_ht_insert(ht, 42, "fortytwo");
  ioopm_int_str_ht_insert(ht, 1, "zero");
  ioopm_int_str_ht_insert(ht, 99, "ninetynine");

  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, "three"));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, "ten"));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, "fortytwo"));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, "zero"));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, "ninetynine"));
  
  char *copy_three = strdup("three");
  char *copy_ten = strdup("ten");
  char *copy_fortytwo = strdup("fortytwo");
  char *copy_zero = strdup("zero");
  char *copy_ninetynine = strdup("ninetynine");

  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, copy_three));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, copy_ten));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, copy_fortytwo));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, copy_zero));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, copy_ninetynine));

  free(copy_three);
  free(copy_ten);
  free(copy_fortytwo);
  free(copy_zero);
  free(copy_ninetynine);


  ioopm_hash_table_destroy(ht);
}

static void remove_even_key_entries(int key, char** value, void *extra) {
    ioopm_hash_table_t *ht = extra;

      if (key % 2 == 0) {
        ioopm_hash_table_remove(ht, key);
      }
}

void test_hash_table_apply_to_all(void) {
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  ioopm_int_str_ht_insert(ht, 3, "three");
  ioopm_int_str_ht_insert(ht, 10, "ten");
  ioopm_int_str_ht_insert(ht, 42, "fortytwo");
  ioopm_int_str_ht_insert(ht, 1, "zero");
  ioopm_int_str_ht_insert(ht, 99, "ninetynine");

  ioopm_hash_table_apply_to_all(ht, remove_even_key_entries, ht);

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, 3));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, 10));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, 42));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, 1));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, 99));

  ioopm_hash_table_destroy(ht);
}

static bool all_function(int key, char *value, void *extra)
{
  ioopm_hash_table_t *ht = extra;
  size_t size = ioopm_hash_table_size(ht); 
  ioopm_list_t *linked_list = ioopm_hash_table_keys(ht);
  ioopm_link_t *link = linked_list->first;

  char **arr_v = ioopm_hash_table_values(ht);
  int i = 0;
  for (; i < size; link = link->next, i++) {
    if (link->element == key)
    {
      if (arr_v[i] == value)
      {
        ioopm_linked_list_destroy(linked_list);
        free(arr_v);
        return true;
      } else {
        ioopm_linked_list_destroy(linked_list);
        free(arr_v);
        return false;
      }
    }
  }
  ioopm_linked_list_destroy(linked_list);
  free(arr_v);
  return false;
}

void test_hash_table_all(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  CU_ASSERT_TRUE(ioopm_hash_table_all(ht, all_function, ht));

  ioopm_int_str_ht_insert(ht, 3, "three");
  ioopm_int_str_ht_insert(ht, 10, "ten");
  ioopm_int_str_ht_insert(ht, 42, "fortytwo");
  ioopm_int_str_ht_insert(ht, 1, "zero");
  ioopm_int_str_ht_insert(ht, 99, "ninetynine");

  CU_ASSERT_TRUE(ioopm_hash_table_all(ht, all_function, ht))

  ioopm_hash_table_destroy(ht);
}

int main() {

  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
  if (my_test_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    (CU_add_test(my_test_suite, "Test for create_destroy functionality", test_create_destroy) == NULL) || 
    (CU_add_test(my_test_suite, "Test for insert_once functionality", test_insert_once) == NULL) ||
    (CU_add_test(my_test_suite, "Test for size functionality", test_hash_table_size) == NULL) ||
    (CU_add_test(my_test_suite, "Test for empty functionality", test_hash_table_empty) == NULL) ||
    (CU_add_test(my_test_suite, "Test for clear functionality", test_hash_table_clear) == NULL) ||
    (CU_add_test(my_test_suite, "Test for keys functionality", test_hash_table_keys) == NULL) ||
    (CU_add_test(my_test_suite, "Test for values functionality", test_hash_table_values) == NULL) ||
    (CU_add_test(my_test_suite, "Test for has_key functionality", test_hash_table_has_key) == NULL) ||
    (CU_add_test(my_test_suite, "Test for has_value functionality", test_hash_table_has_value) == NULL) ||
    (CU_add_test(my_test_suite, "Test for apply_to_all functionality", test_hash_table_apply_to_all) == NULL) ||
    (CU_add_test(my_test_suite, "Test for all functionality", test_hash_table_all) == NULL) ||
    0
  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
} 