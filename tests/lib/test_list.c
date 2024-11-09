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

void test_ll_has_node()
{
    printf("Testing ll_has_node\n");

    struct LinkedList *linked_list = ll_create(int_compare_function, int_free_function);

    int *value = malloc(sizeof(int));
    *value = 42;
    int *value2 = malloc(sizeof(int));
    *value2 = 43;

    ll_push(linked_list, value);
    ll_push(linked_list, value2);

    struct LinkedListNode *node = ll_get_node_by_value(linked_list, value);

    assert(ll_has_node(linked_list, node) == 1);
    assert(ll_has_node(linked_list, node->next) == 1);

    struct LinkedListNode *non_existent_node = malloc(sizeof(struct LinkedListNode));
    non_existent_node->value = value;
    non_existent_node->next = NULL;

    assert(ll_has_node(linked_list, non_existent_node) == 0);

    ll_free(linked_list);

    printf("ll_has_node passed\n");

    return;
}

void test_ll_get_node_by_value()
{
    printf("Testing ll_get_node_by_value\n");

    struct LinkedList *linked_list = ll_create(int_compare_function, int_free_function);

    int *value = malloc(sizeof(int));
    *value = 42;
    int *value2 = malloc(sizeof(int));
    *value2 = 43;

    ll_push(linked_list, value);
    ll_push(linked_list, value2);

    struct LinkedListNode *node = ll_get_node_by_value(linked_list, value);

    assert(node != NULL);
    assert(node->value == value);
    assert(node->next != NULL);
    assert(node->next->value == value2);
    assert(node->next->next == NULL);

    node = ll_get_node_by_value(linked_list, value2);

    assert(node != NULL);
    assert(node->value == value2);
    assert(node->next == NULL);

    int *non_existent_value = malloc(sizeof(int));
    *non_existent_value = 44;

    assert(ll_get_node_by_value(linked_list, non_existent_value) == NULL);

    ll_free(linked_list);

    printf("ll_get_node_by_value passed\n");

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
    assert(linked_list->head->value == value);
    assert(linked_list->head->next == linked_list->tail);
    assert(linked_list->tail->value == value2);
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

void test_ll_insert_before_value()
{
    printf("Testing ll_insert_before_value\n");

    struct LinkedList *linked_list = ll_create(int_compare_function, int_free_function);

    int *value = malloc(sizeof(int));
    *value = 42;
    int *value2 = malloc(sizeof(int));
    *value2 = 43;
    int *value3 = malloc(sizeof(int));
    *value3 = 44;

    ll_push(linked_list, value);

    assert(ll_insert_before_value(linked_list, value, value2) == 0);
    assert(linked_list->size == 2);
    assert(linked_list->head != NULL);
    assert(linked_list->tail != NULL);
    assert(linked_list->head != linked_list->tail);
    assert(linked_list->head->value == value2);
    assert(linked_list->head->next == linked_list->tail);
    assert(linked_list->tail->value == value);
    assert(linked_list->tail->next == NULL);

    assert(ll_insert_before_value(linked_list, value2, value3) == 0);
    assert(linked_list->size == 3);
    assert(linked_list->head != NULL);
    assert(linked_list->tail != NULL);
    assert(linked_list->head != linked_list->tail);
    assert(linked_list->head->value == value3);
    assert(linked_list->head->next != linked_list->tail);
    assert(linked_list->head->next->value == value2);
    assert(linked_list->head->next->next == linked_list->tail);
    assert(linked_list->tail->value == value);
    assert(linked_list->tail->next == NULL);

    int *non_existent_value = malloc(sizeof(int));
    *non_existent_value = 45;

    assert(ll_insert_before_value(linked_list, non_existent_value, value3) == -1);

    ll_free(linked_list);

    printf("ll_insert_before_value passed\n");

    return;
}

void test_ll_insert_after_node()
{
    printf("Testing ll_insert_after_node\n");

    struct LinkedList *linked_list = ll_create(int_compare_function, int_free_function);

    int *value = malloc(sizeof(int));
    *value = 42;
    int *value2 = malloc(sizeof(int));
    *value2 = 43;
    int *value3 = malloc(sizeof(int));
    *value3 = 44;

    ll_push(linked_list, value);
    ll_push(linked_list, value2);

    assert(ll_insert_after_node(linked_list, linked_list->head, value3) == 0);
    assert(linked_list->size == 3);
    assert(linked_list->head != NULL);
    assert(linked_list->tail != NULL);
    assert(linked_list->head != linked_list->tail);
    assert(linked_list->head->value == value);
    assert(linked_list->head->next != linked_list->tail);
    assert(linked_list->head->next->value == value3);
    assert(linked_list->head->next->next == linked_list->tail);
    assert(linked_list->tail->value == value2);
    assert(linked_list->tail->next == NULL);

    struct LinkedListNode *non_existent_node = malloc(sizeof(struct LinkedListNode));
    non_existent_node->value = value;
    non_existent_node->next = NULL;

    assert(ll_insert_after_node(linked_list, non_existent_node, value3) == -1);

    ll_free(linked_list);

    printf("ll_insert_after_node passed\n");

    return;
}

void test_ll_insert_after_value()
{
    printf("Testing ll_insert_after_value\n");

    struct LinkedList *linked_list = ll_create(int_compare_function, int_free_function);

    int *value = malloc(sizeof(int));
    *value = 42;
    int *value2 = malloc(sizeof(int));
    *value2 = 43;
    int *value3 = malloc(sizeof(int));
    *value3 = 44;

    ll_push(linked_list, value);
    ll_push(linked_list, value2);

    assert(ll_insert_after_value(linked_list, value, value3) == 0);
    assert(linked_list->size == 3);
    assert(linked_list->head != NULL);
    assert(linked_list->tail != NULL);
    assert(linked_list->head != linked_list->tail);
    assert(linked_list->head->value == value);
    assert(linked_list->head->next != linked_list->tail);
    assert(linked_list->head->next->value == value3);
    assert(linked_list->head->next->next == linked_list->tail);
    assert(linked_list->tail->value == value2);
    assert(linked_list->tail->next == NULL);

    int *non_existent_value = malloc(sizeof(int));
    *non_existent_value = 45;

    assert(ll_insert_after_value(linked_list, non_existent_value, value3) == -1);

    ll_free(linked_list);

    printf("ll_insert_after_value passed\n");

    return;
}

void test_ll_remove_node()
{
    printf("Testing ll_remove_node\n");

    struct LinkedList *linked_list = ll_create(int_compare_function, int_free_function);

    int *value = malloc(sizeof(int));
    *value = 42;
    int *value2 = malloc(sizeof(int));
    *value2 = 43;
    int *value3 = malloc(sizeof(int));
    *value3 = 44;

    ll_push(linked_list, value);
    ll_push(linked_list, value2);
    ll_push(linked_list, value3);

    struct LinkedListNode *node = linked_list->head->next;

    assert(ll_remove_node(linked_list, node) == 0);
    assert(linked_list->size == 2);
    assert(linked_list->head != NULL);
    assert(linked_list->tail != NULL);
    assert(linked_list->head != linked_list->tail);
    assert(linked_list->head->value == value);
    assert(linked_list->head->next == linked_list->tail);
    assert(linked_list->tail->value == value3);
    assert(linked_list->tail->next == NULL);

    assert(ll_remove_node(linked_list, linked_list->head) == 0);
    assert(linked_list->size == 1);
    assert(linked_list->head != NULL);
    assert(linked_list->tail != NULL);
    assert(linked_list->head == linked_list->tail);
    assert(linked_list->head->value == value3);
    assert(linked_list->head->next == NULL);

    assert(ll_remove_node(linked_list, linked_list->head) == 0);
    assert(linked_list->size == 0);
    assert(linked_list->head == NULL);
    assert(linked_list->tail == NULL);

    struct LinkedListNode *non_existent_node = malloc(sizeof(struct LinkedListNode));
    non_existent_node->value = value;
    non_existent_node->next = NULL;

    assert(ll_remove_node(linked_list, non_existent_node) == -1);

    ll_free(linked_list);

    printf("ll_remove_node passed\n");

    return;
}

void test_ll_remove_value()
{
    printf("Testing ll_remove_value\n");

    struct LinkedList *linked_list = ll_create(int_compare_function, int_free_function);

    int *value = malloc(sizeof(int));
    *value = 42;
    int *value2 = malloc(sizeof(int));
    *value2 = 43;
    int *value3 = malloc(sizeof(int));
    *value3 = 44;

    ll_push(linked_list, value);
    ll_push(linked_list, value2);
    ll_push(linked_list, value3);

    assert(ll_remove_value(linked_list, value2) == 0);
    assert(linked_list->size == 2);
    assert(linked_list->head != NULL);
    assert(linked_list->tail != NULL);
    assert(linked_list->head != linked_list->tail);
    assert(linked_list->head->value == value);
    assert(linked_list->head->next == linked_list->tail);
    assert(linked_list->tail->value == value3);
    assert(linked_list->tail->next == NULL);

    assert(ll_remove_value(linked_list, value) == 0);
    assert(linked_list->size == 1);
    assert(linked_list->head != NULL);
    assert(linked_list->tail != NULL);
    assert(linked_list->head == linked_list->tail);
    assert(linked_list->head->value == value3);
    assert(linked_list->head->next == NULL);

    assert(ll_remove_value(linked_list, value3) == 0);
    assert(linked_list->size == 0);
    assert(linked_list->head == NULL);
    assert(linked_list->tail == NULL);

    int *non_existent_value = malloc(sizeof(int));
    *non_existent_value = 45;

    assert(ll_remove_value(linked_list, non_existent_value) == -1);

    ll_free(linked_list);

    printf("ll_remove_value passed\n");

    return;
}

int main()
{
    printf("Running tests for \"lib/list.c\"\n");

    test_ll_create();
    test_ll_has_node();
    test_ll_get_node_by_value();
    test_ll_push();
    test_ll_pop();
    test_ll_insert_before_node();
    test_ll_insert_before_value();
    test_ll_insert_after_node();
    test_ll_insert_after_value();
    test_ll_remove_node();
    test_ll_remove_value();

    printf("All tests passed for \"lib/list.c\"\n\n");

    return 0;
}
