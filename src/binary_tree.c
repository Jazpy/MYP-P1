#include <stdlib.h>
#include "binary_tree.h"

void free_tree(struct tree_node *node)
{
	if(node != 0)
	{
		free_tree(node -> left);
		free_tree(node -> right);
		free(node);
	}
}
