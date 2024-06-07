static void __attribute__((constructor)) init(void)
{
	g_test_add_func("STR", test_parse_bool);
	g_test_add_func("STR", test_die);
	g_test_add_func("STR", test_die_with_errno);
	g_test_add_func("STR",
			test_sc_nonfatal_mkpath__relative);
	g_test_add_func("STR",
			test_sc_nonfatal_mkpath__absolute);
}