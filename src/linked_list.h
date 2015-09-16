#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "tokenizer.h"

struct node
{
	struct token t;
	struct node *next;
};

void free_list(struct node *head);

#endif /* LINKED_LIST_H */
