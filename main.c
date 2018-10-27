#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "bloom_filter.h"
#include "hash.h"
#include "parse_args.h"
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
        "!!!gerard!!!",
        "d065060202",
    };

    printf("Creating bloom filter\n");
    struct bloom_filter * bf = bloom_filter(3, 200, words, 9);

    printf("test1\n");
    assert(bloom_filter_contains(bf, "blah") == 1);
    assert(bloom_filter_contains(bf, "d065060202") == 1);
    assert(bloom_filter_contains(bf, "!!!gerard!!!") == 1);
    printf("test2\n");
    assert(bloom_filter_contains(bf, "notinthearray") == 0);
    printf("test3\n");
    assert(bloom_filter_contains(bf, "this is a very long string") == 1);

    printf("Freeing bf\n");
    bloom_filter_free(bf);
}


void test_build_bloom_filter() {
    struct bloom_filter* bf = bloom_filter(3, 500000000, 0, 0);
    int num_pwds = get_line_count("dictionary.txt");
    FILE* fp = fopen("dictionary.txt", "r");
    char* temp_str = malloc(256 * sizeof(char));
    for (int i = 0; i < num_pwds; i++) {
        // temp_str = readline(fp);
        readline(fp, temp_str);
        bloom_filter_add_word(bf, temp_str);
        assert(bloom_filter_contains(bf, temp_str) == 1);
        // free(temp_str);
    }
    fclose(fp);
    assert(bloom_filter_contains(bf, "!magnum") == 1);
    assert(bloom_filter_contains(bf, "!!!gerard!!!") == 1);
    assert(bloom_filter_contains(bf, "010289") == 1);
    assert(bloom_filter_contains(bf, "d065050202") == 1);
    assert(bloom_filter_contains(bf, "~~~~~~~~~~    ") == 1);
    assert(bloom_filter_contains(bf, "testestest") == 0);
    bloom_filter_free(bf);
}

void run_bloom_filter(int num_hashes, const char* dictionary, const char* input_file, const char* output_file) {
    struct bloom_filter * bf = bloom_filter(num_hashes, 500000, 0, 0);
    int lines = get_line_count(dictionary);
    FILE * fp_dict = fopen(dictionary, "r+");
    // char* temp_str = (char*) malloc(256 * sizeof(char));
    char temp_str[10000];
    for (int i = 0; i < lines; i++) {
        readline(fp_dict, temp_str);
        bloom_filter_add_word(bf, temp_str);
    }
    fclose(fp_dict);

    lines = get_line_count(input_file);
    FILE * fp_input = fopen(input_file, "r+");
    FILE * fp_output = fopen(output_file, "w+");
    for (int i = 0; i < lines; i++) {
        readline(fp_dict, temp_str);
        int result = bloom_filter_contains(bf, temp_str);
        if (result == 1) {
            fprintf(fp_output, "Maybe\n");
        } else {
            fprintf(fp_output, "No\n");
        }
    }
    fclose(fp_input);
    fclose(fp_output);
    bloom_filter_free(bf);
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    struct args * a = parse_args(argc, argv);
    run_bloom_filter(3, a->dictionary, a->input_file, a->output_files[0]);
    run_bloom_filter(5, a->dictionary, a->input_file, a->output_files[1]);
    free(a);
    return 0;
}