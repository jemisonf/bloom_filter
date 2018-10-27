#include "hash.h"

struct hash {
    int seed;
};

struct hash * hash() {
    struct hash * new_hash = (struct hash *) malloc(sizeof(struct hash)); 

    new_hash->seed = rand();

    return new_hash;
}

unsigned int hash_string(struct hash* self, const char* string) {
    return PMurHash32(self->seed, string, strlen(string));
}

void hash_free(struct hash* self) {
    free(self);
}