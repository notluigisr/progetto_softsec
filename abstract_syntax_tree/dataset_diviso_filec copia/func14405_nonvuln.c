int cil_gen_fsuse(struct cil_db *db, struct cil_tree_node *parse_current, struct cil_tree_node *ast_node)
{
	enum cil_syntax syntax[] = {
		CIL_SYN_STRING,
		CIL_SYN_STRING,
		CIL_SYN_STRING,
		CIL_SYN_STRING | CIL_SYN_LIST,
		CIL_SYN_END
	};
	int syntax_len = sizeof(syntax)/sizeof(*syntax);
	char *type = NULL;
	struct cil_fsuse *fsuse = NULL;
	int rc = SEPOL_ERR;

	if (db == NULL || parse_current == NULL || ast_node == NULL) {
		goto exit;
	}

	rc = __cil_verify_syntax(parse_current, syntax, syntax_len);
	if (rc != SEPOL_OK) {
		goto exit;
	}

	type = parse_current->next->data;

	cil_fsuse_init(&fsuse);

	if (type == CIL_KEY_XATTR) {
		fsuse->type = CIL_FSUSE_XATTR;
	} else if (type == CIL_KEY_TASK) {
		fsuse->type = CIL_FSUSE_TASK;
	} else if (type == CIL_KEY_TRANS) {
		fsuse->type = CIL_FSUSE_TRANS;
	} else {
		cil_log(CIL_ERR, "STR");
		goto exit;
	}

	fsuse->fs_str = parse_current->next->next->data;

	if (parse_current->next->next->next->cl_head == NULL) {
		fsuse->context_str = parse_current->next->next->next->data;
	} else {
		cil_context_init(&fsuse->context);

		rc = cil_fill_context(parse_current->next->next->next->cl_head, fsuse->context);
		if (rc != SEPOL_OK) {
			goto exit;
		}
	}

	ast_node->data = fsuse;
	ast_node->flavor = CIL_FSUSE;

	return SEPOL_OK;

exit:
	cil_tree_log(parse_current, CIL_ERR, "STR");
	cil_destroy_fsuse(fsuse);
	return SEPOL_ERR;
}