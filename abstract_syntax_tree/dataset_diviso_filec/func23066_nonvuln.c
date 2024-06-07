bool test_r_str_ansi_len(void) {
	int len;

	len = r_str_ansi_len ("STR");
	mu_assert_eq (len, 7, "STR");

	len = r_str_ansi_len ("STR");
	mu_assert_eq (len, 7, "STR");

	len = r_str_ansi_len ("STR");
	mu_assert_eq (len, 7, "STR");

	len = r_str_ansi_len ("STR");
	mu_assert_eq (len, 7, "STR");

	len = r_str_ansi_len ("STR");
	mu_assert_eq (len, 8, "STR");

	len = r_str_ansi_len ("STR");
	mu_assert_eq (len, 9, "STR");

	len = r_str_ansi_len ("STR");
	mu_assert_eq (len, 10, "STR");

	mu_end;
}