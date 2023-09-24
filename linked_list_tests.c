#include "linked_list.h"
#include <CUnit/Basic.h>
#include <stdbool.h>


typedef struct list ioopm_list_t;
typedef struct link ioopm_link_t;

struct link
{
    int element;
    ioopm_link_t *next;
};

struct list
{
    ioopm_link_t *first;
    ioopm_link_t *last;
    int size;
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
    CU_ASSERT_PTR_NULL(new_list->first);
    CU_ASSERT_PTR_NULL(new_list->last);

    ioopm_linked_list_destroy(new_list);
}


void test_destroy_list(void)
{
    ioopm_list_t *new_list = ioopm_linked_list_create();

    ioopm_linked_list_append(new_list, 2);
    ioopm_linked_list_append(new_list, 3);
    CU_ASSERT_PTR_NOT_NULL(new_list->last);
    // Måste vara remove function
   // ioopm_linked_list_destroy(new_list);
   // CU_ASSERT_PTR_NULL(new_list);
  ioopm_linked_list_destroy(new_list);
}

void test_append_link(void)
{
    ioopm_list_t *new_list = ioopm_linked_list_create();

    ioopm_linked_list_append(new_list, 2);

    CU_ASSERT_EQUAL(new_list->last->element, 2);

    ioopm_linked_list_destroy(new_list);
}

void test_prepend_link(void)
{
    ioopm_list_t *new_list = ioopm_linked_list_create();
    
    ioopm_linked_list_prepend(new_list, 2);
    CU_ASSERT_EQUAL(new_list->first->element, 2);
    ioopm_linked_list_prepend(new_list, 5);
    CU_ASSERT_EQUAL(new_list->first->element, 5);
    ioopm_linked_list_prepend(new_list, 1239013);
    CU_ASSERT_EQUAL(new_list->first->element, 1239013);

    ioopm_linked_list_destroy(new_list);
}

void test_insert_link(void) {
  ioopm_list_t *new_list = ioopm_linked_list_create();
    
    ioopm_linked_list_prepend(new_list, 2);
    ioopm_linked_list_prepend(new_list, 5);
    ioopm_linked_list_prepend(new_list, 124);
    // Checks that inserting at before first and after last element works.
    ioopm_linked_list_insert(new_list, 0, 69);
    CU_ASSERT_EQUAL(new_list->first->element, 69);
    ioopm_linked_list_insert(new_list, ioopm_linked_list_size(new_list), 100);
    CU_ASSERT_EQUAL(new_list->last->element, 100);

    ioopm_linked_list_insert(new_list, 2, 1337);
    CU_ASSERT_EQUAL(new_list->first->next->element, 1337);


    ioopm_linked_list_destroy(new_list);
}

void test_size_list(void) {
  ioopm_list_t *new_list = ioopm_linked_list_create();
    
  for (int i = 0; i < 20; i++) {
    ioopm_linked_list_prepend(new_list, i);
  }
  CU_ASSERT_EQUAL(new_list->size, 20);

  ioopm_linked_list_destroy(new_list);
}

void test_get_link(void)
{
    ioopm_list_t *new_list = ioopm_linked_list_create();
    
    ioopm_linked_list_append(new_list, 2);
    ioopm_linked_list_append(new_list, 5);
    ioopm_linked_list_append(new_list, 124);

    CU_ASSERT_EQUAL(ioopm_linked_list_get(new_list, 2), 124)

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
    (CU_add_test(my_test_suite, "Test for insert_link functionality", test_insert_link) == NULL) ||
    (CU_add_test(my_test_suite, "Test for size_link functionality", test_size_list) == NULL) ||
    (CU_add_test(my_test_suite, "Test for get_link functionality", test_get_link) == NULL) ||
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