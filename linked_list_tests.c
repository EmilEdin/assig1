#include "linked_list.h"
#include <CUnit/Basic.h>
#include <stdbool.h>

typedef int elem_t;
typedef struct list ioopm_list_t;
struct list 

{
  elem_t element;
  ioopm_list_t *next;
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

void test_create_list(void)
{
    ioopm_list_t *new_list = ioopm_linked_list_create();
    CU_ASSERT_PTR_NULL(new_list->next);
    CU_ASSERT_EQUAL(new_list->element, 0);
    ioopm_linked_list_destroy(new_list);
}


void test_destroy_list(void)
{
    ioopm_list_t *new_list = ioopm_linked_list_create();
    new_list->element = 1;
    
    ioopm_linked_list_append(new_list, 2);
    ioopm_linked_list_append(new_list, 3);
    CU_ASSERT_PTR_NOT_NULL(new_list->next);
    // Måste vara remove function
   // ioopm_linked_list_destroy(new_list);
   // CU_ASSERT_PTR_NULL(new_list);
  ioopm_linked_list_destroy(new_list);
}

void test_append_link(void)
{
    ioopm_list_t *new_list = ioopm_linked_list_create();
    new_list->element = 1;

    ioopm_linked_list_append(new_list, 2);

    CU_ASSERT_EQUAL(new_list->next->element, 2);

    ioopm_linked_list_destroy(new_list);
}

void test_prepend_link(void)
{
    ioopm_list_t *new_list = ioopm_linked_list_create();
    new_list->element = 1;
    
    ioopm_linked_list_prepend(&new_list, 2);
    CU_ASSERT_EQUAL(new_list->element, 2);

    ioopm_linked_list_destroy(new_list);
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
    (CU_add_test(my_test_suite, "Test for create_list functionality", test_create_list) == NULL) || 
    (CU_add_test(my_test_suite, "Test for destroy_list functionality", test_destroy_list) == NULL) ||
    (CU_add_test(my_test_suite, "Test for append_link functionality", test_append_link) == NULL) ||
    (CU_add_test(my_test_suite, "Test for prepend_link functionality", test_prepend_link) == NULL) ||
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