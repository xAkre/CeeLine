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
 * @brief Gets a node by its value.
 * @param linked_list A pointer to the linked list to search.
 * @param value A pointer to the value to search for.
 * @return A pointer to the node with the value, or NULL if the value is not found.
 */
struct LinkedListNode *ll_get_node_by_value(struct LinkedList *linked_list, void *value)
{
    struct LinkedListNode *current_node = linked_list->head;

    while (current_node != NULL)
    {
        if (linked_list->value_compare_function(current_node->value, value) == 0)
        {
            return current_node;
        }

        current_node = current_node->next;
    }

    return NULL;
}

/**
 * @brief Pushes a value onto the tail of a linked list.
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
    new_node->next = NULL;

    if (linked_list->size == 0)
    {
        linked_list->head = new_node;
        linked_list->tail = new_node;
    }
    else
    {
        linked_list->tail->next = new_node;
        linked_list->tail = new_node;
    }

    linked_list->size++;

    return 0;
}

/**
 * @brief Pops a value from the tail of a linked list.
 * @param linked_list A pointer to the linked list to pop from.
 * @return A pointer to the popped value, or NULL if the list is empty.
 */
void *ll_pop(struct LinkedList *linked_list)
{
    if (linked_list->size == 0)
    {
        return NULL;
    }

    if (linked_list->size == 1)
    {
        void *value = linked_list->tail->value;

        free(linked_list->tail);

        linked_list->head = NULL;
        linked_list->tail = NULL;
        linked_list->size = 0;

        return value;
    }

    struct LinkedListNode *popped_node = linked_list->tail;
    void *value = popped_node->value;

    struct LinkedListNode *current_node = linked_list->head;

    while (current_node->next != linked_list->tail)
    {
        current_node = current_node->next;
    }

    linked_list->tail = current_node;
    linked_list->tail->next = NULL;
    linked_list->size--;

    free(popped_node);

    return value;
}

/**
 * @brief Inserts a value before a node in a linked list.
 * @param linked_list A pointer to the linked list to insert into.
 * @param node A pointer to the node to insert before.
 * @param value A pointer to the value to insert.
 * @return 0 if the value was inserted successfully, -1 otherwise.
 */
int ll_insert_before_node(struct LinkedList *linked_list, struct LinkedListNode *node,
                          void *value)
{
    struct LinkedListNode *new_node = malloc(sizeof(struct LinkedListNode));

    if (new_node == NULL)
    {
        return -1;
    }

    new_node->value = value;
    new_node->next = node;

    if (node == linked_list->head)
    {
        linked_list->head = new_node;
        linked_list->size++;

        return 0;
    }
    else
    {
        struct LinkedListNode *current_node = linked_list->head;

        while (current_node != NULL)
        {
            if (current_node->next == node)
            {
                current_node->next = new_node;
                linked_list->size++;

                return 0;
            }

            return -1;
        }
    }

    return -1;
}

/**
 * @brief Inserts a value before a value in a linked list.
 * @param linked_list A pointer to the linked list to insert into.
 * @param before A pointer to the value to insert before.
 * @param value A pointer to the value to insert.
 * @return 0 if the value was inserted successfully, -1 otherwise.
 */
int ll_insert_before_value(struct LinkedList *linked_list, void *before, void *value)
{
    struct LinkedListNode *current_node = linked_list->head;

    while (current_node != NULL)
    {
        if (linked_list->value_compare_function(current_node->value, before) == 0)
        {
            return ll_insert_before_node(linked_list, current_node, value);
        }

        current_node = current_node->next;
    }

    return -1;
}

/**
 * @brief Inserts a value after a node in a linked list.
 * @param linked_list A pointer to the linked list to insert into.
 * @param node A pointer to the node to insert after.
 * @param value A pointer to the value to insert.
 * @return 0 if the value was inserted successfully, -1 otherwise.
 */
int ll_insert_after_node(struct LinkedList *linked_list, struct LinkedListNode *node,
                         void *value);

/**
 * @brief Inserts a value after a value in a linked list.
 * @param linked_list A pointer to the linked list to insert into.
 * @param after A pointer to the value to insert after.
 * @param value A pointer to the value to insert.
 * @return 0 if the value was inserted successfully, -1 otherwise.
 */
int ll_insert_after_value(struct LinkedList *linked_list, void *after, void *value);

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
