#include <stdlib.h>
#include <check.h>
#include "../src/tokenizer.h"
#include "../src/grammar_checker.h"

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

}
END_TEST

START_TEST(test_grammar_check)
{
 	ck_assert_msg(1 == 1, "yeh");
}
END_TEST

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

	s = suite_create("Grammar");

	/* main case*/
	tc_grammar = tcase_create("GrammarMain");

	tcase_add_test(tc_grammar, test_grammar_check);
	suite_add_tcase(s, tc_grammar);

	return s;
}

int main()
{
	int number_failed;
	Suite *token_s;
	Suite *grammar_s;
	SRunner *sr;

	token_s = tokenizer_suite();
	grammar_s = grammar_suite();

	sr = srunner_create(token_s);
	srunner_add_suite(sr, grammar_s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
