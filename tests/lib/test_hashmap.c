#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/hashmap.h"

size_t int_hash_function(struct HashMap *hm, void *key)
{
    return *(int *)key % hm->capacity;
};

int int_compare_function(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

void entry_free_function(struct HashMapEntry *entry)
{
    free(entry->key);
    free(entry->value);

    return;
}

void test_hm_create()
{
    printf("Testing hm_create\n");

    struct HashMap *hashmap = hm_create(10, int_hash_function, int_compare_function);

    assert(hashmap != NULL);
    assert(hashmap->capacity == 10);
    assert(hashmap->buckets != NULL);
    assert(hashmap->hash_function == int_hash_function);
    assert(hashmap->key_compare_function == int_compare_function);

    hm_free(hashmap, entry_free_function);

    printf("hm_create passed\n");

    return;
}

void test_hm_set()
{
    printf("Testing hm_set\n");

    struct HashMap *hashmap = hm_create(10, int_hash_function, int_compare_function);

    int *key = malloc(sizeof(int));
    *key = 0;
    int *value = malloc(sizeof(int));
    *value = 10;

    assert(hm_set(hashmap, key, value) == 0);
    assert(((struct HashMapEntry *)hashmap->buckets[0]->head->value)->key == key);
    assert(((struct HashMapEntry *)hashmap->buckets[0]->head->value)->value == value);

    int *key2 = malloc(sizeof(int));
    *key2 = 10;
    int *value2 = malloc(sizeof(int));
    *value2 = 20;

    assert(hm_set(hashmap, key2, value2) == 0);
    assert(((struct HashMapEntry *)hashmap->buckets[0]->head->value)->key == key);
    assert(((struct HashMapEntry *)hashmap->buckets[0]->head->value)->value == value);
    assert(((struct HashMapEntry *)hashmap->buckets[0]->head->next->value)->key ==
           key2);
    assert(((struct HashMapEntry *)hashmap->buckets[0]->head->next->value)->value ==
           value2);

    int *key3 = malloc(sizeof(int));
    *key3 = 1;
    int *value3 = malloc(sizeof(int));
    *value3 = 30;

    assert(hm_set(hashmap, key3, value3) == 0);
    assert(((struct HashMapEntry *)hashmap->buckets[1]->head->value)->key == key3);
    assert(((struct HashMapEntry *)hashmap->buckets[1]->head->value)->value == value3);

    int *overlap_key = malloc(sizeof(int));
    *overlap_key = 0;
    int *overlap_value = malloc(sizeof(int));
    *overlap_value = 40;

    assert(hm_set(hashmap, overlap_key, overlap_value) == 0);
    assert(((struct HashMapEntry *)hashmap->buckets[0]->head->value)->key ==
           overlap_key);
    assert(((struct HashMapEntry *)hashmap->buckets[0]->head->value)->value ==
           overlap_value);
    assert(((struct HashMapEntry *)hashmap->buckets[0]->head->next->value)->key ==
           key2);
    assert(((struct HashMapEntry *)hashmap->buckets[0]->head->next->value)->value ==
           value2);

    hm_free(hashmap, entry_free_function);

    printf("hm_set passed\n");

    return;
}

void test_hm_get()
{
    printf("Testing hm_get\n");

    struct HashMap *hashmap = hm_create(10, int_hash_function, int_compare_function);

    int *key = malloc(sizeof(int));
    *key = 0;
    int *value = malloc(sizeof(int));
    *value = 10;

    assert(hm_set(hashmap, key, value) == 0);
    assert(hm_get(hashmap, key) == value);

    int *key2 = malloc(sizeof(int));
    *key2 = 10;
    int *value2 = malloc(sizeof(int));
    *value2 = 20;

    assert(hm_set(hashmap, key2, value2) == 0);
    assert(hm_get(hashmap, key2) == value2);
    assert(hm_get(hashmap, key) == value);

    int *key3 = malloc(sizeof(int));
    *key3 = 1;
    int *value3 = malloc(sizeof(int));
    *value3 = 30;

    assert(hm_set(hashmap, key3, value3) == 0);
    assert(hm_get(hashmap, key3) == value3);

    int *non_existent_key = malloc(sizeof(int));
    *non_existent_key = 2;

    assert(hm_get(hashmap, non_existent_key) == NULL);

    hm_free(hashmap, entry_free_function);

    printf("hm_get passed\n");

    return;
}

void test_hm_remove()
{
    printf("Testing hm_remove\n");

    struct HashMap *hashmap = hm_create(10, int_hash_function, int_compare_function);

    int *key = malloc(sizeof(int));
    *key = 0;
    int *value = malloc(sizeof(int));
    *value = 10;

    assert(hm_set(hashmap, key, value) == 0);
    assert(hm_remove(hashmap, key) == value);
    assert(hm_get(hashmap, key) == NULL);

    free(key);
    free(value);

    int *key2 = malloc(sizeof(int));
    *key2 = 10;
    int *value2 = malloc(sizeof(int));
    *value2 = 20;

    assert(hm_set(hashmap, key2, value2) == 0);
    assert(hm_remove(hashmap, key2) == value2);
    assert(hm_get(hashmap, key2) == NULL);

    free(key2);
    free(value2);

    int *key3 = malloc(sizeof(int));
    *key3 = 1;
    int *value3 = malloc(sizeof(int));
    *value3 = 30;

    assert(hm_set(hashmap, key3, value3) == 0);
    assert(hm_remove(hashmap, key3) == value3);
    assert(hm_get(hashmap, key3) == NULL);

    free(key3);
    free(value3);

    int *non_existent_key = malloc(sizeof(int));
    *non_existent_key = 2;

    assert(hm_remove(hashmap, non_existent_key) == NULL);

    free(non_existent_key);

    hm_free(hashmap, entry_free_function);

    printf("hm_remove passed\n");

    return;
}

int main()
{
    printf("Running tests for \"lib/hashmap.c\"\n");

    test_hm_create();
    test_hm_set();
    test_hm_get();
    test_hm_remove();

    printf("All tests passed for \"lib/hashmap.c\"\n\n");

    return 0;
}
