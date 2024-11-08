/**
 * @brief A generic linked list implementation.
 */

#include <stdlib.h>

#include "lib/list.h"

/**
 * @brief Creates a new linked list.
 * @param value_compare_function A function that compares two values in the list.
 * @param value_free_function A function that frees a value in the list. Pass NULL
 *                            if the values do not need to be freed when ll_free is
 *                            called.
 * @return A pointer to the created linked list.
 */
struct LinkedList *ll_create(ValueCompareFunction value_compare_function,
                             ValueFreeFunction value_free_function)
{
    struct LinkedList *linked_list = malloc(sizeof(struct LinkedList));

    if (linked_list == NULL)
    {
        return NULL;
    }

    linked_list->size = 0;
    linked_list->head = NULL;
    linked_list->tail = NULL;
    linked_list->value_compare_function = value_compare_function;
    linked_list->value_free_function = value_free_function;

    return linked_list;
}

/**
 * @brief Frees a linked list.
 * @param linked_list A pointer to the linked list to free.
 * @return void
 */
void ll_free(struct LinkedList *linked_list)
{
    struct LinkedListNode *current_node = linked_list->head;

    while (current_node != NULL)
    {
        struct LinkedListNode *next_node = current_node->next;
        if (linked_list->value_free_function != NULL)
        {
            linked_list->value_free_function(current_node->value);
        }

        free(current_node);
        current_node = next_node;
    }

    free(linked_list);

    return;
}

/**
 * @brief Pushes a value onto the front of a linked list.
 * @param linked_list A pointer to the linked list to push onto.
 * @param value A pointer to the value to push.
 * @return 0 if the value was pushed successfully, -1 otherwise.
 */
int ll_push(struct LinkedList *linked_list, void *value)
{
    struct LinkedListNode *new_node = malloc(sizeof(struct LinkedListNode));

    if (new_node == NULL)
    {
        return -1;
    }

    new_node->value = value;
    new_node->next = linked_list->head;

    linked_list->head = new_node;

    if (linked_list->tail == NULL)
    {
        linked_list->tail = new_node;
    }

    linked_list->size++;

    return 0;
}

/**
 * @brief Pops a value from the front of a linked list.
 * @param linked_list A pointer to the linked list to pop from.
 * @return A pointer to the popped value.
 */
void *ll_pop(struct LinkedList *linked_list);

/**
 * @brief Inserts a value before a node in a linked list.
 * @param linked_list A pointer to the linked list to insert into.
 * @param node A pointer to the node to insert before.
 * @return 0 if the value was inserted successfully, -1 otherwise.
 */
int ll_insert_before_node(struct LinkedList *linked_list, struct LinkedListNode *node);

/**
 * @brief Inserts a value before a value in a linked list.
 * @param linked_list A pointer to the linked list to insert into.
 * @param value A pointer to the value to insert before.
 * @return 0 if the value was inserted successfully, -1 otherwise.
 */
int ll_insert_before_value(struct LinkedList *linked_list, void *value);

/**
 * @brief Inserts a value after a node in a linked list.
 * @param linked_list A pointer to the linked list to insert into.
 * @param node A pointer to the node to insert after.
 * @return 0 if the value was inserted successfully, -1 otherwise.
 */
int ll_insert_after_node(struct LinkedList *linked_list, struct LinkedListNode *node);

/**
 * @brief Inserts a value after a value in a linked list.
 * @param linked_list A pointer to the linked list to insert into.
 * @param value A pointer to the value to insert after.
 * @return 0 if the value was inserted successfully, -1 otherwise.
 */
int ll_insert_after_value(struct LinkedList *linked_list, void *value);

/**
 * @brief Removes a node from a linked list.
 * @param linked_list A pointer to the linked list to remove from.
 * @param node A pointer to the node to remove.
 * @return 0 if the node was removed successfully, -1 otherwise.
 */
int ll_remove_node(struct LinkedList *linked_list, struct LinkedListNode *node);

/**
 * @brief Removes a value from a linked list.
 * @param linked_list A pointer to the linked list to remove from.
 * @param value A pointer to the value to remove.
 * @return 0 if the value was removed successfully, -1 otherwise.
 */
int ll_remove_value(struct LinkedList *linked_list, void *value);