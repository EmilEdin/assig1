#pragma once

#define int_elem(x) (elem_t) { .int_value=(x) }
#define ptr_elem(x) (elem_t) { .string_value=(x) }

typedef union { 
  int   int_value;
  char *string_value;
  void *void_value;
} elem_t;

typedef int (*hash_function)(elem_t key);

/// Compares two elements and returns true if they are equal
typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);
