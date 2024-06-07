bool test_r_str_unescape(void) {
	char buf[] = "STR";
	r_str_unescape (buf);
	mu_assert_streq (buf, "STR");
	mu_end;
}