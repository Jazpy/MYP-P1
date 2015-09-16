#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <check.h>
#include "../src/tokenizer.h"
#include "../src/grammar_checker.h"
#include "../src/shunting_yard.h"
#include "../src/linked_list.h"
#include "../src/binary_tree.h"

START_TEST(test_shunting_yard)
{
	char *test_string = "(-x)";
	//char *test_string = "(-(x+5)/sqr(5.64))*2";
	int index = 0, prev_token_id = 0;

	struct node *head;
	struct node *conductor;
	head = malloc(sizeof(struct node));
	head -> next = 0;
	conductor = head;

	while(test_string[index] != '\0')
	{
		conductor -> t = get_next_token(test_string, &index,
			&prev_token_id);
	
		if(test_string[index] != '\0')
		{
			conductor -> next = malloc(sizeof(struct node));
			conductor = conductor -> next;
			conductor -> next = 0;
		}
	}

	const char *result = analyze_linked_list(head);
	printf("%s\n", result);

	struct node *con = head;

	while(con != 0)
	{
		printf("token id: %d\n", con -> t.id);

		if(con -> t.id == 0)
			printf("val: %f\n", con ->t.val);

		con = con -> next;
	}

    	struct node *parsed;
	parsed = parse_linked_list(head);
	con = parsed;

	printf("*****\n");

	while(con != 0)
	{
		printf("token id: %d\n", con -> t.id);
		
		if(con -> t.id == 0)
			printf("val: %f\n", con ->t.val);

		con = con -> next;
	}

 	ck_assert_msg(0 == 0);

	free_list(head);
	free_list(parsed);
}
END_TEST

START_TEST(test_token_init)
{
    	struct token t;
    	token_init(&t);

 	ck_assert_msg(t.id == 0, "failed init id");
 	ck_assert_msg(t.val == 0.00f, "failed init val");
}
END_TEST

START_TEST(test_get_next_token)
{
	char *test_string = "-x+(5.65*-4.00)/sincostancotseccscsqr(-son.";
	int index = 0, prev_token_id = 0;
	struct token t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 2, "failed 1");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 1, "failed 2");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 4, "failed 3");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 8, "failed 4");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 0, "failed 5");
 	ck_assert_msg(t.val == 5.65f, "failed 5.val");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 5, "failed 6");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 2, "failed 7");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 0, "failed 8");
 	ck_assert_msg(t.val == 4.00f, "failed 8.val");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 9, "failed 9");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 6, "failed 10");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 10, "failed 11");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 11, "failed 12");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 12, "failed 13");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 13, "failed 14");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 14, "failed 15");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 15, "failed 16");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 16, "failed 17");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 8, "failed 18");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == 2, "failed 19");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == -1, "failed 20");
	t = get_next_token(test_string, &index, &prev_token_id);
 	ck_assert_msg(t.id == -1, "failed 21");

	test_string = "";
	ck_assert_msg(t.id == -1, "failed 22");
}
END_TEST

START_TEST(test_grammar_check)
{
	char *test_string = "(-(x+5)/sqr(5.64))*2";
	int index = 0, prev_token_id = 0;

	struct node *root;
	struct node *conductor;
	root = (struct node*)malloc(sizeof(struct node));
	root -> next = 0;
	conductor = root;

	while(test_string[index] != '\0')
	{
		conductor -> t = get_next_token(test_string, &index,
			&prev_token_id);
	
		if(test_string[index] != '\0')
		{
			conductor -> next = malloc(sizeof(struct node));
			conductor = conductor -> next;
			conductor -> next = 0;
		}
	}

	const char *result = analyze_linked_list(root);
	printf("(-(x+5)/sqr(5.64))*2 says:\n");
	printf("%s\n", result);
	ck_assert_msg(strcmp(result, "s") == 0, "failed 1");

	free_list(root);
}
END_TEST

START_TEST(test_grammar_check_bad_start)
{
	char *test_string = ")x+5";
	int index = 0, prev_token_id = 0;

	struct node *root;
	struct node *conductor;
	root = (struct node*)malloc(sizeof(struct node));
	root -> next = 0;
	conductor = root;

	while(test_string[index] != '\0')
	{
		conductor -> t = get_next_token(test_string, &index,
			&prev_token_id);
	
		if(test_string[index] != '\0')
		{
			conductor -> next = malloc(sizeof(struct node));
			conductor = conductor -> next;
			conductor -> next = 0;
		}
	}

	const char *result = analyze_linked_list(root);
	printf(")x+5 says:\n");
	printf("%s\n", result);
	ck_assert_msg(strcmp(result, "can't start an equation with a closing parenthesis") == 0, "failed 1");

	free_list(root);
}
END_TEST

START_TEST(test_grammar_check_bad_paren)
{
	char *test_string = "(()()(())))";
	int index = 0, prev_token_id = 0;

	struct node *root;
	struct node *conductor;
	root = (struct node*)malloc(sizeof(struct node));
	root -> next = 0;
	conductor = root;

	while(test_string[index] != '\0')
	{
		conductor -> t = get_next_token(test_string, &index,
			&prev_token_id);
	
		if(test_string[index] != '\0')
		{
			conductor -> next = malloc(sizeof(struct node));
			conductor = conductor -> next;
			conductor -> next = 0;
		}
	}

	const char *result = analyze_linked_list(root);
	printf("(()()(()))) says:\n");
	printf("%s\n", result);
	ck_assert_msg(strcmp(result, "mismatched parenthesis") == 0, "failed 1");

	free_list(root);
}
END_TEST

