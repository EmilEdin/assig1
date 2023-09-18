#include "hash_table.h"
#include <CUnit/Basic.h>
#include <stdbool.h>

typedef struct option ioopm_option_t;

struct option
{
  bool success;
  char *value;
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
  ioopm_hash_table_insert(ht, 6, "Hej");
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

 ioopm_hash_table_destroy(ht);
}

void test_hash_table_size(void)
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
  // Checks that size of empty hashtable is 0.
   int empty_hash_table = ioopm_hash_table_size(ht);
   CU_ASSERT_EQUAL(0, empty_hash_table);

  // Checks that size of hashtable is one.
  ioopm_hash_table_insert(ht, 6, "Hej");
  int one_entry = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(1, one_entry);
  ioopm_hash_table_remove(ht, 6);

  // Checks that size of hashtable is the_size
  int the_size = 5;
  for (int i = 1; i <= 5; i++) {
    ioopm_hash_table_insert(ht, i, "Hello");
  }
  int five_entries = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(the_size, five_entries);
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