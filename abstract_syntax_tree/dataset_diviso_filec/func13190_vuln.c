static const char *escape_identifier(const char *identifier)
{
	size_t pos = strcspn(identifier, "STR");
	
	if (identifier[pos] == '\0')
		return identifier;

	size_t len = strlen(identifier);
	string_t *new_id = t_str_new(len);
	str_append_data(new_id, identifier, pos);

	for (size_t i = pos; i < len; i++) {
	        switch (identifier[i]) {
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
	                str_append_c(new_id, identifier[i]);
	                break;
	        }
	}
	return str_c(new_id);
}