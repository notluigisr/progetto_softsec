const char *ldb_msg_find_attr_as_string(const struct ldb_message *msg,
					const char *attr_name,
					const char *default_value)
{
	const struct ldb_val *v = ldb_msg_find_ldb_val(msg, attr_name);
	if (!v || !v->data) {
		return default_value;
	}
	if (v->data[v->length] != '\0') {
		return default_value;
	}
	return (const char *)v->data;
}