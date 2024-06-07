create_attr_sval(
	int attr,
	char *s
	)
{
	attr_val *my_val;

	my_val = emalloc_zero(sizeof(*my_val));
	my_val->attr = attr;
	if (NULL == s)			
		s = estrdup("");
	my_val->value.s = s;
	my_val->type = T_String;

	return my_val;
}