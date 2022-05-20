#include <assert.h>
#include <stdlib.h>

#include "hashtable.h"

int main(void)
{
// str -> key
	assert(as_key("t") == 116);
	assert(as_key("pt") == 14452);
	assert(as_key("tp") != 14452);
// end: str -> key

// hash function
	assert(hash(12, 100) == 4);
// end: hash function

	hashtable ht = malloc_hashtable(12);

	hashtable_insert("Butter", 523, ht);
	assert(hashtable_search("Butter", ht) == 523);

	hashtable_insert("Biscuts", 832, ht);
	assert(hashtable_search("Biscuts", ht) == 832);

	hashtable_delete("Butter", ht);
	assert(hashtable_search("Butter", ht) == NIL);

	free_hashtable(ht);

	exit(0);
}
