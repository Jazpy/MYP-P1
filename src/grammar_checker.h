#ifndef GRAMMAR_CHECKER_H
#define GRAMMAR_CHECKER_H

/**
 * @file grammar_checker.h
 *
 * @brief grammar checking function prototypes
 *
 * 2 simple functions to check validity of math equation
 */

#include "linked_list.h"

/**
 * @brief check if equation has valid grammar
 *
 * @param root head of list of tokens to analyze
 * @return string with "s" for success and error if there is one
 */

char *analyze_linked_list(struct node *root);

/**
 * @brief check if parenthesis match
 *
 * @param root head of list of tokens
 * @return 1 if parenthesis match, 0 if not
 */

int paren_pass(struct node *root);

#endif /* GRAMMAR_CHECKER_H */
