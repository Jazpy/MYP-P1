#ifndef BINARY_TREE_H
#define BINARY_TREE_H

/**
 * @file binary_tree.h
 *
 * @brief binary tree function prototypes and structs.
 *
 * These are the function prototypes for tree generation,
 * handling, and evaluation
 */


#include "tokenizer.h"
#include "linked_list.h"

/**
 * @brief tree node struct
 * 
 * simple struct used to represent binary trees
 */

struct tree_node
{
	struct token t;
	struct tree_node *left;
	struct tree_node *right;
};

/**
 * @brief tree result struct
 * 
 * simple struct used to represent the result of evaluating a tree,
 * indlucing errors
 */

struct tree_result
{
	char *str;
	float val;
};


/**
 * @brief free memory used by tree
 * 
 * @param node root of tree to free
 */

void free_tree(struct tree_node *node);

/**
 * @brief create tree from tokens
 *
 * @param head token list to generate tree from 
 * @return root node of resulting tree
 */

struct tree_node *make_tree(struct node *head);

/**
 * @brief free memory used by tree
 *
 * @param root root of tree to evaluate
 * @param xval value of x to substitute when needed
 * @return tree_result with resulting value and error string 
 */

struct tree_result evaluate_tree(struct tree_node *root, float xval);

#endif /* BINARY_TREE_H */
