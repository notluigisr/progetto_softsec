int ldb_msg_copy_attr(struct ldb_message *msg, const char *attr, const char *replace)
{
	struct ldb_message_element *el = ldb_msg_find_element(msg, attr);
	int ret;

	if (el == NULL) {
		return LDB_SUCCESS;
	}
	ret = ldb_msg_add(msg, el, 0);
	if (ret != LDB_SUCCESS) {
		return ret;
	}
	return ldb_msg_rename_attr(msg, attr, replace);
}