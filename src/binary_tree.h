#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "tokenizer.h"
#include "linked_list.h"

struct tree_node
{
	struct token t;
	struct tree_node *left;
	struct tree_node *right;
};

struct tree_result
{
	char *str;
	float val;
};

void free_tree(struct tree_node *node);

struct tree_node *make_tree(struct node *head);

struct tree_result evaluate_tree(struct tree_node *root, float xval);

#endif /* BINARY_TREE_H */
