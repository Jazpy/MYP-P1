#ifndef TOKERNIZER_H
#define TOKERNIZER_H

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

struct token
{
	short id;
	float val;
};

void token_init(struct token *t);

struct token get_next_token(char *str, int *index, int *prev_token_id);


#endif /* TOKERNIZER_H */
