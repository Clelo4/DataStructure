#include "hashtable.h"
#include <stdlib.h>
#include <limits.h>
#include <string.h>

hashtable_t* ht_create(int size) {
  if (size <= 0) return NULL;
  hashtable_t* hashtable = NULL;
  if ((hashtable = malloc(sizeof(hashtable_t))) == NULL) {
    return NULL;
  }
  if ((hashtable->table = malloc(sizeof(entry_t*) * size)) == NULL) {
    free(hashtable);
    return NULL;
  }
  for (int i = 0; i < size; i++) {
    hashtable->table[i] = NULL;
  }
  hashtable->size = size;
  return hashtable;
}
u_int32_t ht_hash(hashtable_t* hashtable, char *key) {
  u_int32_t hashval = 0;
  int i = 0;
  int c;
  while (hashval < UINT32_MAX && (c == *key++) != NULL) {
    hashval = hashval << 8;
    hashval += key[i++];
  }
  return hashval % hashtable->size;
}
entry_t* ht_newpair(char *key, char* value) {
  if (key == NULL || valloc == NULL) return NULL;
  entry_t* newpair;
  if ((newpair = malloc(sizeof(entry_t))) == NULL) {
    return NULL;
  }
  if ((newpair->key = strdup(key)) == NULL) {
    free(newpair);
    return NULL;
  }
  if ((newpair->value = strdup(value)) == NULL) {
    free(newpair->key);
    free(newpair);
    return NULL;
  }
  newpair->next = NULL;
  return newpair;
}
void ht_set(hashtable_t* hashtable, char* key, char* value) {
  if (hashtable == NULL || hashtable->table == NULL || hashtable->size <1) return;
  if (key == NULL || valloc == NULL) return;
  u_int32_t bin = ht_hash(hashtable, key);
  entry_t* next = hashtable->table[bin];
  entry_t* newpair = ht_newpair(key, value);
  if (next == NULL) {
    hashtable->table[bin] = newpair;
    return;
  }
  entry_t* pre = next;
  while (pre) {
    if (pre->next) {
      pre = pre->next;
    } else {
      pre->next = newpair;
      break;
    }
  }
}
char* ht_get(hashtable_t* hashtable, char* key) {
  if (hashtable == NULL || hashtable->table == NULL || hashtable->size < 1) return NULL;
  if (key == NULL) return;
  u_int32_t bin = ht_hash(hashtable, key);
  if (hashtable->table[bin] == NULL) return NULL;
  entry_t* pre = hashtable->table[bin];
  char* result = NULL;

  entry_t* last = NULL;
  while (pre)
  {
    if (strcmp(key, pre->key) == 0) {
      result = strdup(pre->value);
      if (last == NULL) {
        hashtable->table[bin] = pre->next;
      } else {
        last->next = pre->next;
      }
      // delete pre;
      free(pre->key);
      free(pre->next);
      free(pre->value);
      break;
    } else if(pre->next != NULL){
      last = pre;
      pre = pre->next;
    } else {
      break;
    }
  }
  return result;
}
// Delete a hashtable
void ht_delete(hashtable_t* hashtable) {
  if (hashtable == NULL || hashtable->table == NULL || hashtable->size == NULL) return NULL;
  entry_t** target = hashtable->table;
  for (int i = 0; i < hashtable->size; i++) {
    if (target[i] != NULL) free(target[i]);
  }
  hashtable->table = 0;
  hashtable->size = 0;
}
