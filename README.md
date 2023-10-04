# assig1

# How to run the program
gcc -g -o freq_count freq-count.c
valgrind --leak-check=full ./freq_count 1k-long-words.txt
gcc -g  hash_Table.c hash_table_tests.c -o hash_table -lcunit

/* Line and branch coverage using gcov */
* linked_list.c 100% 
* hash_table.c 99.51% // int_compare function not read

# Brief program documentation
* The hash table is implemented with a dummy entry.
* The linked list is NOT implemented with a sentinel link.
* When we create a hash table the function ioopm_hash_table_create takes in to arguments, if the first argument (hash_fun) is NULL then we treat keys as ints, otherwise strings. If the second argument (eq_fun) is NULL, then values are ints, otherwise strings. 
* If a function has an index argument, we use assert in our function to make sure we do not remove or acess memory out of bounds. When it comes to types that we mentioned previously, it's a precondition that is also specified in the repsective .h file. 

# Initial Profiling Results
/* Small.txt */
// For each input, what are the top 3 functions?
Number of calls / same as Each % time, all functions take up 0s
1. ioopm_linked_list_append
2. key_equiv
3. string_sum_hash
// For each input, what are the top 3 functions in your code (that you have written), or is it library functions?
1. ioopm_linked_list_append
2. key_equiv
3. ioopm_linked_list_create/destroy // Annars string_sum_hash

/* 1k-long-words.txt */
// For each input, what are the top 3 functions?
Number of calls / same as Each % time, all functions take up 0s
1. ioopm_linked_list_append
2. key_equiv
3. string_sum_hash
// For each input, what are the top 3 functions in your code (that you have written), or is it library functions?
1. ioopm_linked_list_append
2. key_equiv
3. ioopm_linked_list_create/destroy // Annars string_sum_hash

/* 10k-words.txt */
// For each input, what are the top 3 functions?
Number of calls
1. ioopm_linked_list_append
2. key_equiv
3. string_sum_hash
// For each input, what are the top 3 functions in your code (that you have written), or is it library functions?
1. ioopm_linked_list_append
2. key_equiv
3. ioopm_linked_list_create/destroy // Annars string_sum_hash
Each % time
Inconsistent results

/* 16k-words.txt */
// For each input, what are the top 3 functions?
1. ioopm_linked_list_append
2. key_equiv
3. string_sum_hash
// For each input, what are the top 3 functions in your code (that you have written), or is it library functions?
1. ioopm_linked_list_append
2. key_equiv
3. ioopm_linked_list_create/destroy // Annars string_sum_hash
Each % time
// For each input, what are the top 3 functions?
1. ioopm_hash_table_size / links_destroy
2. ioopm_hash_table_values / ioopm_hash_table_keys / linked_list_append
// For each input, what are the top 3 functions in your code (that you have written), or is it library functions?
1. ioopm_hash_table_size / links_destroy
2. ioopm_hash_table_values / ioopm_hash_table_keys / linked_list_append

Results:
/* Are the top 3 functions in your code consistent across the inputs? Why? Why not? */
The top 3 functions are consistent in terms of the number of calls. When it comes to the time the functions take up 
when it runs we don't get any time percentage on these small files so we are uncertain as to the answer. In the 10k words file, the top 3 functions are not consistent in terms of time, while the 16k words file are also not consistent but a few functions share the top 3 spot in terms of time. 

/* Do the results correspond with your expectations? */
When it comes to number of calls we expected it to be the same across inputs. When it comes to the time spent on each function, we had a general understanding, since those top functions iterate through the whole hash table or linked list. But we did not expect that ioopm_hash_table_size would be top 3 because we thought it was not called very often. We also did not expect the append function to take up a lot of time the function takes constant time, but considering we call it a lot it makes sense. 

As to the smaller files we do not really know the behaviour but we expect similiar results. When it comes the 10k word file the result of the time spent was not expected as we thought it would be quite consistent when program runs multiple times. That was not the case for the most part but generally there was a pattern of the top functions, however not the top 3. 

/* Based on these results, do you see a way to make your program go faster? */
Yes, since size takes up a lot of time in atleast the bigger files, we could make the function run in constant time by having an extra struct component that would track the size of the hash table without iterating through the whole hash table each time we want to know the size. So each time we insert or remove an element, we would have to increase vice versa decrease the size variable in the hash table struct. When it comes to append we do not know, because it takes constant time, it just takes up a lot of time since we call it a lot during the program. 

// We obtained the numbers using gprof //


