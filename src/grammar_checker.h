#ifndef GRAMMAR_CHECKER_H
#define GRAMMAR_CHECKER_H

#include "linked_list.h"

char *analyze_linked_list(struct node *root);

int paren_pass(struct node *root);

#endif /* GRAMMAR_CHECKER_H */
