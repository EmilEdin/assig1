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
    ioopm_linked_list_append(new_list, 10);
    ioopm_linked_list_append(new_list, 9);
    ioopm_linked_list_append(new_list, 6);
    CU_ASSERT_EQUAL(new_list->last->element, 6);
    CU_ASSERT_EQUAL(new_list->first->element, 2);
    CU_ASSERT_EQUAL(new_list->first->next->element, 10);

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
    
    int size = ioopm_linked_list_size(new_list);
    for (int i = 0; i < size; i++) {
      ioopm_linked_list_insert(new_list, i, i*i);
    }

    ioopm_linked_list_destroy(new_list);
}

void test_size_n_empty_list(void) {
  ioopm_list_t *new_list = ioopm_linked_list_create();
  bool is_empty = ioopm_linked_list_is_empty(new_list);
  CU_ASSERT_TRUE(is_empty);
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

void test_remove_element_from_list(void) {
  ioopm_list_t *new_list = ioopm_linked_list_create();
  ioopm_linked_list_prepend(new_list, 1);
  ioopm_linked_list_prepend(new_list, 100);
  ioopm_linked_list_prepend(new_list, 69);
  ioopm_linked_list_prepend(new_list, 420);
  ioopm_linked_list_prepend(new_list, 3);
  ioopm_linked_list_prepend(new_list, 20);
  
  // Tests for removing first element
  int removed_first_element = ioopm_linked_list_remove(new_list, 0);
  CU_ASSERT_EQUAL(removed_first_element, 20); // Ensure that the removed element is 20
  CU_ASSERT_EQUAL(new_list->first->element, 3);
  CU_ASSERT_EQUAL(new_list->last->element, 1);
  // Tests for removing last element
  int remove_last_element = new_list->size - 1;
  int removed_last_element = ioopm_linked_list_remove(new_list, remove_last_element);
  CU_ASSERT_EQUAL(removed_last_element, 1);
  CU_ASSERT_EQUAL(new_list->last->element, 100);
  // Tests for removing element in the middle
  int removed_element = ioopm_linked_list_remove(new_list, 2);
  CU_ASSERT_EQUAL(removed_element, 69);
  // Check that the rest of the elements are in the list and in same order
  CU_ASSERT_EQUAL(new_list->first->element, 3);
  CU_ASSERT_EQUAL(new_list->first->next->element, 420);
  CU_ASSERT_EQUAL(new_list->last->element, 100);

  int another_removed_element = ioopm_linked_list_remove(new_list, 1);
  CU_ASSERT_EQUAL(another_removed_element, 420);
  // Check that the rest of the elements are in the list and in same order
  CU_ASSERT_EQUAL(new_list->first->element, 3);
  CU_ASSERT_EQUAL(new_list->first->next->element, 100);
  CU_ASSERT_EQUAL(new_list->last->element, 100);

  ioopm_linked_list_destroy(new_list);
}

void test_clear_list(void) {
  ioopm_list_t *new_list = ioopm_linked_list_create();
  ioopm_linked_list_prepend(new_list, 1);
  ioopm_linked_list_prepend(new_list, 100);
  ioopm_linked_list_prepend(new_list, 69);
  ioopm_linked_list_prepend(new_list, 420);
  ioopm_linked_list_prepend(new_list, 3);
  ioopm_linked_list_prepend(new_list, 20);
  ioopm_linked_list_prepend(new_list, 3);
  
  ioopm_linked_list_clear(new_list);

  CU_ASSERT_PTR_NULL(new_list->first);
  CU_ASSERT_PTR_NULL(new_list->last);

  ioopm_linked_list_destroy(new_list);
  
}

bool is_even(int value, void *extra)
{
    if(value % 2 == 0) {
        return true;
    } else {
        return false;
    }
}

void test_linked_list_all(void)
{
    ioopm_list_t *new_list = ioopm_linked_list_create();

    CU_ASSERT_TRUE(ioopm_linked_list_all(new_list, is_even, new_list));

    ioopm_linked_list_prepend(new_list, 2);
    ioopm_linked_list_prepend(new_list, 100);
    ioopm_linked_list_prepend(new_list, -68);

    CU_ASSERT_TRUE(ioopm_linked_list_all(new_list, is_even, new_list));

    ioopm_linked_list_prepend(new_list, 69);

    CU_ASSERT_FALSE(ioopm_linked_list_all(new_list, is_even, new_list));

    ioopm_linked_list_destroy(new_list);
}

void test_linked_list_any(void)
{
    ioopm_list_t *new_list = ioopm_linked_list_create();

    CU_ASSERT_FALSE(ioopm_linked_list_any(new_list, is_even, new_list)); 

    ioopm_linked_list_prepend(new_list, 3);
    ioopm_linked_list_prepend(new_list, 15);
    ioopm_linked_list_prepend(new_list, -68);

    CU_ASSERT_TRUE(ioopm_linked_list_any(new_list, is_even, new_list));

    ioopm_linked_list_remove(new_list, 0);
    ioopm_linked_list_prepend(new_list, 69);

    CU_ASSERT_FALSE(ioopm_linked_list_any(new_list, is_even, new_list));

    ioopm_linked_list_destroy(new_list);
}

void is_odd_add_one(int *elem, void *extra) 
{
    if(*elem % 2 != 0) {
        *elem = *elem + 1;
    }
}

void multiply_by(int *elem, void *extra)
{
    int *plol = extra;
    *elem = (*elem) * (*plol);
}


void test_linked_list_fun_all(void)
{
    ioopm_list_t *new_list = ioopm_linked_list_create();

    ioopm_linked_list_apply_to_all(new_list, is_odd_add_one, new_list); 
    CU_ASSERT_TRUE(ioopm_linked_list_all(new_list, is_even, new_list));

    ioopm_linked_list_prepend(new_list, 3);
    ioopm_linked_list_prepend(new_list, 15);
    ioopm_linked_list_prepend(new_list, -68);

    ioopm_linked_list_apply_to_all(new_list, is_odd_add_one, new_list);
    CU_ASSERT_TRUE(ioopm_linked_list_all(new_list, is_even, new_list));

    ioopm_linked_list_prepend(new_list, 2);
    ioopm_linked_list_prepend(new_list, 64);

    ioopm_linked_list_apply_to_all(new_list, is_odd_add_one, new_list);
    CU_ASSERT_TRUE(ioopm_linked_list_all(new_list, is_even, new_list));
    
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
    (CU_add_test(my_test_suite, "Test for get_link functionality", test_get_link) == NULL) ||
    (CU_add_test(my_test_suite, "Test for size_n_empty_link functionality", test_size_n_empty_list) == NULL) ||
    (CU_add_test(my_test_suite, "Test for remove_link functionality", test_remove_element_from_list) == NULL) ||
    (CU_add_test(my_test_suite, "Test for clearing the list", test_clear_list) == NULL) ||
    (CU_add_test(my_test_suite, "Test for linked_list_all functionality", test_linked_list_all) == NULL) ||
    (CU_add_test(my_test_suite, "Test for linked_list_any functionality", test_linked_list_any) == NULL) ||
    (CU_add_test(my_test_suite, "Test for apply_to_all functionality", test_linked_list_fun_all) == NULL) ||
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