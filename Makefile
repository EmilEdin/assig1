CC = gcc
FLAGS = -Wall -g
# GCOVFLAGS
MEM = valgrind --leak-check=full


%.o: %.c %.h
	$(CC) $(FLAGS) $< -c

linked_list_test: linked_list.o linked_list_tests.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

test_ll: linked_list_test
	./linked_list_test

test_ll_mem: test_ll
	$(MEM) ./linked_list_test



hash_table_test: hash_table.c hash_table_tests.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

test_ht: hash_table_test
	./hash_table_test

test_ht_mem: hash_table_test linked_list_test
	$(mem) ./hash_table_test

	

freq_count: hash_table.c freq-count.c
	$(CC) $(FLAGS) freq-count.c -o freq_count

freq_small: freq_count small.txt
	$(MEM) ./freq_count small.txt

freq_1k: freq_count 1k-long-words.txt
	$(MEM) ./freq_count 1k-long-words.txt

freq_10k: freq_count 10k-words.txt
	$(MEM) ./freq_count 10k-words.txt

freq_16k: freq_count 16k-words.txt
	$(MEM) ./freq_count 16k-words.txt



all_mem: test_ll_mem test_ht_mem
	test_ll_mem test_ht_mem




clean:
	rm -f *.o
	rm -f test_ht test_ll

.PHONY: test clean