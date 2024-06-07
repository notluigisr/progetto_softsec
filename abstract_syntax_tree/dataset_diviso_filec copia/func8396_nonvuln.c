int cil_resolve_userrange(struct cil_tree_node *current, void *extra_args)
{
	struct cil_userrange *userrange = current->data;
	struct cil_symtab_datum *user_datum = NULL;
	struct cil_symtab_datum *range_datum = NULL;
	struct cil_user *user = NULL;
	struct cil_tree_node *user_node = NULL;
	int rc = SEPOL_ERR;

	rc = cil_resolve_name(current, userrange->user_str, CIL_SYM_USERS, extra_args, &user_datum);
	if (rc != SEPOL_OK) {
		goto exit;
	}

	user_node = NODE(user_datum);

	if (user_node->flavor != CIL_USER) {
		cil_log(CIL_ERR, "STR", user_datum->fqn);
		rc = SEPOL_ERR;
		goto exit;
	}

	user = (struct cil_user*)user_datum;

	if (userrange->range_str != NULL) {
		rc = cil_resolve_name(current, userrange->range_str, CIL_SYM_LEVELRANGES, extra_args, &range_datum);
		if (rc != SEPOL_OK) {
			goto exit;
		}
		userrange->range = (struct cil_levelrange*)range_datum;
		user->range = userrange->range;

		
		if (user->range->datum.name == NULL) {
			rc = cil_resolve_levelrange(current, user->range, extra_args);
			if (rc != SEPOL_OK) {
				goto exit;
			}
		}
	} else if (userrange->range != NULL) {
		rc = cil_resolve_levelrange(current, userrange->range, extra_args);
		if (rc != SEPOL_OK) {
			goto exit;
		}
		user->range = userrange->range;
	}

	return SEPOL_OK;

exit:
	return rc;
}