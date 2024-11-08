/**
 * @brief A generic linked list implementation.
 */

#ifndef __LIST_H
#define __LIST_H

/**
 * @brief A function that frees a generic value.
 * @param param1 The value to free.
 * @return void
 */
typedef void (*ValueFreeFunction)(void *);

/**
 * @brief A function that compares two generic values.
 * @param param1 The first value to compare.
 * @param param2 The second value to compare.
 * @return 0 if the values are equal, else a non-zero value.
 */
typedef int (*ValueCompareFunction)(void *, void *);

/**
 * @struct LinkedListNode
 * @brief A node in a linked list.
 *
 * This node contains a generic value and a pointer to the next node in the list.
 */
struct LinkedListNode
{
    void *value;
    struct LinkedListNode *next;
};

/**
 * @struct LinkedList
 * @brief A linked list.
 *
 * This linked list contains a size, a pointer to it's head and tail nodes,
 * as well as pointers to functions that free and compare values contained
 * in the list.
 */
struct LinkedList
{
    int size;
    struct LinkedListNode *head;
    struct LinkedListNode *tail;
    ValueFreeFunction value_free_function;
    ValueCompareFunction value_compare_function;
};

/**
 * @brief Creates a new linked list.
 * @param value_compare_function A function that compares two values in the list.
 * @param value_free_function A function that frees a value in the list. Pass NULL
 *                            if the values do not need to be freed when ll_free is
 *                            called.
 * @return A pointer to the created linked list.
 */
struct LinkedList *ll_create(ValueCompareFunction value_compare_function,
                             ValueFreeFunction value_free_function);

/**
 * @brief Frees a linked list.
 * @param linked_list A pointer to the linked list to free.
 * @return void
 */
void ll_free(struct LinkedList *linked_list);

/**
 * @brief Pushes a value onto the front of a linked list.
 * @param linked_list A pointer to the linked list to push onto.
 * @param value A pointer to the value to push.
 * @return 0 if the value was pushed successfully, -1 otherwise.
 */
int ll_push(struct LinkedList *linked_list, void *value);

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

#endif
