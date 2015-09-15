#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "tokenizer.h"

struct tree_node
{
	struct token t;
	struct tree_node *left;
	struct tree_node *right;
};

#endif /* BINARY_TREE_H */
