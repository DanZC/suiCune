#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 100

// Define the Entry structure
typedef struct Entry {
    char* key;
    void* value;
} Entry;

// Define the Hashtable structure
typedef struct Hashtable {
    Entry* entries;
    int size;
    int count;
} Hashtable;

// Function to create a new hashtable
Hashtable* createHashtable() {
    Hashtable* hashtable = malloc(sizeof(Hashtable));
    hashtable->size = INITIAL_SIZE;
    hashtable->count = 0;
    hashtable->entries = malloc(sizeof(Entry) * hashtable->size);
    memset(hashtable->entries, 0, sizeof(Entry) * hashtable->size);
    return hashtable;
}

// Hash function
unsigned int hash(const char* key, const int size) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }

    value = value % size;

    return value;
}

// Function to calculate the hash slot for a given key and hashtable size
unsigned int calculateHashSlot(const char* key, int size) {
    unsigned int slot = hash(key, size);
    return slot;
}

// Function to resize the hashtable
void resizeHashtable(Hashtable* hashtable) {
    Entry* old_entries = hashtable->entries;
    int old_size = hashtable->size;

    int new_size = hashtable->size * 2;
    Entry* new_entries = malloc(sizeof(Entry) * new_size);
    memset(new_entries, 0, sizeof(Entry) * new_size);

    for (int i = 0; i < old_size; i++) {
        if (old_entries[i].key != NULL) {
            unsigned int slot = calculateHashSlot(old_entries[i].key, new_size);
            Entry* entry = &(new_entries[slot]);

            while (isEntryOccupied(entry)) {
                slot = getNextSlot(slot, new_size);
                entry = &(new_entries[slot]);
            }

            // Use initializer syntax to create a new Entry directly
            *entry = (Entry){ .key = strdup(old_entries[i].key), .value = old_entries[i].value };
        }
    }

    free(old_entries);

    hashtable->entries = new_entries;
    hashtable->size = new_size;
}

// Function to check if an entry is occupied
int isEntryOccupied(const Entry* entry) {
    return (entry->key != NULL);
}

// Function to get the next slot based on the current slot and hashtable size
unsigned int getNextSlot(unsigned int currentSlot, int size) {
    return (currentSlot + 1) % size;
}

// Function to create a new entry in the hashtable
void createNewEntry(Entry* entry, const char* key, void* value) {
    entry->key = strdup(key);
    entry->value = value;
}

// Function to set a value in the hashtable
void setHashtableValue(Hashtable* hashtable, const char* key, void* value) {
    if (hashtable->count * 2 >= hashtable->size) {
        resizeHashtable(hashtable);
    }

    unsigned int slot = hash(key, hashtable->size);
    Entry* entry = &(hashtable->entries[slot]);

    while (entry->key != NULL) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return;
        }

        slot = (slot + 1) % hashtable->size;
        entry = &(hashtable->entries[slot]);
    }

    entry->key = strdup(key);
    entry->value = value;
    hashtable->count++;
}

// Function to get a value from the hashtable
void* get(Hashtable* hashtable, const char* key) {
    unsigned int slot = hash(key, hashtable->size);
    Entry* entry = &(hashtable->entries[slot]);

    while (entry->key != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }

        slot = (slot + 1) % hashtable->size;
        entry = &(hashtable->entries[slot]);
    }

    return NULL;
}

// Function to delete an entry from the hashtable
void deleteEntry(Hashtable* hashtable, const char* key) {
    unsigned int slot = hash(key, hashtable->size);
    Entry* entry = &(hashtable->entries[slot]);

    while (entry->key != NULL) {
        if (strcmp(entry->key, key) == 0) {
            free(entry->key);
            entry->key = NULL;
            entry->value = NULL;
            hashtable->count--;
            return;
        }

        slot = (slot + 1) % hashtable->size;
        entry = &(hashtable->entries[slot]);
    }
}

// Function to free the hashtable
void freeHashtable(Hashtable* hashtable) {
    for (int i = 0; i < hashtable->size; i++) {
        if (hashtable->entries[i].key != NULL) {
            free(hashtable->entries[i].key);
        }
    }

    free(hashtable->entries);
    free(hashtable);
}
