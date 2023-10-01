#include "hash_table.h"
#include "linked_list.h"
#include "common.h"
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct entry entry_t;

struct entry
{
  elem_t key;       // holds the key
  elem_t value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

int string_to_int(elem_t str){
  int new_int = atoi(str.string_value);
  return new_int;
}

#define No_Buckets 17

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
  char *value;
};

struct link
{
    elem_t element;
    ioopm_link_t *next;
};

struct list
{
    ioopm_link_t *first;
    ioopm_link_t *last;
    size_t size; // Added field to store the number of elements in the linked list.
};

static bool value_equiv(elem_t key_ignored, elem_t value, void *arg, bool x)
{
    elem_t *other_value_ptr = arg;
    char *other_value = other_value_ptr->string_value;
    return strcmp(value.string_value, other_value) == 0;
}

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
//static bool int_compare(elem_t a, elem_t b) { return a.int_value == b.int_value;}

void test_create_destroy(void)
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, NULL);
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, NULL);
  ioopm_hash_table_t *ht_str = ioopm_hash_table_create(string_to_int, NULL);
  for (int i = 0; i <= 16; ++i) {
    ioopm_option_t answer = ioopm_hash_table_lookup(ht, int_elem(i));
    char *struct_value = answer.value;
    CU_ASSERT_PTR_NULL(struct_value);
  }
  // TODO: Test when insert and lookup are given a negative integer.
  
  // Checks that insert works combined with lookup.
  // Checks that insert works combined with lookup.

  ioopm_hash_table_insert(ht_str, ptr_elem("4"), ptr_elem("Hej"));
  ioopm_hash_table_insert(ht_str, ptr_elem("72"), ptr_elem("Hej"));
  ioopm_hash_table_insert(ht_str, ptr_elem("21"), ptr_elem("Hej"));
  ioopm_option_t struct_test1 = ioopm_hash_table_lookup(ht_str, ptr_elem("72"));
  char *struct_value_of_test1 = struct_test1.value;
  CU_ASSERT_PTR_NOT_NULL(struct_value_of_test1);


  ioopm_hash_table_insert(ht, int_elem(6), ptr_elem("Hej"));
  ioopm_hash_table_insert(ht, int_elem(40), ptr_elem("Hej"));
  ioopm_hash_table_insert(ht, int_elem(23), ptr_elem("Hej"));
   ioopm_hash_table_insert(ht, int_elem(23), ptr_elem("Sko"));
  ioopm_option_t struct_test = ioopm_hash_table_lookup(ht, int_elem(6));
  char *struct_value_of_test = struct_test.value;
  CU_ASSERT_PTR_NOT_NULL(struct_value_of_test);

  // Checks that inserts works for negative integer values for key.
  ioopm_hash_table_insert(ht, int_elem(-1), ptr_elem("Hej"));
  ioopm_option_t negative_test = ioopm_hash_table_lookup(ht, int_elem(-1));
  char *test_negative_key = negative_test.value;
  CU_ASSERT_PTR_NOT_NULL(test_negative_key);
  ioopm_hash_table_remove(ht, int_elem(-1));
  // Checks that inserts works for zero key
  ioopm_hash_table_insert(ht, int_elem(0), ptr_elem("ju8emjihuj766hui"));
  ioopm_option_t zero_test = ioopm_hash_table_lookup(ht, int_elem(0));
  char *test_zero_key = zero_test.value;
  CU_ASSERT_PTR_NOT_NULL(test_zero_key);

 ioopm_hash_table_destroy(ht);
 ioopm_hash_table_destroy(ht_str);
}

void test_hash_table_size(void)
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, NULL);
  // Checks that size of empty hashtable is 0.
   int empty_hash_table = ioopm_hash_table_size(ht);
   CU_ASSERT_EQUAL(0, empty_hash_table);

  // Checks that size of hashtable is one.
  ioopm_hash_table_insert(ht, int_elem(-6), ptr_elem("Hej"));
  int one_entry = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(1, one_entry);
  ioopm_hash_table_remove(ht, int_elem(-6));

  // Checks that size of hashtable is the_size
  int the_size = 5;
  for (int i = 1; i <= 5; i++) {
    ioopm_hash_table_insert(ht, int_elem(i), ptr_elem("Hello"));
  }
  int five_entries = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(the_size, five_entries);

  ioopm_hash_table_destroy(ht);
}

