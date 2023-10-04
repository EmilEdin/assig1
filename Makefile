CC = gcc
FLAGS = -Wall -g
GCOVFLAGS = -fprofile-arcs -ftest-coverage
MEM = valgrind --leak-check=full


%.o: %.c %.h
	$(CC) $(FLAGS) $<



linked_list_test: linked_list.o  linked_list_tests.c
	$(CC) $(FLAGS) $^ -o $@ -lcunit

test_ll: linked_list_test
	./linked_list_test

test_ll_mem: linked_list.o linked_list_test
	valgrind --leak-check=full ./linked_list_test



hash_table_test: hash_table.o hash_table_tests.c
	$(CC) $(FLAGS) $^ -o $@ -lcunit

test_ht: hash_table_test
	./hash_table_test

test_ht_mem: hash_table.o hash_table_test
	valgrind --leak-check=full ./hash_table_test


all: linked_list.o hash_table.o
	make linked_list.o	
	make hash_table.o


memtest:
	make test_ll_mem 
	make test_ht_mem
	

gcov_ht: hash_table.o 
	$(CC) $(GCOVFLAGS) $(FLAGS) -o hash_table hash_table.c hash_table_tests.c -lcunit
	./hash_table
	gcov hash_table.c

gcov_ll: linked_list.o 
	$(CC) $(GCOVFLAGS) -o linked_list linked_list.c linked_list_tests.c -lcunit
	./linked_list
	gcov linked_list.c


freq_count: hash_table.c freq-count.c
	$(CC) $(FLAGS) freq-count.c -o freq_count



freq_small: freq_count small.txt
	$(MEM) ./freq_count small.txt

gprof_small: freq-count.c
	$(CC) -pg freq-count.c -o freq_count
	./freq_count small.txt
	gprof freq_count gmon.out > prof_output



freq_1k: freq_count 1k-long-words.txt
	$(MEM) ./freq_count 1k-long-words.txt

gprof_1k: freq-count.c
	$(CC) -pg freq-count.c -o freq_count
	./freq_count 1k-long-words.txt
	gprof freq_count gmon.out > prof_output



freq_10k: freq_count 10k-words.txt
	$(MEM) ./freq_count 10k-words.txt

gprof_10k: freq-count.c
	$(CC) -pg freq-count.c -o freq_count
	./freq_count 10k-words.txt
	gprof freq_count gmon.out > prof_output



freq_16k: freq_count 16k-words.txt
	$(MEM) ./freq_count 16k-words.txt

gprof_16k: freq-count.c
	$(CC) -pg freq-count.c -o freq_count
	./freq_count 16k-words.txt
	gprof freq_count gmon.out > prof_output




clean:
	rm -f *.o
	rm -f test_ht test_ll memtest test_ht_mem test_ll_mem freq freq_10k freq_16k freq_1k freq_count freq_small gcov_ht gcov_ll 
	rm -f gprof_10k gprof_16k gprof_1k gprof_small

.PHONY: test clean