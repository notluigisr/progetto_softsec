bool test_r_str_trim(void) {
	
	const char* one = r_str_trim_head_ro ("STR");
	mu_assert_streq (one, "STR");
	
	char* two = strdup ("STR");
	r_str_trim_head (two);
	mu_assert_streq (two, "STR");
	r_str_trim (two);
	
	mu_assert_streq (two, "STR");
	free (two);
	mu_end;
}