START_TEST(test_grammar_check_bad_number)
{
	char *test_string = "(x+5)6";
	int index = 0, prev_token_id = 0;

	struct node *root;
	struct node *conductor;
	root = (struct node*)malloc(sizeof(struct node));
	root -> next = 0;
	conductor = root;

	while(test_string[index] != '\0')
	{
		conductor -> t = get_next_token(test_string, &index,
			&prev_token_id);
	
		if(test_string[index] != '\0')
		{
			conductor -> next = malloc(sizeof(struct node));
			conductor = conductor -> next;
			conductor -> next = 0;
		}
	}

	const char *result = analyze_linked_list(root);
	printf("(x+5)6 says:\n");
	printf("%s\n", result);
	ck_assert_msg(strcmp(result, "can't have anything other than an operator or a closing parenthesis right after a closing parenthesis") == 0, "failed 1");

	free_list(root);
}
END_TEST

START_TEST(test_grammar_check_bad_operator)
{
	char *test_string = "(+x+5)";
	int index = 0, prev_token_id = 0;

	struct node *root;
	struct node *conductor;
	root = (struct node*)malloc(sizeof(struct node));
	root -> next = 0;
	conductor = root;

	while(test_string[index] != '\0')
	{
		conductor -> t = get_next_token(test_string, &index,
			&prev_token_id);
	
		if(test_string[index] != '\0')
		{
			conductor -> next = malloc(sizeof(struct node));
			conductor = conductor -> next;
			conductor -> next = 0;
		}
	}

	const char *result = analyze_linked_list(root);
	printf("(+x+5) says:\n");
	printf("%s\n", result);
	ck_assert_msg(strcmp(result, "can't have an operator right after an opening parenthesis") == 0, "failed 1");

	free_list(root);
}
END_TEST

START_TEST(test_grammar_check_bad_function_name)
{
	char *test_string = "son(x)";
	int index = 0, prev_token_id = 0;

	struct node *root;
	struct node *conductor;
	root = (struct node*)malloc(sizeof(struct node));
	root -> next = 0;
	conductor = root;

	while(test_string[index] != '\0')
	{
		conductor -> t = get_next_token(test_string, &index,
			&prev_token_id);
	
		if(test_string[index] != '\0')
		{
			conductor -> next = malloc(sizeof(struct node));
			conductor = conductor -> next;
			conductor -> next = 0;
		}
	}

	const char *result = analyze_linked_list(root);
	printf("son(x) says:\n");
	printf("%s\n", result);
	ck_assert_msg(strcmp(result, "unrecognized expression, please refer to the README") == 0, "failed 1");

	free_list(root);
}
END_TEST

START_TEST(test_grammar_check_bad_function)
{
	char *test_string = "sinx";
	int index = 0, prev_token_id = 0;

	struct node *root;
	struct node *conductor;
	root = (struct node*)malloc(sizeof(struct node));
	root -> next = 0;
	conductor = root;

	while(test_string[index] != '\0')
	{
		conductor -> t = get_next_token(test_string, &index,
			&prev_token_id);
	
		if(test_string[index] != '\0')
		{
			conductor -> next = malloc(sizeof(struct node));
			conductor = conductor -> next;
			conductor -> next = 0;
		}
	}

	const char *result = analyze_linked_list(root);
	printf("sinx says:\n");
	printf("%s\n", result);
	ck_assert_msg(strcmp(result, "can't have anything other than an opening parenthesis after a function") == 0, "failed 1");

	free_list(root);
}
END_TEST

Suite *shunting_yard_suite()
{
	Suite *s;
	TCase *tc_shunting_yard;

	s = suite_create("ShuntingYard");

	/* core case */
	tc_shunting_yard = tcase_create("Core");

	tcase_add_test(tc_shunting_yard, test_shunting_yard);
	suite_add_tcase(s, tc_shunting_yard);

	return s;
}

Suite *tokenizer_suite()
{
	Suite *s;
	TCase *tc_init;
	TCase *tc_tokenize;

	s = suite_create("Tokenizer");

	/* init case */
	tc_init = tcase_create("Init");
	/* tokenizer case*/
	tc_tokenize = tcase_create("Tokenize");

	tcase_add_test(tc_init, test_token_init);
	tcase_add_test(tc_tokenize, test_get_next_token);
	suite_add_tcase(s, tc_init);
	suite_add_tcase(s, tc_tokenize);

	return s;
}

Suite *grammar_suite()
{
	Suite *s;
	TCase *tc_grammar;
	TCase *tc_mistakes;

	s = suite_create("Grammar");

	/* main case*/
	tc_grammar = tcase_create("GrammarMain");
	tc_mistakes = tcase_create("GrammarMistakes");

	tcase_add_test(tc_grammar, test_grammar_check);
	tcase_add_test(tc_mistakes, test_grammar_check_bad_start);
	tcase_add_test(tc_mistakes, test_grammar_check_bad_paren);
	tcase_add_test(tc_mistakes, test_grammar_check_bad_number);
	tcase_add_test(tc_mistakes, test_grammar_check_bad_operator);
	tcase_add_test(tc_mistakes, test_grammar_check_bad_function_name);
	tcase_add_test(tc_mistakes, test_grammar_check_bad_function);
	suite_add_tcase(s, tc_grammar);
	suite_add_tcase(s, tc_mistakes);

	return s;
}

int main()
{
	int number_failed;
	Suite *token_s;
	Suite *grammar_s;
	Suite *shunting_yard_s;
	SRunner *sr;

	token_s = tokenizer_suite();
	grammar_s = grammar_suite();
	shunting_yard_s = shunting_yard_suite();

	sr = srunner_create(token_s);
	srunner_add_suite(sr, grammar_s);
	srunner_add_suite(sr, shunting_yard_s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
