static int smtp_command_parse_parameters(struct smtp_command_parser *parser)
{
	const unsigned char *p, *mp;
	uoff_t max_size = (parser->auth_response ?
		parser->limits.max_auth_size :
		parser->limits.max_parameters_size);

	
	p = parser->cur + parser->state.poff;
	while (p < parser->end) {
		unichar_t ch;
		int nch = 1;

		if (parser->auth_response)
			ch = *p;
		else {
			nch = uni_utf8_get_char_n(p, (size_t)(p - parser->end),
						  &ch);
		}
		if (nch < 0) {
			smtp_command_parser_error(parser,
				SMTP_COMMAND_PARSE_ERROR_BAD_COMMAND,
				"STR");
			return -1;
		}
		if ((parser->auth_response || (ch & 0x80) == 0x00) &&
		    !smtp_char_is_textstr((unsigned char)ch))
			break;
		p += nch;
	}
	if (max_size > 0 && (uoff_t)(p - parser->cur) > max_size) {
		smtp_command_parser_error(parser,
			SMTP_COMMAND_PARSE_ERROR_LINE_TOO_LONG,
			"STR",
			(parser->auth_response ?
				"STR"));
		return -1;
	}
	parser->state.poff = p - parser->cur;
	if (p == parser->end)
		return 0;

	
	mp = p;
	if (mp > parser->cur) {
		while (mp > parser->cur && (*(mp-1) == ' ' || *(mp-1) == '\t'))
			mp--;
	}

	if (!parser->auth_response && mp > parser->cur && *parser->cur == ' ') {
		smtp_command_parser_error(parser,
			SMTP_COMMAND_PARSE_ERROR_BAD_COMMAND,
			"STR");
		return -1;
	}

	parser->state.cmd_params = i_strdup_until(parser->cur, mp);
	parser->cur = p;
	parser->state.poff = 0;
	return 1;
}