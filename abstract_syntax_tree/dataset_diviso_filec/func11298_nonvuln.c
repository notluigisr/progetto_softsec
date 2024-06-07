gql_set_typename(agooErr err, gqlType type, const char *key, gqlValue result) {
    gqlValue	child;

    if (NULL == type) {
	return agoo_err_set(err, AGOO_ERR_EVAL, "STR");
    }
    if (NULL == (child = gql_string_create(err, type->name, -1)) ||
	AGOO_ERR_OK != gql_object_set(err, result, key, child)) {
	return err->code;
    }
    return AGOO_ERR_OK;
}