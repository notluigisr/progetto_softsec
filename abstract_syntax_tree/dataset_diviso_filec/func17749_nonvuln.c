int cil_gen_typeattributeset(struct cil_db *db, struct cil_tree_node *parse_current, struct cil_tree_node *ast_node)
{
	enum cil_syntax syntax[] = {
		CIL_SYN_STRING,
		CIL_SYN_STRING,
		CIL_SYN_STRING | CIL_SYN_LIST,
		CIL_SYN_END
	};
	int syntax_len = sizeof(syntax)/sizeof(*syntax);
	struct cil_typeattributeset *attrset = NULL;
	int rc = SEPOL_ERR;

	if (db == NULL || parse_current == NULL || ast_node == NULL) {
		goto exit;
	}

	rc = __cil_verify_syntax(parse_current, syntax, syntax_len);
	if (rc != SEPOL_OK) {
		goto exit;
	}

	cil_typeattributeset_init(&attrset);

	attrset->attr_str = parse_current->next->data;

	rc = cil_gen_expr(parse_current->next->next, CIL_TYPE, &attrset->str_expr);
	if (rc != SEPOL_OK) {
		goto exit;
	}
	ast_node->data = attrset;
	ast_node->flavor = CIL_TYPEATTRIBUTESET;

	return SEPOL_OK;

exit:
	cil_tree_log(parse_current, CIL_ERR, "STR");
	cil_destroy_typeattributeset(attrset);
	return rc;
}