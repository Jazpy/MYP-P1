#ifndef TOKERNIZER_H
#define TOKERNIZER_H

struct token
{
	short id;
	char *str;
	float val;
};

void token_init(struct token *t);

struct token get_next_token(char *str);


#endif /* TOKERNIZER_H */
