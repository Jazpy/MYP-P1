#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/**
 * @file linked_list.h
 *
 * @brief linked list prototype functions
 *
 * linked list prototype function and node struct
 */

#include "tokenizer.h"

/**
 * @brief linked list node struct
 *
 * simple node, token data and reference to next node
 */
struct node
{
	struct token t;
	struct node *next;
};

/**
 * @file linked_list.h
 *
 * @param head head of list to free
 */
void free_list(struct node *head);

#endif /* LINKED_LIST_H */
