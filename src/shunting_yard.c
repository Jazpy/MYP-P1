#include <stdlib.h>
#include <stdio.h>
#include "shunting_yard.h"
#include "tokenizer.h"

struct node *parse_linked_list(struct node *head)
{
	struct token initial;
	token_init(&initial);
	initial.id = -1;

	//our hackish queue
	struct node *queue = malloc(sizeof(struct node));
	struct node *queue_con = queue;
	struct node *queue_prev = queue_con;
	queue -> t = initial;

	//our hackish stack
	struct node *stack = malloc(sizeof(struct node));
	stack -> next = 0;
	stack -> t = initial;

	while(head != 0)
	{
		struct token curr_tok = head -> t;		

	 	// if it's a number or var we add to output
		if(curr_tok.id == 0 || curr_tok.id == 1)
		{
			queue_prev = queue_con;
			queue_con -> t = curr_tok;
			queue_con -> next = malloc(sizeof(struct node));
			queue_con = queue_con -> next;
			queue_con -> next = 0;
		//if it's a function it goes on the stack
		} else if(curr_tok.id >= 10 && curr_tok.id <= 16){
			struct node *temp_stack = stack;
			stack = malloc(sizeof(struct node));
			stack -> t = curr_tok;
			stack -> next = temp_stack;
		} else if(curr_tok.id >= 2 && curr_tok.id <= 7){
			struct token top_stack;

			if(stack == 0)
				top_stack.id = 0;
			else
				top_stack = stack -> t;
		
			while(top_stack.id >= 2 && top_stack.id <= 7)
			{
				int changed = 0;
				//left associative
				if(curr_tok.id >= 3 && curr_tok.id <= 6)
				{
					int top_prec = top_stack.id;
					int curr_prec = curr_tok.id;
					if(top_prec == 6 ||
						top_prec == 4)
						--top_prec;
					else
						top_prec = 8;

					if(curr_prec == 6 ||
						curr_prec == 4)
						--curr_prec;

					if(curr_prec <= top_prec)
					{
						queue_prev = 
							queue_con;
						queue_con -> t =
							top_stack;
						queue_con -> next =
							malloc(sizeof(
							struct node));
						queue_con = queue_con ->
							next;
						queue_con -> next = 0;

						struct node* stack_temp;
						stack_temp = stack;

						stack = stack -> next;

						free(stack_temp);
						changed = 1;
					}
				} else if(curr_tok.id == 2 &&
					top_stack.id == 7)
				{
					queue_prev = queue_con;
					queue_con -> t = top_stack;
					queue_con -> next = malloc(sizeof(
						struct node));
					queue_con = queue_con -> next;
					queue_con -> next = 0;

					struct node* stack_temp;
					stack_temp = stack;
					stack = stack -> next;

					free(stack_temp);
					changed = 1;
				}

				if(changed)
				{
					if(stack == 0)
						top_stack.id = 0;
					else
						top_stack = stack -> t;
				} else 
					top_stack.id = 0;
			}

			struct node *temp_stack = stack;
			stack = malloc(sizeof(struct node));
			stack -> t = curr_tok;
			stack -> next = temp_stack;
		} else if(curr_tok.id == 8){
			struct node *temp_stack = stack;
			stack = malloc(sizeof(struct node));
			stack -> t = curr_tok;
			stack -> next = temp_stack;
		} else if(curr_tok.id == 9){
			while(stack -> t.id != 8)
			{
				queue_prev = queue_con;
				queue_con -> t = stack -> t;
				queue_con -> next = malloc(sizeof(
					struct node));
				queue_con = queue_con -> next;
				queue_con -> next = 0;

				struct node* stack_temp;
				stack_temp = stack;
				stack = stack -> next;

				free(stack_temp);
			}

			//discard left paren
			struct node* stack_temp;
			stack_temp = stack;
			stack = stack -> next;

			free(stack_temp);

			if(stack -> t.id >= 10 && stack -> t.id <= 16)
			{
				queue_prev = queue_con;
				queue_con -> t = stack -> t;
				queue_con -> next = malloc(sizeof(
					struct node));
				queue_con = queue_con -> next;
				queue_con -> next = 0;

				struct node* stack_temp;
				stack_temp = stack;
				stack = stack -> next;

				free(stack_temp);
			}
		}
	
		head = head -> next;
	}
	
	while(stack != 0 && stack -> t.id != -1)
	{
		queue_prev = queue_con;
		queue_con -> t = stack -> t;
		queue_con -> next = malloc(sizeof(struct node));
		queue_con = queue_con -> next;
		queue_con -> next = 0;

		struct node* stack_temp;
		stack_temp = stack;
		stack = stack -> next;

		free(stack_temp);
	}

	//clean up linked list's trailing junk
	queue_prev -> next = 0;
	
	return queue;
}
