/**
 * @brief A generic hashmap implementation that uses linked lists to handle collisions.
 */

#ifndef __HASHMAP_H
#define __HASHMAP_H

#include <stddef.h>

#include "lib/list.h"

/**
 * @struct HashMapEntry
 * @brief The value stored in a LinkedListNode in a hashmap bucket.
 */
struct HashMapEntry
{
    void *key;
    void *value;
};

/**
 * @brief A function that frees a hash map entry consisting of a key and a value.
 * @param entry A pointer to the entry to free.
 * @return void
 *
 * This function should not free the entry pointer itself. Only the key and value.
 */
typedef void (*HashMapEntryFreeFunction)(struct HashMapEntry *);

struct HashMap;

/**
 * @brief A hash function that hashes a generic key to an index in a hashmap.
 * @param hashmap A pointer to the hashmap to hash into.
 * @param key A pointer to the key to hash.
 * @return The index in the hashmap to hash the key to.
 */
typedef size_t (*HashMapHashFunction)(struct HashMap *, void *);

/**
 * @brief A function that compares two generic keys.
 * @param key1 The first key to compare.
 * @param key2 The second key to compare.
 * @return 0 if the keys are equal, else a non-zero value.
 */
typedef int (*HashMapKeyCompareFunction)(void *, void *);

typedef struct LinkedList HashMapBucket;

/**
 * @struct HashMap
 * @brief A generic hashmap.
 *
 * This hashmap contains a capacity, a pointer to its buckets,
 * as well as pointers to a hash function and key compare function.
 */
struct HashMap
{
    size_t capacity;
    HashMapBucket **buckets;
    HashMapHashFunction hash_function;
    HashMapKeyCompareFunction key_compare_function;
};

/**
 * @brief Creates a new hashmap.
 * @param capacity The capacity of the hashmap.
 * @param hash_function A function that hashes a key to an index in the hashmap.
 * @param key_compare_function A function that compares two keys in the hashmap.
 * @return A pointer to the created hashmap.
 */
struct HashMap *hm_create(size_t capacity, HashMapHashFunction hash_function,
                          HashMapKeyCompareFunction key_compare_function);
/**
 * @brief Frees a hashmap.
 * @param hashmap A pointer to the hashmap to free.
 * @param entry_free_function A function that frees an entry in the hashmap.
 *                           Pass NULL if the entries do not need to be freed.
 * @return void
 */
void hm_free(struct HashMap *hashmap, HashMapEntryFreeFunction entry_free_function);

/**
 * @brief Sets a key-value pair in a hashmap.
 * @param hashmap A pointer to the hashmap to set in.
 * @param key A pointer to the key to set.
 * @param value A pointer to the value to set.
 * @return 0 if the key-value pair was set successfully, -1 otherwise.
 */
int hm_set(struct HashMap *hashmap, void *key, void *value);

/**
 * @brief Gets a value from a hashmap.
 * @param hashmap A pointer to the hashmap to get from.
 * @param key A pointer to the key to get.
 * @return A pointer to the value, or NULL if the key is not in the hashmap.
 */
void *hm_get(struct HashMap *hashmap, void *key);

/**
 * @brief Removes a key-value pair from a hashmap.
 * @param hashmap A pointer to the hashmap to remove from.
 * @param key A pointer to the key to remove.
 * @return A pointer to the removed value, or NULL if the key is not in the hashmap.
 */
void *hm_remove(struct HashMap *hashmap, void *key);

#endif