void test_ht_remove_str_key(void) {
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_to_int, NULL);

  ioopm_hash_table_insert(ht, ptr_elem("4"), ptr_elem("Första"));
  ioopm_hash_table_insert(ht, ptr_elem("72"), ptr_elem("Andra"));
  ioopm_hash_table_insert(ht, ptr_elem("89"), ptr_elem("Fjärde"));
  ioopm_option_t false_remove_str = ioopm_hash_table_remove(ht, ptr_elem("21"));
  CU_ASSERT_FALSE(false_remove_str.success);

  ioopm_option_t remove_middle = ioopm_hash_table_remove(ht, ptr_elem("72"));
  ioopm_option_t struct_test_middle = ioopm_hash_table_lookup(ht, ptr_elem("72"));
  CU_ASSERT_FALSE(struct_test_middle.success);
  CU_ASSERT_TRUE(remove_middle.success);
  
  ioopm_option_t remove_last = ioopm_hash_table_remove(ht, ptr_elem("89"));
  ioopm_option_t struct_test_last = ioopm_hash_table_lookup(ht, ptr_elem("89"));
  CU_ASSERT_FALSE(struct_test_last.success);
  CU_ASSERT_TRUE(remove_last.success);

  ioopm_option_t remove_first = ioopm_hash_table_remove(ht, ptr_elem("4"));
  ioopm_option_t struct_test_first = ioopm_hash_table_lookup(ht, ptr_elem("4"));
  CU_ASSERT_FALSE(struct_test_first.success);
  CU_ASSERT_TRUE(remove_first.success);


  ioopm_option_t remove_already_removed = ioopm_hash_table_remove(ht, ptr_elem("4"));
  CU_ASSERT_FALSE(remove_already_removed.success);

    ioopm_hash_table_destroy(ht);
}

void test_remove_int_key(void) {
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, NULL);

  ioopm_hash_table_insert(ht, int_elem(6), ptr_elem("Hej"));
  ioopm_hash_table_insert(ht, int_elem(40), ptr_elem("Hej"));
  ioopm_hash_table_insert(ht, int_elem(57), ptr_elem("Sko"));
  ioopm_option_t false_remove_int = ioopm_hash_table_remove(ht, int_elem(23));
  ioopm_option_t false_remove_int_v2 = ioopm_hash_table_remove(ht, int_elem(21));
  CU_ASSERT_FALSE(false_remove_int_v2.success);
  CU_ASSERT_FALSE(false_remove_int.success);

  ioopm_option_t remove_middle = ioopm_hash_table_remove(ht, int_elem(40));
  ioopm_option_t struct_test_middle = ioopm_hash_table_lookup(ht, int_elem(40));
  CU_ASSERT_FALSE(struct_test_middle.success);
  CU_ASSERT_TRUE(remove_middle.success);

  ioopm_option_t remove_last = ioopm_hash_table_remove(ht, int_elem(57));
  ioopm_option_t struct_test_last = ioopm_hash_table_lookup(ht, int_elem(57));
  CU_ASSERT_FALSE(struct_test_last.success);
  CU_ASSERT_TRUE(remove_last.success);

  ioopm_option_t remove_first = ioopm_hash_table_remove(ht, int_elem(6));
  ioopm_option_t struct_test_first = ioopm_hash_table_lookup(ht, int_elem(6));
  CU_ASSERT_FALSE(struct_test_first.success);
  CU_ASSERT_TRUE(remove_first.success);

  ioopm_option_t remove_already_removed = ioopm_hash_table_remove(ht, int_elem(6));
  CU_ASSERT_FALSE(remove_already_removed.success);

  ioopm_hash_table_destroy(ht);
}

