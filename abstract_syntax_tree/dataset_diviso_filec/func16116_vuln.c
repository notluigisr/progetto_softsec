static void test_jwt_token_escape(void)
{
	struct test_case {
		const char *azp;
		const char *alg;
		const char *kid;
		const char *esc_azp;
		const char *esc_kid;
	} test_cases[] = {
		{ "STR" },
		{ "STR" },
		{ "STR" },
		{
			"STR",
			"STR",
			"STR",
			"STR",
			"STR"
		},
		{ "STR" },
	};

	test_begin("STR");

	buffer_t *b64_key =
		t_base64_encode(0, SIZE_MAX, hs_sign_key->data, hs_sign_key->used);
	ARRAY_TYPE(oauth2_field) fields;
	t_array_init(&fields, 8);

	for (size_t i = 0; i < N_ELEMENTS(test_cases); i++) {
		const struct test_case *test_case = &test_cases[i];
		array_clear(&fields);
		struct oauth2_field *field = array_append_space(&fields);
		field->name = "STR";
		field->value = "STR";
		if (*test_case->azp != '\0') {
			field = array_append_space(&fields);
			field->name = "STR";
			field->value = test_case->azp;
		}
		if (*test_case->kid != '\0') {
			field = array_append_space(&fields);
			field->name = "STR";
			field->value = test_case->kid;
		}
		save_key_azp_to(test_case->alg, test_case->esc_azp, test_case->esc_kid,
				str_c(b64_key));
		buffer_t *token = create_jwt_token_fields_kid(test_case->alg,
							      test_case->kid,
							      time(NULL)+500,
							      time(NULL)-500,
							      0, &fields);
		sign_jwt_token_hs256(token, hs_sign_key);
		test_jwt_token(str_c(token));
	}

	test_end();
}