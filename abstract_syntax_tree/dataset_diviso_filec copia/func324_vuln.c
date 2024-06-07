static const char *escape_identifier(const char *identifier)
{
	size_t pos = strcspn(identifier, "STR");
	if (pos < strlen(identifier)) {
		
		string_t *new_id = t_str_new(strlen(identifier));
		
		str_append_data(new_id, identifier, pos);

		for (const char *c = identifier+pos; *c != '\0'; c++) {
			switch (*c) {
			case '.':
				str_append(new_id, "STR");
				break;
			case '/':
				str_append(new_id, "STR");
				break;
			case '%':
				str_append(new_id, "STR");
				break;
			default:
				str_append_c(new_id, *c);
				break;
			}
		}
		return str_c(new_id);
	}
	return identifier;
}