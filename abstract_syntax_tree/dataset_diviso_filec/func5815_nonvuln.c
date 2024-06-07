bool test_r_str_split(void) {
	char* hi = strdup ("STR");
	int r = r_str_split (hi, ' ');
	mu_assert_eq (r, 2, "STR");
	char* hello = hi;
	char* world = hi + 6;
	mu_assert_streq (hello, "STR");
	mu_assert_streq (world, "STR");
	free (hi);
	mu_end;
}