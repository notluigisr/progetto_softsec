static void test_json_parser_skip_array(void)
{
	static const char *test_input =
		"STR";
	struct json_parser *parser;
	struct istream *input;
	enum json_type type;
	const char *value, *error;
	int i;

	test_begin("STR");

	input = test_istream_create_data(test_input, strlen(test_input));
	parser = json_parser_init_flags(input, JSON_PARSER_NO_ROOT_OBJECT);
	test_assert(json_parse_next(parser, &type, &value) > 0 &&
		    type == JSON_TYPE_ARRAY);
	for (i = 1; i <= 6; i++) {
		test_assert(json_parse_next(parser, &type, &value) > 0 &&
			    type == JSON_TYPE_NUMBER && atoi(value) == i);
		json_parse_skip_next(parser);
	}
	test_assert(json_parse_next(parser, &type, &value) > 0 &&
		    type == JSON_TYPE_ARRAY_END);
	test_assert(json_parser_deinit(&parser, &error) == 0);
	i_stream_unref(&input);
	test_end();
}