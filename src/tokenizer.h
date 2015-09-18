#ifndef TOKERNIZER_H
#define TOKERNIZER_H

/**
 * @file tokenizer.h
 *
 * @brief tokenizer struct and prototypes
 *
 * functions for tokenizing
 *
 *	IDs:
 *	-1 = error token
 *	0 = number
 *	1 = variable
 *	2 = unary '-'
 *	3 = binary '-'
 *	4 = '+'
 *	5 = '*'
 *	6 = '/'
 *	7 = '^'
 *	8 = '('
 *	9 = ')'
 *	10 = sin
 *	11 = cos
 *	12 = tan
 *	13 = cot
 *	14 = sec
 *	15 = csc
 *	16 = sqr
 */

/**
 * @brief tokenizer struct
 *
 *	IDs:
 *	-1 = error token
 *	0 = number
 *	1 = variable
 *	2 = unary '-'
 *	3 = binary '-'
 *	4 = '+'
 *	5 = '*'
 *	6 = '/'
 *	7 = '^'
 *	8 = '('
 *	9 = ')'
 *	10 = sin
 *	11 = cos
 *	12 = tan
 *	13 = cot
 *	14 = sec
 *	15 = csc
 *	16 = sqr
 */

struct token
{
	short id;
	float val;
};

/**
 * @brief initialize token
 * 
 * @param t token to initialize
 */
void token_init(struct token *t);

/**
 * @brief tokenize string
 * 
 * @param str string to tokenize
 * @param index index of next token
 * @param prev_token_id previous token ID, should be 0 when called for the first time
 */
struct token get_next_token(const char *str, int *index, int *prev_token_id);


#endif /* TOKERNIZER_H */
