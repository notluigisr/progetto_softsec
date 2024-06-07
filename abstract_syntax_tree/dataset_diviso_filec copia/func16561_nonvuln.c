bool yang_get_default_bool(const char *xpath_fmt, ...)
{
	char xpath[XPATH_MAXLEN];
	const char *value;
	va_list ap;

	va_start(ap, xpath_fmt);
	vsnprintf(xpath, sizeof(xpath), xpath_fmt, ap);
	va_end(ap);

	value = yang_get_default_value(xpath);
	return yang_str2bool(value);
}