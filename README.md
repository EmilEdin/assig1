# assig1

Hantera 0 och negative värden som key

Hash_table

felhantering

TEST:
    coverage med lcov
    uppdelning till fler test

dokumentation

gcc -g -o freq_count freq-count.c
valgrind --leak-check=full ./freq_count 1k-long-words.txt
gcc -g  hash_Table.c hash_table_tests.c -o hash_table -lcunit