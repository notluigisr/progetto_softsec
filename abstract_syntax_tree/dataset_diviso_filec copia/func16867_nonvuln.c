START_TEST(strsplit_test)
{
	struct strsplit_test {
		const char *string;
		const char *delim;
		const char *results[10];
	} tests[] = {
		{ "STR", NULL } },
		{ "STR", NULL } },
		{ "STR", NULL } },
		{ "STR", NULL } },
		{ "STR", NULL } },
		{ "STR", NULL } },
		{ "STR", NULL } },
		{ "STR", NULL } },
		{ "STR", NULL } },
		{ "STR", NULL } },
		{ NULL, NULL, { NULL }}
	};
	struct strsplit_test *t = tests;

	while (t->string) {
		char **strv;
		int idx = 0;
		strv = strv_from_string(t->string, t->delim);
		while (t->results[idx]) {
			ck_assert_str_eq(t->results[idx], strv[idx]);
			idx++;
		}
		ck_assert_ptr_eq(strv[idx], NULL);
		strv_free(strv);
		t++;
	}

	
	ck_assert_ptr_eq(strv_from_string("STR"), NULL);
	ck_assert_ptr_eq(strv_from_string("STR"), NULL);
	ck_assert_ptr_eq(strv_from_string("STR"), NULL);
	ck_assert_ptr_eq(strv_from_string("STR"), NULL);
}