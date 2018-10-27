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

    self->hashes = (struct hash_collection*) malloc(sizeof(struct hash_collection));
    self->hashes->hashes = (struct hash **) malloc(num_hashes * sizeof(struct hash*));

    for (int i = 0; i < num_hashes; i++) {
        self->hashes->hashes[i] = hash();
        printf("%p\n", self->hashes->hashes[i]);
    }

    self->hashes->num_hashes = num_hashes;

    self->bit_array = (int*) malloc(array_size * sizeof(int));
    self->bit_array_size = array_size;
    // memset(self->bit_array, 0, array_size * sizeof(int));
    for (int i = 0; i < num_words; i++) {
        /*
        for (int j = 0; j < self->hashes->num_hashes; j++) {
            int hash = abs(hash_string(self->hashes->hashes[j], words[i]) % array_size);
            self->bit_array[hash] = 1;
        }
        */
       bloom_filter_add_word(self, words[i]);
    }
    return self;
}

void bloom_filter_add_word(struct bloom_filter* self, const char* word) {
    for (int i = 0; i < self->hashes->num_hashes; i++) {
        int hash = hash_string(self->hashes->hashes[i], word) % self->bit_array_size;
        self->bit_array[hash] = 1;
    }

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