void test_hash_table_empty(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, NULL);

  // Check if hashtable without entries is empty
  bool empty = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_TRUE(empty);

  // Check if hashtable with one entry is not empty
  ioopm_hash_table_insert(ht, int_elem(6), ptr_elem("Hej"));
  bool one_element = ioopm_hash_table_is_empty(ht);
  CU_ASSERT_FALSE(one_element);

  ioopm_hash_table_destroy(ht);
}

void test_hash_table_clear(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, NULL);

  ioopm_hash_table_insert(ht, int_elem(6), ptr_elem("Hej"));
  ioopm_hash_table_clear(ht);
  entry_t *t = ht->buckets[6]->next;
  CU_ASSERT_PTR_NULL(t);

  ioopm_hash_table_destroy(ht);
}

void test_hash_table_keys(void) {
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, NULL);

  int keys[5] = {1, 2, 3, 4, 5};
  bool found[5] = {false, false, false, false, false};
  for (int i = 1; i <= 5; i++) {
    ioopm_hash_table_insert(ht, int_elem(i), ptr_elem("Hej"));
  }
  ioopm_list_t *linked_list = ioopm_hash_table_keys(ht);
  ioopm_link_t *link = linked_list->first;
  for (int index = 0; index < 5; index++) {
    for (int j = 0; j < 5; j++) {
      if (link->element.int_value == keys[index]) {
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
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, NULL);

  int keys[5] = {3, 71, 42, 1, 99};
  char *values[5] = {"three", "ten", "fortytwo", "zero", "ninetynine"};

  ioopm_hash_table_insert(ht, int_elem(3), ptr_elem("three"));
  ioopm_hash_table_insert(ht, int_elem(71), ptr_elem("ten"));
  ioopm_hash_table_insert(ht, int_elem(42), ptr_elem("fortytwo"));
  ioopm_hash_table_insert(ht, int_elem(1), ptr_elem("zero"));
  ioopm_hash_table_insert(ht, int_elem(99), ptr_elem("ninetynine"));

  ioopm_list_t *linked_list = ioopm_hash_table_keys(ht);
  ioopm_link_t *link = linked_list->first;
  ioopm_list_t *v = ioopm_hash_table_values(ht);
  ioopm_link_t *v1 = v->first;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (link->element.int_value == keys[j]) {
        CU_ASSERT_FALSE(strcmp(v1->element.string_value, values[j]));
        }
      }
    link = link->next;
    v1 = v1->next;
    }
  
  ioopm_linked_list_destroy(v);
  ioopm_linked_list_destroy(linked_list);
  ioopm_hash_table_destroy(ht);
}

void test_hash_table_has_key_int(void) {
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, NULL);

  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, int_elem(53)));
  
  ioopm_hash_table_insert(ht, int_elem(3), ptr_elem("three"));
  ioopm_hash_table_insert(ht, int_elem(10), ptr_elem("ten"));
  ioopm_hash_table_insert(ht, int_elem(42), ptr_elem("fortytwo"));

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, int_elem(3)));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, int_elem(10)));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, int_elem(53)));


  ioopm_hash_table_destroy(ht);
}

void test_hash_table_has_value(void) {
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, value_equiv);
  ioopm_hash_table_t *ht_int = ioopm_hash_table_create(NULL, NULL);

  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, ptr_elem("fortyone")));
  
  ioopm_hash_table_insert(ht, int_elem(3), ptr_elem("three"));
  ioopm_hash_table_insert(ht, int_elem(10), ptr_elem("ten"));
  ioopm_hash_table_insert(ht, int_elem(42), ptr_elem("fortytwo"));


  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, ptr_elem("three")));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, ptr_elem("ten")));
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, ptr_elem("fortykone")));

  
  char *copy_three = strdup("three");
  char *copy_ten = strdup("ten");
  char *copy_fortytwo = strdup("fortytwo");

  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, ptr_elem(copy_three)));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, ptr_elem(copy_ten)));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, ptr_elem(copy_fortytwo)));

  // Values are ints
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht_int, int_elem(4)));
  
  ioopm_hash_table_insert(ht_int, int_elem(3), int_elem(69));
  ioopm_hash_table_insert(ht_int, int_elem(10), int_elem(420));
  ioopm_hash_table_insert(ht_int, int_elem(42), int_elem(696));


  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht_int, int_elem(69)));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht_int, int_elem(420)));
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht_int, int_elem(6986)));


  free(copy_three);
  free(copy_ten);
  free(copy_fortytwo);


  ioopm_hash_table_destroy(ht);
  ioopm_hash_table_destroy(ht_int);
}

