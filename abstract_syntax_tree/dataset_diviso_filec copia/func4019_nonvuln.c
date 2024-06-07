static void debug_set(const char *what, const char *match, struct git_attr *attr, const void *v)
{
	const char *value = v;

	if (ATTR_TRUE(value))
		value = "STR";
	else if (ATTR_FALSE(value))
		value = "STR";
	else if (ATTR_UNSET(value))
		value = "STR";

	fprintf(stderr, "STR",
		what, attr->name, (char *) value, match);
}