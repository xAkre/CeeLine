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

void test_ll_push()
{
    printf("Testing ll_push\n");

    struct LinkedList *linked_list = ll_create(int_compare_function, int_free_function);

    int *value = malloc(sizeof(int));
    *value = 42;

    assert(ll_push(linked_list, value) == 0);
    assert(linked_list->size == 1);
    assert(linked_list->head != NULL);
    assert(linked_list->tail != NULL);
    assert(linked_list->head == linked_list->tail);
    assert(linked_list->head->value == value);
    assert(linked_list->head->next == NULL);

    int *value2 = malloc(sizeof(int));
    *value2 = 43;

    assert(ll_push(linked_list, value2) == 0);
    assert(linked_list->size == 2);
    assert(linked_list->head != NULL);
    assert(linked_list->tail != NULL);
    assert(linked_list->head != linked_list->tail);
    assert(linked_list->head->value == value2);
    assert(linked_list->head->next == linked_list->tail);
    assert(linked_list->tail->value == value);
    assert(linked_list->tail->next == NULL);

    ll_free(linked_list);

    printf("ll_push passed\n");

    return;
}

void test_ll_pop()
{
    printf("Testing ll_pop\n");

    struct LinkedList *linked_list = ll_create(int_compare_function, int_free_function);

    assert(ll_pop(linked_list) == NULL);

    int *value = malloc(sizeof(int));
    *value = 42;
    int *value2 = malloc(sizeof(int));
    *value2 = 43;

    ll_push(linked_list, value);
    ll_push(linked_list, value2);

    int *popped_value = ll_pop(linked_list);

    assert(popped_value != NULL);
    assert(*popped_value == *value2);
    assert(linked_list->size == 1);
    assert(linked_list->head != NULL);
    assert(linked_list->tail != NULL);
    assert(linked_list->head == linked_list->tail);
    assert(linked_list->head->value == value);
    assert(linked_list->head->next == NULL);

    popped_value = ll_pop(linked_list);

    assert(popped_value != NULL);
    assert(*popped_value == *value);
    assert(linked_list->size == 0);
    assert(linked_list->head == NULL);
    assert(linked_list->tail == NULL);

    ll_free(linked_list);

    printf("ll_pop passed\n");

    return;
}

void test_ll_insert_before_node()
{
    printf("Testing ll_insert_before_node\n");

    struct LinkedList *linked_list = ll_create(int_compare_function, int_free_function);

    int *value = malloc(sizeof(int));
    *value = 42;
    int *value2 = malloc(sizeof(int));
    *value2 = 43;
    int *value3 = malloc(sizeof(int));
    *value3 = 44;

    ll_push(linked_list, value);

    struct LinkedListNode *node = linked_list->head;

    assert(ll_insert_before_node(linked_list, node, value2) == 0);
    assert(linked_list->size == 2);
    assert(linked_list->head != NULL);
    assert(linked_list->tail != NULL);
    assert(linked_list->head != linked_list->tail);
    assert(linked_list->head->value == value2);
    assert(linked_list->head->next == linked_list->tail);
    assert(linked_list->tail->value == value);
    assert(linked_list->tail->next == NULL);

    assert(ll_insert_before_node(linked_list, linked_list->tail, value3) == 0);
    assert(linked_list->size == 3);
    assert(linked_list->head != NULL);
    assert(linked_list->tail != NULL);
    assert(linked_list->head != linked_list->tail);
    assert(linked_list->head->value == value2);
    assert(linked_list->head->next != linked_list->tail);
    assert(linked_list->head->next->value == value3);
    assert(linked_list->head->next->next == linked_list->tail);
    assert(linked_list->tail->value == value);
    assert(linked_list->tail->next == NULL);

    struct LinkedListNode *non_existent_node = malloc(sizeof(struct LinkedListNode));
    non_existent_node->value = value;
    non_existent_node->next = NULL;

    assert(ll_insert_before_node(linked_list, non_existent_node, value3) == -1);

    ll_free(linked_list);

    printf("ll_insert_before_node passed\n");

    return;
}

int main()
{
    printf("Running tests for \"lib/list.c\"\n");

    test_ll_create();
    test_ll_push();
    test_ll_pop();
    test_ll_insert_before_node();

    printf("All tests passed for \"lib/list.c\"\n");

    return 0;
}
