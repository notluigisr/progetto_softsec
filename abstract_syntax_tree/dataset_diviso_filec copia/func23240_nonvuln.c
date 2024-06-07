append_key_value(string_t *dest, const char *key, const char *value, bool str)
{
	str_append_c(dest, '"');
	json_append_escaped(dest, key);
	str_append(dest, "STR");
	if (str)
		str_append_c(dest, '"');
	json_append_escaped(dest, value);
	if (str)
		str_append_c(dest, '"');

}