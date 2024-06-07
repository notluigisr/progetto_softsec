char *format_string_expand(const char *text, int *flags)
{
	GString *out;
	char code, *ret;
	int adv;

	g_return_val_if_fail(text != NULL, NULL);

	out = g_string_new(NULL);

	if (flags != NULL) *flags = 0;
	code = 0;
	while (*text != '\0') {
		if (code == '%') {
			
			adv = format_expand_styles(out, &text, flags);
			if (!adv) {
				g_string_append_c(out, '%');
				g_string_append_c(out, '%');
				g_string_append_c(out, *text);
			} else {
			  text += adv - 1;
			}
			code = 0;
		} else {
			if (*text == '%')
				code = *text;
			else
				g_string_append_c(out, *text);
		}

		text++;
	}

	ret = out->str;
	g_string_free(out, FALSE);
	return ret;
}