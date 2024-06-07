static void test_json_append_escaped_data(void)
{
	static const unsigned char test_input[] =
		"STR";
	string_t *str = t_str_new(32);

	test_begin("STR");
	json_append_escaped_data(str, test_input, sizeof(test_input)-1);
	test_assert(strcmp(str_c(str), "STR") == 0);
	test_end();
}