static void remove_even_key_entries(elem_t key, elem_t value, void *extra) {
  //char *lol = key.string_value;
  ioopm_hash_table_t *ht = extra;
  if (key.int_value % 2 == 0) {
    ioopm_hash_table_remove(ht, key);
  }
}

void test_hash_table_apply_to_all(void) {
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, NULL);

  ioopm_hash_table_insert(ht, int_elem(3), ptr_elem("three"));
  ioopm_hash_table_insert(ht, int_elem(10), ptr_elem("ten"));
  ioopm_hash_table_insert(ht, int_elem(42), ptr_elem("fortytwo"));
  ioopm_hash_table_insert(ht, int_elem(1), ptr_elem("zero"));
  ioopm_hash_table_insert(ht, int_elem(99), ptr_elem("ninetynine"));

  ioopm_hash_table_apply_to_all(ht, remove_even_key_entries, ht);

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, int_elem(3)));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, int_elem(10)));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, int_elem(42)));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, int_elem(1)));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, int_elem(99)));

  ioopm_hash_table_destroy(ht);
}

bool is_even(elem_t key, elem_t value, void *arg, bool x)
{
    if(key.int_value % 2 == 0) {
        return true;
    } else {
        return false;
    }
}


// static bool all_function(int key, char *value, void *extra)
// {
//   ioopm_hash_table_t *ht = extra;
//   size_t size = ioopm_hash_table_size(ht); 
//   ioopm_list_t *linked_list = ioopm_hash_table_keys(ht);
//   ioopm_link_t *link = linked_list->first;

//   char **arr_v = ioopm_hash_table_values(ht);
//   int i = 0;
//   for (; i < size; link = link->next, i++) {
//     if (link->element == key)
//     {
//       if (arr_v[i] == value)
//       {
//         ioopm_linked_list_destroy(linked_list);
//         free(arr_v);
//         return true;
//       } else {
//         ioopm_linked_list_destroy(linked_list);
//         free(arr_v);
//         return false;
//       }
//     }
//   }
//   ioopm_linked_list_destroy(linked_list);
//   free(arr_v);
//   return false;
// }

void test_hash_table_all(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(NULL, NULL);

  CU_ASSERT_TRUE(ioopm_hash_table_all(ht, is_even, ht));

  ioopm_hash_table_insert(ht, int_elem(3), ptr_elem("three"));
  CU_ASSERT_FALSE(ioopm_hash_table_all(ht, is_even, ht))

  ioopm_hash_table_insert(ht, int_elem(10), ptr_elem("ten"));
  ioopm_hash_table_insert(ht, int_elem(42), ptr_elem("fortytwo"));
  ioopm_hash_table_insert(ht, int_elem(1), ptr_elem("zero"));
  ioopm_hash_table_insert(ht, int_elem(99), ptr_elem("ninetynine"));

  CU_ASSERT_FALSE(ioopm_hash_table_all(ht, is_even, ht))

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
    (CU_add_test(my_test_suite, "Test for remove_str functionality", test_ht_remove_str_key) == NULL) ||
    (CU_add_test(my_test_suite, "Test for remove_int functionality", test_remove_int_key) == NULL) ||
    (CU_add_test(my_test_suite, "Test for empty functionality", test_hash_table_empty) == NULL) ||
    (CU_add_test(my_test_suite, "Test for clear functionality", test_hash_table_clear) == NULL) ||
    (CU_add_test(my_test_suite, "Test for keys functionality", test_hash_table_keys) == NULL) ||
    (CU_add_test(my_test_suite, "Test for values functionality", test_hash_table_values) == NULL) ||
    (CU_add_test(my_test_suite, "Test for has_key functionality", test_hash_table_has_key_int) == NULL) ||
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