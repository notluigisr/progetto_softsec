int cil_resolve_selinuxuser(struct cil_tree_node *current, void *extra_args)
{
	struct cil_selinuxuser *selinuxuser = current->data;
	struct cil_symtab_datum *user_datum = NULL;
	struct cil_symtab_datum *lvlrange_datum = NULL;
	struct cil_tree_node *user_node = NULL;
	int rc = SEPOL_ERR;

	rc = cil_resolve_name(current, selinuxuser->user_str, CIL_SYM_USERS, extra_args, &user_datum);
	if (rc != SEPOL_OK) {
		goto exit;
	}

	user_node = NODE(user_datum);

	if (user_node->flavor != CIL_USER) {
		cil_log(CIL_ERR, "STR", user_datum->fqn);
		rc = SEPOL_ERR;
		goto exit;
	}

	selinuxuser->user = (struct cil_user*)user_datum;

	if (selinuxuser->range_str != NULL) {
		rc = cil_resolve_name(current, selinuxuser->range_str, CIL_SYM_LEVELRANGES, extra_args, &lvlrange_datum);
		if (rc != SEPOL_OK) {
			goto exit;
		}
		selinuxuser->range = (struct cil_levelrange*)lvlrange_datum;

		
		if (selinuxuser->range->datum.name == NULL) {
			rc = cil_resolve_levelrange(current, selinuxuser->range, extra_args);
			if (rc != SEPOL_OK) {
				goto exit;
			}
		}
	} else if (selinuxuser->range != NULL) {
		rc = cil_resolve_levelrange(current, selinuxuser->range, extra_args);
		if (rc != SEPOL_OK) {
			goto exit;
		}
	}

	rc = SEPOL_OK;
exit:
	return rc;
}