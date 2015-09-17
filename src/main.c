#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "view.h"
#include "grammar_checker.h"
#include "linked_list.h"
#include "binary_tree.h"
#include "shunting_yard.h"

int main()
{
	//INPUT HANDLING
	char input[512];

	printf("Input:\n");

	if(!fgets(input, sizeof(input), stdin))
	{
		fprintf(stderr, "Something went wrong with handling "
			"your input");

		return -1;
	}

	input[strcspn(input, "\r\n")] = 0;

	//TOKENIZAN
	int index = 0, prev_token_id = 0;
	struct node *token_head;
	struct node *conductor;
	token_head = malloc(sizeof(struct node));
	token_head -> next = 0;
	conductor = token_head;

	while(input[index] != '\0')
	{
		conductor -> t = get_next_token(input, &index,
			&prev_token_id);
	
		if(input[index] != '\0')
		{
			conductor -> next = malloc(sizeof(struct node));
			conductor = conductor -> next;
			conductor -> next = 0;
		}
	}

	//ANALYZAN
	const char *result = analyze_linked_list(token_head);
	
	if(strcmp(result, "s") != 0)
	{
		fprintf(stderr, "%s\n", result);

		return -1;
	}

    	struct node *parsed;
	parsed = parse_linked_list(token_head);

	//TREE GENERATAN
	struct tree_node *tree = make_tree(parsed);
	
	if(tree == 0)
	{
		fprintf(stderr, "error generating tree");

		return -1;
	}

	struct view window;

	while(0)
	{
		
	}
	
	//MEMORY FREEAN
	free_list(token_head);
	free_list(parsed);
	free_tree(tree);

	return 0;
}
