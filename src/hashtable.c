#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

#define KEY_SIZE 30

typedef struct $node
{
	char key[KEY_SIZE + 1];
	uint64_t value;
	struct $node *next;
} node;

struct hashtable
{
	uint64_t capacity;
	node **slots;
};

uint64_t as_key(const char *str)
{
	const size_t len = strlen(str);
	uint64_t key = 0;

	for (size_t i = 0, j = len - 1; i < len; ++i, --j)
	{
		key += str[i] * (uint64_t) pow(128, j);
	}

	return key;
}

node *get_node(const char *key, const hashtable ht)
{
	return ht->slots[hash(ht->capacity, as_key(key))];
}

void free_node(node *n)
{
	if (n->next != NULL)
	{
		free_node(n->next);
	}

	free(n);
}

void cpy_key(node *n, const char *key)
{
	for (int i = 0; i < KEY_SIZE; ++i)
	{
		n->key[i] = key[i];
		if (key[i] == '\0')
		{
			break;
		}
	}
	n->key[KEY_SIZE] = '\0';
}

node *malloc_node(const char *key, uint64_t value)
{
	node *new_node = malloc(sizeof(*new_node));
	assert(new_node != NULL);

	cpy_key(new_node, key);
	new_node->value = value;
	new_node->next = NULL;

	return new_node;
}

void free_hashtable(hashtable ht)
{
	for (uint64_t i = 0; i < ht->capacity; ++i)
	{
		if (ht->slots[i] == NULL)
		{
			continue;
		}

		free_node(ht->slots[i]);
	}
	free(ht);
}

uint64_t hash(uint64_t num_slots, uint64_t key)
{
	return key % num_slots;
}

void hashtable_delete(const char *key, hashtable ht)
{
	node *cur = get_node(key, ht);
	if (cur->value == NIL)
	{
		return;
	}

	do
	{
		if (strcmp(cur->key, key) == 0)
		{
			cur->key[0] = '\0';
			cur->value = NIL;
			return;
		}
		
		cur = cur->next;
	} while (cur != NULL);
}

void hashtable_insert(const char *key, uint64_t value, hashtable ht)
{
	node *cur = get_node(key, ht);
	if (cur->value == NIL)
	{
		cpy_key(cur, key);
		cur->value = value;
		return;
	}

	node *new_node = malloc_node(key, value);

	while (cur->next != NULL)
	{
		cur = cur->next;
	}

	cur->next = new_node;
}

uint64_t hashtable_search(const char *key, const hashtable ht)
{
	node *cur = get_node(key, ht);
	do
	{
		if (strcmp(key, cur->key) == 0)
		{
			return cur->value;
		}

		cur = cur->next;
	} while (cur != NULL);

	return NIL;
}

hashtable malloc_hashtable(uint64_t capacity)
{
	struct hashtable *new_ht = malloc(sizeof(*new_ht));
	assert(new_ht != NULL);

	new_ht->capacity = (uint64_t) (1.3 * capacity);
	node **new_slots = malloc(sizeof(*new_slots) * new_ht->capacity);
	assert(new_slots != NULL);
	for (uint64_t i = 0; i < new_ht->capacity; ++i)
	{
		node *new_node = malloc_node("", NIL);
		new_slots[i] = new_node;
	}

	new_ht->slots = new_slots;

	return new_ht;
}
