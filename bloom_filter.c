#include "bloom_filter.h"

struct hash_collection {
    struct hash** hashes;
    int num_hashes;
};

struct bloom_filter {
    struct hash_collection * hashes;
    int * bit_array;
    int bit_array_size;
};

struct bloom_filter* bloom_filter(int num_hashes,
                                    int array_size,
                                    const char** words,
                                    int num_words) {
    
    struct bloom_filter * self = (struct bloom_filter*) malloc(sizeof(struct bloom_filter));
    self->hashes->hashes = (struct hash **) malloc(num_hashes * sizeof(struct hash*));
    for (int i = 0; i < num_hashes; i++) {
        self->hashes->hashes[i] = hash();
    }
    self->hashes->num_hashes = num_hashes;
    // allocate bit array[size]
    self->bit_array = (int*) malloc(array_size * sizeof(int));
    self->bit_array_size = array_size;
    memset(&(self->bit_array), 0, array_size * sizeof(int));

    // for each word in words
    for (int i = 0; i < num_words; i++) {
        // for each hash in hashes
        for (int j = 0; j < self->hashes->num_hashes; j++) {
            // get hash of word and truncate to size
            int hash = hash_string(self->hashes->hashes[j], words[i]) % array_size;
            // set bit_array[hash] to 1
            self->bit_array[hash] = 1;

        }
    }
    return self;

}

int bloom_filter_contains(struct bloom_filter* self, const char* word) {
    // while hash of word is in self return 0 if hash of word not in self
    for (int i = 0; i < self->hashes->num_hashes; i++) {
        int hash = hash_string(self->hashes->hashes[i], word) % self->bit_array_size;
        if (self->bit_array[hash] == 0) {
            return 0;
        }
    }
    // return 1
    return 1;
}

void bloom_filter_free(struct bloom_filter * self) {
    for (int i = 0; i < self->hashes->num_hashes; i++) {
        hash_free(self->hashes->hashes[i]);
    }
    free(self->hashes);
    free(self);
}