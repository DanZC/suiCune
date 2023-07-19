#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct Entry {
    char* key;
    void* value;
} Entry;

typedef struct Hashtable {
    int size;
    int count;
    Entry* entries;
} Hashtable;

// Function to create a new hashtable
Hashtable* createHashtable();

// Hash function
unsigned int hash(const char* key, const int size);

// Function to calculate the hash slot for a given key and hashtable size
unsigned int calculateHashSlot(const char* key, int size);

// Function to resize the hashtable
void resizeHashtable(Hashtable* hashtable);

// Function to check if an entry is occupied
int isEntryOccupied(const Entry* entry);

// Function to get the next slot based on the current slot and hashtable size
unsigned int getNextSlot(unsigned int currentSlot, int size);

// Function to create a new entry in the hashtable
void createNewEntry(Entry* entry, const char* key, void* value);

// Function to set a value in the hashtable
void setHashtableValue(Hashtable* hashtable, const char* key, void* value);

// Function to get a value from the hashtable
void* get(Hashtable* hashtable, const char* key);

// Function to delete an entry from the hashtable
void deleteEntry(Hashtable* hashtable, const char* key);

// Function to free the hashtable
void freeHashtable(Hashtable* hashtable);

#endif  // HASHTABLE_H