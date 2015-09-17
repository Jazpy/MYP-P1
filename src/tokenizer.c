#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

void token_init(struct token *t)
{
	/**
		IDs:
		-1 = error token
		0 = number
		1 = variable
		2 = unary '-'
		3 = binary '-'
		4 = '+'
		5 = '*'
		6 = '/'
		7 = '^'
		8 = '('
		9 = ')'
		10 = sin
		11 = cos
		12 = tan
		13 = cot
		14 = sec
		15 = csc
		16 = sqr
	**/

	t -> id = 0;
	t -> val = 0;
}

struct token get_next_token(char *str, int *index, int *prev_token_id)
{
	struct token ret;
	token_init(&ret);

	char curr = str[*index];
	int length = 0;

	//First we check for operators
	if(curr == '-')
	{
		//Check if it's unary '-'
		//That is, if it's first char or previous char is
		//any operator other than ')'
		//Else, it's a binary '-'
		if(*index == 0 || (*prev_token_id > 1 &&
			*prev_token_id < 9))
		{
			ret.id = 2;
		} else {
			ret.id = 3;
		}
	} else if(curr == '+') {
		ret.id = 4;
	} else if(curr == '*') {
		ret.id = 5;
	} else if(curr == '/') {
		ret.id = 6;
	} else if(curr == '^') {
		ret.id = 7;
	} else if(curr == '(') {
		ret.id = 8;
	} else if(curr == ')') {
		ret.id = 9;
	}
	//Now we check for numbers, integers or floats
	else if(curr >= '0' && curr <= '9')
	{
		char *pointer_end;
		ret.id = 0;
		ret.val = strtof(&str[*index], &pointer_end);

		//Some pointer arithmetic so next index is next token
		length = pointer_end - &str[*index];
	}
	//Check if curr is the variable
	else if(curr == 'x')
		ret.id = 1;
	//Only option left is that curr is the beginning of a function
	//if strncpy pads with 0s we create an err token, since all functions
	//are of the form xxx(expression), if it doesn't match any
	// of our functions we err token too.
	else
	{
		char substr[4];
		strncpy(substr, &str[*index], 3);
		//manually add '\0'
		substr[3] = '\0';
		
		if(strcmp("sin", substr) == 0)
			ret.id = 10;
		else if (strcmp("cos", substr) == 0)
			ret.id = 11;
		else if (strcmp("tan", substr) == 0)
			ret.id = 12;
		else if (strcmp("cot", substr) == 0)
			ret.id = 13;
		else if (strcmp("sec", substr) == 0)
			ret.id = 14;
		else if (strcmp("csc", substr) == 0)
			ret.id = 15;
		else if (strcmp("sqr", substr) == 0)
			ret.id = 16;
		else
			ret.id = -1;
	}
	//Determine how many blocks away the next token starts,
	//and modify index
	if(ret.id == 0)
		*index += length;
	else if((ret.id >= 1 && ret.id <= 9) || ret.id == -1)
		*index += 1;
	else if(ret.id >= 10 && ret.id <= 16)
		*index += 3;

	//Update prev_token_id
	*prev_token_id = ret.id;

	return ret;
}
