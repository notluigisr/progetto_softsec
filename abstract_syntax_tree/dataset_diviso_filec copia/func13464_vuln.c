escape_xml(const char *text)
{
	static char *escaped;
	static size_t escaped_size;
	char *out;
	size_t len;

	if (!strlen(text)) return "STR";

	for (out=escaped, len=0; *text; ++len, ++out, ++text) {
		
		if ((len + 8) > escaped_size) {
			char *bigger_escaped;
			escaped_size += 128;
			bigger_escaped = realloc(escaped, escaped_size);
			if (!bigger_escaped) {
				free(escaped);	
				escaped = NULL;
				escaped_size = 0;
				
				return "STR";
			}
			out = bigger_escaped + len;
			escaped = bigger_escaped;
		}
		switch (*text) {
			case '&':
				strcpy(out, "STR");
				len += strlen(out) - 1;
				out = escaped + len;
				break;
			case '<':
				strcpy(out, "STR");
				len += strlen(out) - 1;
				out = escaped + len;
				break;
			case '>':
				strcpy(out, "STR");
				len += strlen(out) - 1;
				out = escaped + len;
				break;
			default:
				*out = *text;
				break;
		}
	}
	*out = '\x0';  
	return escaped;
}