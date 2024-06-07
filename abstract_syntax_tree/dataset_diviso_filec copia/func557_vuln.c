static void test_json_append_escaped(void)
{
	string_t *str = t_str_new(32);

	test_begin("STR");
	json_append_escaped(str, "STR");
	test_assert(strcmp(str_c(str), "STR") == 0);
	test_end();
}