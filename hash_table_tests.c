#include "hash_table.h"
#include <CUnit/Basic.h>
#include <stdbool.h>

typedef struct option option_t;

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
    option_t answer = ioopm_hash_table_lookup(ht, i);
    char *lol = answer.value;
    CU_ASSERT_PTR_NULL(lol);
  }
  ioopm_hash_table_insert(ht, 6, "Hej");
  option_t but = ioopm_hash_table_lookup(ht, 6);
  char *lol1 = but.value;
  CU_ASSERT_PTR_NOT_NULL(lol1);
  option_t but1 = ioopm_hash_table_remove(ht, 6);
  char *lol2 = but1.value;
  CU_ASSERT_PTR_NOT_NULL(lol2);
  option_t but3 = ioopm_hash_table_lookup(ht, 6);
  char *lol3 = but3.value;
  CU_ASSERT_PTR_NULL(lol3);

  //CU_ASSERT_PTR_NULL(lol1);


  /* TODO:
  option_t but2 = ioopm_hash_table_lookup(ht, -2);
  char *lol3 = but2.value;
  CU_ASSERT_PTR_NULL(lol3);
  ioopm_hash_table_insert(ht, -1, "Hej");
  option_t but1 = ioopm_hash_table_lookup(ht, -1);
  char *lol2 = but1.value;
  CU_ASSERT_PTR_NOT_NULL(lol2);
  */
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