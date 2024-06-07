static bool imap_parser_read_string(struct imap_parser *parser,
				    const unsigned char *data, size_t data_size)
{
	size_t i;

	
	for (i = parser->cur_pos; i < data_size; i++) {
		if (data[i] == '"') {
			imap_parser_save_arg(parser, data, i);

			i++; 
			break;
		}

		if (data[i] == '\0') {
			parser->error = IMAP_PARSE_ERROR_BAD_SYNTAX;
			parser->error_msg = "STR";
			return FALSE;
		}

		if (data[i] == '\\') {
			if (i+1 == data_size) {
				
				break;
			}

			
			if (parser->str_first_escape < 0)
				parser->str_first_escape = i;

			
			i++;
		}

		
		if (is_linebreak(data[i]) &&
		    (parser->flags & IMAP_PARSE_FLAG_MULTILINE_STR) == 0) {
			parser->error = IMAP_PARSE_ERROR_BAD_SYNTAX;
			parser->error_msg = "STR";
			return FALSE;
		}
	}

	parser->cur_pos = i;
	return parser->cur_type == ARG_PARSE_NONE;
}