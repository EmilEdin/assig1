# assig1

felhantering

hashtalbe size fel

Varför 505-511 hash_table_tests

gcc -g -o freq_count freq-count.c
valgrind --leak-check=full ./freq_count 1k-long-words.txt
gcc -g  hash_Table.c hash_table_tests.c -o hash_table -lcunit