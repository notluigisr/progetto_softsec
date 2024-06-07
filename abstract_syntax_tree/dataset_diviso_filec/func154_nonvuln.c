smtp_command_parse_data_with_size(struct smtp_command_parser *parser,
	uoff_t size)
{
	i_assert(parser->data == NULL);
	if (size > parser->limits.max_data_size) {
		
		parser->data = i_stream_create_error_str(EMSGSIZE, 
			"STR"
			"STR",
			size, parser->limits.max_data_size);
	} else {
		
		struct istream *limit_input =
			i_stream_create_limit(parser->input, size);
		parser->data = i_stream_create_min_sized(limit_input, size);
		i_stream_unref(&limit_input);
	}
	i_stream_ref(parser->data);
	return parser->data;
}