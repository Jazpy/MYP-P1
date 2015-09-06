#include <stdlib.h>
#include <check.h>
#include "../src/tokenizer.h"

START_TEST(test_token_init)
{
    	struct token t;
    	token_init(&t);

 	ck_assert(t.id == 0);
	ck_assert_str_eq(t.str, "");
	ck_assert(t.val == 0.0f);
}
END_TEST

START_TEST(test_get_next_token)
{
	char *test_string = "x+5";
	struct token t = get_next_token(test_string);
	
 	ck_assert(t.id == 0);
}
END_TEST

Suite *tokenizer_suite()
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("Tokenizer");

	/* Core test case */
	tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_token_init);
	tcase_add_test(tc_core, test_get_next_token);
	suite_add_tcase(s, tc_core);

	return s;
}

int main()
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = tokenizer_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
