#include "grammar_checker.h"

char *analyze_linked_list(struct node *root)
{
	if(root == 0)
		return "empty equation";

	int curr_id = root -> t.id;
	struct node* curr_node = root;

	if(curr_id <= 7 && curr_id >= 3)
		return "can't start an equation with a binary operator";
	else if(curr_id == 9)
		return "can't start an equation with a closing parenthesis";
	else if(curr_id == -1)
		return "unrecognized expression, please refer to the README";

	if(paren_pass(root) == -1)
		return "mismatched parenthesis";

	while(curr_node -> next != 0)
	{
		curr_node = curr_node -> next;

		int prev_id = curr_id;
		curr_id = curr_node -> t.id;

		if(curr_id == -1)
		{
			return "unrecognized expression, please "
				"refer to the README";
		}

		if(prev_id == 0 && (curr_id > 7 && curr_id < 3))
		{
			return "can't have number followed by "
				"something other than an operator";
		}

		if(prev_id == 1 && (curr_id > 7 && curr_id < 3))
		{
			return "can't have variable followed by "
				"something other than an operator";
		}
		
		if(prev_id == 2 && ((curr_id >= 3 && curr_id <= 7) || curr_id == 9))
		{
			return "can't negate something other than number, "
				"variable, or expression";
		}

		if((prev_id >= 3 && prev_id <= 7) && 
			(curr_id != 0 && curr_id != 1) &&
			!(curr_id >= 10 && curr_id <= 16) && 
			curr_id != 2 && curr_id != 8)
		{
			return "can't have something other than number "
				"or variable after binary operator";
		}

		if(prev_id == 8 && (curr_id >= 3 && curr_id <= 7))
		{
			return "can't have an operator right after "
				"an opening parenthesis";
		}

		if(prev_id == 9 && (curr_id < 3 ||
			curr_id > 7) && curr_id != 9)
		{
			return "can't have anything other than an operator "
				"or a closing parenthesis right after "
				"a closing parenthesis";
		}

		if(prev_id >= 10 && curr_id != 8)
		{
			return "can't have anything other than an opening "
				"parenthesis after a function";
		}
	}

	if(curr_id == -1 || curr_id <= 16 && curr_id >= 2)
	{
		if(curr_id == 9)
			return "s";

		return "Invalid end to expression, should be var, "
			"number, or closing parenthesis";
	}

	return "s";
}

int paren_pass(struct node *root)
{
	int paren_counter = 0;

	while(root)
	{
		if(root -> t.id == 8)
			++paren_counter;
		else if(root -> t.id == 9)
			--paren_counter;

		if(paren_counter < 0)
			return -1;

		root = root -> next;
	}

	if(paren_counter == 0)
		return 0;
	else
		return -1;
}
