#include <stdio.h>

#include "hash.h"

struct bloom_filter;

struct bloom_filter * bloom_filter(int num_hashes, int size, const char** words, int num_words);

struct bloom_filter * bloom_filter_blank(int num_hashes, int size);

int bloom_filter_contains(struct bloom_filter* self, const char* word);

void bloom_filter_add_word(struct bloom_filter* self, const char* word);

void bloom_filter_free(struct bloom_filter * self);