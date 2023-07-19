#include "tmx_utils.h"
#include "hashtable.h"

void* mk_hashtable(unsigned int initial_size) {
    return (void*)createHashtable();
}

//void hashtable_set(void* hashtable, const char* key, void* val, hashtable_entry_deallocator deallocator) {
    //setHashtableValue((Hashtable*)hashtable, key, val);
//}

void* hashtable_get(void* hashtable, const char* key) {
    return get((Hashtable*)hashtable, key);
}

void hashtable_rm(void* hashtable, const char* key, hashtable_entry_deallocator deallocator) {
    deleteEntry((Hashtable*)hashtable, key);
}

void free_hashtable(void* hashtable, hashtable_entry_deallocator deallocator) {
    freeHashtable((Hashtable*)hashtable);
}

void hashtable_foreach(void* hashtable, hashtable_foreach_functor functor, void* userdata) {
    Hashtable* ht = (Hashtable*)hashtable;
    for (int i = 0; i < ht->size; i++) {
        if (ht->entries[i].key != NULL) {
            functor(ht->entries[i].key, ht->entries[i].value, userdata);
        }
    }
}
