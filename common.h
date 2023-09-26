#define int_elem(x) (elem_t) { .int_value=(x) }
#define ptr_elem(x) (elem_t) { .string_value=(x) }
#define ioopm_int_str_ht_insert(ht, i, s) \
   ioopm_hash_table_insert(ht, int_elem(i), ptr_elem(s))

typedef union { 
  int   int_value;
  char *string_value;
  void *void_value;
} elem_t;

/// Compares two elements and returns true if they are equal
typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);