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

void int_free_function(void *value)
{
    free(value);
}

void test_hm_create()
{
    printf("Testing hm_create\n");

    struct HashMap *hashmap = hm_create(10, int_hash_function, int_compare_function,
                                        int_free_function, int_free_function);

    assert(hashmap != NULL);
    assert(hashmap->capacity == 10);
    assert(hashmap->buckets != NULL);
    assert(hashmap->hash_function == int_hash_function);
    assert(hashmap->key_compare_function == int_compare_function);
    assert(hashmap->key_free_function == int_free_function);
    assert(hashmap->value_free_function == int_free_function);

    hm_free(hashmap);

    printf("hm_create passed\n");

    return;
}

int main()
{
    printf("Running tests for \"lib/hashmap.c\"\n");

    test_hm_create();

    printf("All tests passed for \"lib/hashmap.c\"\n\n\n");

    return 0;
}
