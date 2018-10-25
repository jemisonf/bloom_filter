#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "bloom_filter.h"
#include "hash.h"

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
int main(int argc, char* argv[]) {
    srand(time(NULL));
    printf("Hello world!\n");
    test_hash();
    return 0;
}