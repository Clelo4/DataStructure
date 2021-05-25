#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include <limits.h>

#define UINT32_MAX 0xffffffffU

typedef unsigned int u_int32_t;

struct entry_s {
  char *key;
  char *value;
  struct entry_s* next;
};

typedef struct entry_s entry_t;
struct hashtable_s {
  int size;
  struct entry_s **table;
};

typedef struct hashtable_s hashtable_t;

// create a new hashtable
hashtable_t* ht_create(int size);
// Delete a hashtable
void ht_delete(hashtable_t* hashtable);
// hash a string for a particular hash table
u_int32_t ht_hash(hashtable_t* hashtable, char *key);
// create a key-value pair
entry_t* ht_newpair(char *key, char* value);
// insert a key-value pari into a hash table;
void ht_set(hashtable_t* hashtable, char* key, char* value);
// Retrieve a key-value pair from a hash table.
char* ht_get(hashtable_t* hashtable, char* key);

#endif