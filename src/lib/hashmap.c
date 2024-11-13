/**
 * @brief A generic hashmap implementation that uses linked lists to handle collisions.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/hashmap.h"
#include "lib/list.h"

static void hm_ll_node_free_function(void *node)
{
    struct HashMapLinkedListNode *hashmap_node = node;

    if (hashmap_node->hashmap->key_free_function != NULL)
    {
        hashmap_node->hashmap->key_free_function(hashmap_node->key);
    }

    if (hashmap_node->hashmap->value_free_function != NULL)
    {
        hashmap_node->hashmap->value_free_function(hashmap_node->value);
    }

    free(hashmap_node);
}

static int hm_ll_node_compare_function(void *a, void *b)
{
    struct HashMapLinkedListNode *node_a = a;
    struct HashMapLinkedListNode *node_b = b;

    return node_a->hashmap->key_compare_function(node_a->key, node_b->key);
}

/**
 * @brief Creates a new hashmap.
 * @param capacity The capacity of the hashmap.
 * @param hash_function A function that hashes a key to an index in the hashmap.
 * @param key_compare_function A function that compares two keys in the hashmap.
 * @param key_free_function A function that frees a key in the hashmap. Pass NULL if
 *                          the keys do not need to be freed when hm_free is called.
 * @param value_free_function A function that frees a value in the hashmap. Pass NULL if
 *                            the values do not need to be freed when hm_free is called.
 * @return A pointer to the created hashmap.
 */
struct HashMap *hm_create(size_t capacity, HashMapHashFunction hash_function,
                          HashMapKeyCompareFunction key_compare_function,
                          KeyFreeFunction key_free_function,
                          ValueFreeFunction value_free_function)
{
    struct HashMap *hashmap = malloc(sizeof(struct HashMap));
    if (hashmap == NULL)
    {
        return NULL;
    }

    hashmap->capacity = capacity;
    hashmap->hash_function = hash_function;
    hashmap->key_compare_function = key_compare_function;
    hashmap->key_free_function = key_free_function;
    hashmap->value_free_function = value_free_function;

    hashmap->buckets = malloc(capacity * sizeof(HashMapBucket));
    if (hashmap->buckets == NULL)
    {
        free(hashmap);

        return NULL;
    }

    for (size_t i = 0; i < capacity; i++)
    {
        hashmap->buckets[i] = ll_create(hm_ll_node_compare_function);
        if (hashmap->buckets[i] == NULL)
        {
            for (size_t j = 0; j < i; j++)
            {
                ll_free(hashmap->buckets[j], hm_ll_node_free_function);
            }

            free(hashmap->buckets);
            free(hashmap);

            return NULL;
        }
    }

    return hashmap;
}

/**
 * @brief Frees a hashmap.
 * @param hashmap A pointer to the hashmap to free.
 * @return void
 */
void hm_free(struct HashMap *hashmap)
{
    for (size_t i = 0; i < hashmap->capacity; i++)
    {
        ll_free(hashmap->buckets[i], hm_ll_node_free_function);
    }

    free(hashmap->buckets);
    free(hashmap);

    return;
}

/**
 * @brief Sets a key-value pair in a hashmap.
 * @param hashmap A pointer to the hashmap to set in.
 * @param key A pointer to the key to set.
 * @param value A pointer to the value to set.
 * @return 0 if the key-value pair was set successfully, -1 otherwise.
 */
int hm_set(struct HashMap *hashmap, void *key, void *value)
{
    size_t index = hashmap->hash_function(hashmap, key);

    struct HashMapLinkedListNode *node_value =
        malloc(sizeof(struct HashMapLinkedListNode));
    if (node_value == NULL)
    {
        return -1;
    }

    node_value->hashmap = hashmap;
    node_value->key = key;
    node_value->value = value;

    struct LinkedListNode *existing_node_with_key =
        ll_get_node_by_value(hashmap->buckets[index], node_value);

    if (existing_node_with_key == NULL)
    {
        ll_push(hashmap->buckets[index], node_value);
    }
    else
    {
        existing_node_with_key->value = node_value;
    }

    return 0;
}

/**
 * @brief Gets a value from a hashmap.
 * @param hashmap A pointer to the hashmap to get from.
 * @param key A pointer to the key to get.
 * @return A pointer to the value, or NULL if the key is not in the hashmap.
 */
void *hm_get(struct HashMap *hashmap, void *key)
{
    size_t index = hashmap->hash_function(hashmap, key);

    HashMapBucket *bucket = hashmap->buckets[index];
    struct LinkedListNode *current_node = bucket->head;

    while (current_node != NULL)
    {
        struct HashMapLinkedListNode *current_hashmap_node = current_node->value;

        if (hashmap->key_compare_function(current_hashmap_node->key, key) == 0)
        {
            return current_hashmap_node->value;
        }

        current_node = current_node->next;
    }

    return NULL;
}

/**
 * @brief Removes a key-value pair from a hashmap.
 * @param hashmap A pointer to the hashmap to remove from.
 * @param key A pointer to the key to remove.
 * @return 0 if the key-value pair was removed successfully, -1 otherwise.
 */
int hm_remove(struct HashMap *hashmap, void *key);
