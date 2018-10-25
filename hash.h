#include <stdlib.h>
#include <string.h>

#include "lib/PMurHash.h"

struct hash;

struct hash * hash();

int hash_string(struct hash* self, const char * string);

void hash_free(struct hash* self);

