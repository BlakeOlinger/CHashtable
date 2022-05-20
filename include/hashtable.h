#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdint.h>

#define NIL 0

typedef struct hashtable *hashtable;

uint64_t as_key(const char *str);

void free_hashtable(hashtable ht);

uint64_t hash(uint64_t num_slots, uint64_t key);

void hashtable_delete(const char *key, hashtable ht);

void hashtable_insert(const char *key, uint64_t value, hashtable ht);

uint64_t hashtable_search(const char *key, const hashtable ht);

hashtable malloc_hashtable(uint64_t capacity);

#endif
