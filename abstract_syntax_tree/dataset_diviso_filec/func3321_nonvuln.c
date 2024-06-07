static bool replmd_check_urgent_attribute(const struct ldb_message_element *el)
{
	if (ldb_attr_in_list(urgent_attrs, el->name)) {
		return true;
	}
	return false;
}