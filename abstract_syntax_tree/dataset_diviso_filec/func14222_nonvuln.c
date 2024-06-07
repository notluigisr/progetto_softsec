test_json_parse_input(const char *test_input, enum json_parser_flags flags)
{
	struct json_parser *parser;
	struct istream *input;
	enum json_type type;
	const char *value, *error;
	int ret = 0;

	input = test_istream_create_data(test_input, strlen(test_input));
	parser = json_parser_init_flags(input, flags);
	while (json_parse_next(parser, &type, &value) > 0)
		ret++;
	if (json_parser_deinit(&parser, &error) < 0)
		ret = -1;
	i_stream_unref(&input);
	return ret;
}