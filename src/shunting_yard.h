#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

/**
 * @file shunting_yard.h
 *
 * @brief shunting-yard prototype
 *
 * function that turns tokens into postfix notation
 */

#include "linked_list.h"

/**
 * @brief shunting-yard prototype
 *
 * @param head head of list of tokens to transform
 * @return linked list with postfix form of input
 */

struct node *parse_linked_list(struct node *head);

#endif /* SHUNTING_YARD_H */
