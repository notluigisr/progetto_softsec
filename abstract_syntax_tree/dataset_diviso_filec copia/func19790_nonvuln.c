START_TEST(dimension_prop_parser)
{
	struct parser_test_dimension {
		char *tag;
		bool success;
		int x, y;
	} tests[] = {
		{ "STR", true, 10, 10 },
		{ "STR", true, 1, 20 },
		{ "STR", true, 1, 8000 },
		{ "STR", true, 238492, 428210 },
		{ "STR", false, 0, 0 },
		{ "STR", false, 0, 0 },
		{ "STR", false, 0, 0 },
		{ "STR", false, 0, 0 },
		{ "STR", false, 0, 0 },
		{ "STR", false, 0, 0 },
		{ "", false, 0, 0 },
		{ "STR", false, 0, 0 },
		{ "STR", false, 0, 0 },
		{ "STR", false, 0, 0 },
		{ "STR", false, 0, 0 },
		{ "STR", false, 0, 0 },
		{ NULL, false, 0, 0 }
	};
	int i;
	size_t x, y;
	bool success;

	for (i = 0; tests[i].tag != NULL; i++) {
		x = y = 0xad;
		success = parse_dimension_property(tests[i].tag, &x, &y);
		ck_assert(success == tests[i].success);
		if (success) {
			ck_assert_int_eq(x, tests[i].x);
			ck_assert_int_eq(y, tests[i].y);
		} else {
			ck_assert_int_eq(x, 0xad);
			ck_assert_int_eq(y, 0xad);
		}
	}

	success = parse_dimension_property(NULL, &x, &y);
	ck_assert(success == false);
}