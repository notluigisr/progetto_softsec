static int samldb_check_user_account_control_rules(struct samldb_ctx *ac,
						   struct dom_sid *sid,
						   uint32_t req_uac,
						   uint32_t user_account_control,
						   uint32_t user_account_control_old,
						   bool is_computer_objectclass)
{
	int ret;
	struct dsdb_control_password_user_account_control *uac = NULL;

	ret = samldb_check_user_account_control_invariants(ac, user_account_control);
	if (ret != LDB_SUCCESS) {
		return ret;
	}
	ret = samldb_check_user_account_control_objectclass_invariants(ac,
								       user_account_control,
								       user_account_control_old,
								       is_computer_objectclass);
	if (ret != LDB_SUCCESS) {
		return ret;
	}

	ret = samldb_check_user_account_control_acl(ac, sid, user_account_control, user_account_control_old);
	if (ret != LDB_SUCCESS) {
		return ret;
	}

	uac = talloc_zero(ac->req,
			  struct dsdb_control_password_user_account_control);
	if (uac == NULL) {
		return ldb_module_oom(ac->module);
	}

	uac->req_flags = req_uac;
	uac->old_flags = user_account_control_old;
	uac->new_flags = user_account_control;

	ret = ldb_request_add_control(ac->req,
				DSDB_CONTROL_PASSWORD_USER_ACCOUNT_CONTROL_OID,
				false, uac);
	if (ret != LDB_SUCCESS) {
		return ret;
	}

	return ret;
}