#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "bloom_filter.h"
#include "hash.h"
#include "parse_file.h"

char* get_str(const char* str) {
    char* str_out = (char*) malloc(strlen(str) * sizeof(char));
    memset(str_out, 0, strlen(str));
    strcpy(str_out, str);
    return str_out;
}
void test_hash() {
    struct hash * hash1 = hash(), * hash2 = hash();

    const char * test_str = "testblah", * test_str2 = "testblahblah";
    printf("Hash values\n");
    printf("Hash 1:\n");
    printf("\tHash of %s: %d\n\tHash of %s: %d\n", test_str, hash_string(hash1, test_str), test_str2, hash_string(hash1, test_str2));
    printf("Hash 2:\n");
    printf("\tHash of %s: %d\n\tHash of %s: %d\n", test_str, hash_string(hash2, test_str), test_str2, hash_string(hash2, test_str2));

    printf("\nTests\n");

    assert(hash_string(hash1, test_str) != hash_string(hash1, test_str2));
    printf("Passed: two different string should not hash to the same value\n");

    assert(hash_string(hash1, test_str) == hash_string(hash1, test_str));
    printf("Passed: the same string should hash to the same value\n");

    assert(hash_string(hash1, test_str) != hash_string(hash2, test_str));
    printf("Passed: two different hash functions should not give the same value\n");
    hash_free(hash1);
    hash_free(hash2);
}

void test_bloom_filter() {
    const char * words[] = {
        "blah",
        "blahblah",
        "test",
        "testtest",
        "a",
        "b",
        "this is a very long string",
    };

    printf("Creating bloom filter\n");
    struct bloom_filter * bf = bloom_filter(3, 200, words, 7);

    printf("test1\n");
    assert(bloom_filter_contains(bf, "blah") == 1);
    printf("test2\n");
    assert(bloom_filter_contains(bf, "notinthearray") == 0);
    printf("test3\n");
    assert(bloom_filter_contains(bf, "this is a very long string") == 1);

    printf("Freeing bf\n");
    bloom_filter_free(bf);
}


void build_bloom_filter() {
    struct bloom_filter* bf = bloom_filter(3, 500, 0, 0);
    int num_pwds = get_line_count("dictionary.txt");
    FILE* fp = fopen("dictionary.txt", "r");
    char* temp_str;
    for (int i = 0; i < num_pwds; i++) {
        printf("%d\n", i);
        temp_str = readline(fp);
        bloom_filter_add_word(bf, temp_str);
        free(temp_str);
    }
    printf("added all words\n");
}
int main(int argc, char* argv[]) {
    srand(time(NULL));
    printf("Hello world!\n");
    test_hash();
    test_bloom_filter();
    build_bloom_filter();
    return 0;
}