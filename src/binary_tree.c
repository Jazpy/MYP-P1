#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "binary_tree.h"

struct tree_node_list{
	struct tree_node *data;
	struct tree_node_list *next;
};

void free_tree(struct tree_node *node)
{
	if(node != 0)
	{
		free_tree(node -> left);
		free_tree(node -> right);
		free(node);
	}
}

struct tree_node *make_tree(struct node *head)
{
	struct tree_node_list *stack;

	while(head != 0)
	{
		struct token curr_tok = head -> t;

		if(curr_tok.id == 0 || curr_tok.id == 1)
		{
			struct tree_node *new = malloc(sizeof(
				struct tree_node));
			new -> t = curr_tok;
			new -> left = 0;
			new -> right = 0;

			struct tree_node_list *temp_stack = stack;
			stack = malloc(sizeof(struct tree_node_list));
			stack -> data = new;
			stack -> next = temp_stack;
		} else if(curr_tok.id >= 3 && curr_tok.id <= 7){
			
			//pop first operand
			if(stack == 0)
				return 0;

			struct tree_node *t1 = stack -> data;
			struct tree_node_list *temp_stack = stack;
			stack = stack -> next;

			free(temp_stack);

			//pop second operand
			if(stack == 0)
				return 0;

			struct tree_node *t2 = stack -> data;
			temp_stack = stack;
			stack = stack -> next;

			free(temp_stack);

			//push new node
			struct tree_node *new = malloc(sizeof(
				struct tree_node));
			new -> t = curr_tok;
			new -> left = t1;
			new -> right = t2;
			
			temp_stack = stack;
			stack = malloc(sizeof(struct tree_node_list));
			stack -> data = new;
			stack -> next = temp_stack;
		} else {
	
			//pop operand
			if(stack == 0)
				return 0;	

			struct tree_node *t1 = stack -> data;
			struct tree_node_list *temp_stack = stack;
			stack = stack -> next;

			free(temp_stack);

			//push new node
			struct tree_node *new = malloc(sizeof(
				struct tree_node));
			new -> t = curr_tok;
			new -> left = t1;
			new -> right = 0;
			
			temp_stack = stack;
			stack = malloc(sizeof(struct tree_node_list));
			stack -> data = new;
			stack -> next = temp_stack;
		}

		head = head -> next;
	}

	if(stack == 0)
		return 0;
	
	return stack -> data;
}

struct tree_result evaluate_tree(struct tree_node *root, float xval)
{
	struct tree_result ret;
	ret.str = "undefined error";
	ret.val = 0;

	if(root -> t.id >= 3 && root -> t.id <= 7)
	{
		struct tree_result val1 =
			evaluate_tree(root -> left, xval);
		struct tree_result val2 =
			evaluate_tree(root -> right, xval);

		if(strcmp(val1.str, "s") != 0)
			return val1;
		if(strcmp(val2.str, "s") != 0)
			return val2;

		switch(root -> t.id)
		{
			case 3:
			{
				ret.str = "s";
				ret.val = val1.val - val2.val;
				
				return ret;
			}
			case 4:
			{
				ret.str = "s";
				ret.val = val1.val + val2.val;
				
				return ret;
			}
			case 5:
			{
				ret.str = "s";
				ret.val = val1.val * val2.val;
				
				return ret;
			}
			case 6:
			{
				if(val2.val == 0)
				{
					ret.str = "division by 0";
					ret.val = 0;
				} else {
					ret.str = "s";
					ret.val = val1.val / val2.val;
				}
				
				return ret;
			}
			case 7:
			{
				if(val1.val == 0 && val2.val < 0)
				{
					ret.str = "0 to neg power";
					ret.val = 0;
				} else if(val1.val < 0 && 
					ceilf(val2.val) != val2.val)
				{
					ret.str = "neg to frac power";
					ret.val = 0;
				} else {
					ret.str = "s";
					ret.val = pow(val1.val, val2.val);
				}
				
				return ret;
			}
			default:
				return ret;
		}
	} else if((root -> t.id >= 10 && root -> t.id <= 16) || 
		root -> t.id == 2){
					
		struct tree_result val =
			evaluate_tree(root -> left, xval);

		if(strcmp(val.str, "s") != 0)
			return val;

		switch(root -> t.id)
		{
			case 2:
			{
				ret.str = "s";
				ret.val = 0 - val.val;

				return ret;
			}
			case 10:
			{
				ret.str = "s";
				ret.val = sin(val.val);

				return ret;
			}
			case 11:
			{
				ret.str = "s";
				ret.val = cos(val.val);

				return ret;
			}
			case 12:
			{
				if(cos(val.val) == 0)
				{
					ret.str = "division by 0";
					ret.val = 0;
				} else {
					ret.str = "s";
					ret.val = sin(val.val) /
						cos(val.val);
				}

				return ret;
			}
			case 13:
			{
				if(sin(val.val) == 0)
				{
					ret.str = "division by 0";
					ret.val = 0;
				} else {
					ret.str = "s";
					ret.val = cos(val.val) /
						sin(val.val);
				}

				return ret;
			}
			case 14:
			{
				if(cos(val.val) == 0)
				{
					ret.str = "undef sec";
					ret.val = 0;
				} else {
					ret.str = "s";
					ret.val = 1 / cos(val.val);
				}

				return ret;
			}
			case 15:
			{
				if(sin(val.val) == 0)
				{
					ret.str = "undef csc";
					ret.val = 0;
				} else {
					ret.str = "s";
					ret.val = 1 / sin(val.val);
				}

				return ret;
			}
			case 16:
			{
				if(val.val < 0)
				{
					ret.str = "neg sqr";
					ret.val = 0;
				} else {
					ret.str = "s";
					ret.val = sqrt(val.val);
				}

				return ret;
			}
			default:
				return ret;
		}
	} else if(root -> t.id == 1){
		ret.str = "s";
		ret.val = xval;
		return ret;
	} else if(root -> t.id == 0){
		ret.str = "s";
		ret.val = root -> t.val;
		return ret;
	}

	return ret;
}
