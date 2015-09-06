#include "tokenizer.h"

void token_init(struct token *t)
{
	t -> id = 0;
	t -> str = "";
	t -> val = 0;
}

struct token get_next_token(char *str)
{
	struct token ret;
	token_init(&ret);

	return ret;
}
