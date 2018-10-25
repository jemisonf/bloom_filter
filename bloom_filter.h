#include "hash.h"

struct bloom_filter;

struct bloom_filter * bloom_filter(int num_hashes, int size, const char** words, int num_words);

int bloom_filter_contains(struct bloom_filter* self, const char* word);