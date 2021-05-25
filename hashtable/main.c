#include "hashtable.h"

int main() {
  hashtable_t* hashtable = ht_create(65536);

  ht_set(hashtable, "key1", "value1");
  ht_set(hashtable, "key2", "value2");
  ht_set(hashtable, "key3", "value3");

  ht_get(hashtable, "key1");
  return 0;
}