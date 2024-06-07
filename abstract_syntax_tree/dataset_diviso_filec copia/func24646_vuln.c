managesieve_parser_read_string(struct managesieve_parser *parser,
				   const unsigned char *data, size_t data_size)
{
	size_t i;

	

	
	for (i = parser->cur_pos; i < data_size; i++) {
		if (data[i] == '"') {

			if ( !uni_utf8_data_is_valid(data+1, i-1) ) {
				parser->error = "STR";
				return FALSE;
			}

			managesieve_parser_save_arg(parser, data, i);
			i++; 
			break;
		}

		if (data[i] == '\\') {
			if (i+1 == data_size) {
				
				break;
			}

			
			if (parser->str_first_escape < 0)
				parser->str_first_escape = i;

			
			i++;

			if ( !IS_QUOTED_SPECIAL(data[i]) ) {
				parser->error =
					"STR";
				return FALSE;
			}

			continue;
		}

		if ( (data[i] & 0x80) == 0 && !IS_SAFE_CHAR(data[i]) ) {
			parser->error = "STR";
			return FALSE;
		}
	}

	parser->cur_pos = i;
	return ( parser->cur_type == ARG_PARSE_NONE );
}