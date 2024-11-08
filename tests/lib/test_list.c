#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib/list.h"

void int_free_function(void *value)
{
    free(value);
}

int int_compare_function(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

void test_ll_create()
{
    printf("Testing ll_create\n");

    struct LinkedList *linked_list = ll_create(int_compare_function, int_free_function);

    assert(linked_list != NULL);
    assert(linked_list->size == 0);
    assert(linked_list->head == NULL);
    assert(linked_list->tail == NULL);
    assert(linked_list->value_compare_function == int_compare_function);
    assert(linked_list->value_free_function == int_free_function);

    ll_free(linked_list);

    printf("ll_create passed\n");

    return;
}

int main()
{
    printf("Running tests for \"lib/list.c\"\n");

    test_ll_create();

    printf("All tests passed for \"lib/list.c\"\n");

    return 0;
}