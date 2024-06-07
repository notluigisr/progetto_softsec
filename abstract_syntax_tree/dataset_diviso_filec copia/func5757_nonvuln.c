static int calipso_doi_add(struct calipso_doi *doi_def,
			   struct netlbl_audit *audit_info)
{
	int ret_val = -EINVAL;
	u32 doi;
	u32 doi_type;
	struct audit_buffer *audit_buf;

	doi = doi_def->doi;
	doi_type = doi_def->type;

	if (doi_def->doi == CALIPSO_DOI_UNKNOWN)
		goto doi_add_return;

	refcount_set(&doi_def->refcount, 1);

	spin_lock(&calipso_doi_list_lock);
	if (calipso_doi_search(doi_def->doi)) {
		spin_unlock(&calipso_doi_list_lock);
		ret_val = -EEXIST;
		goto doi_add_return;
	}
	list_add_tail_rcu(&doi_def->list, &calipso_doi_list);
	spin_unlock(&calipso_doi_list_lock);
	ret_val = 0;

doi_add_return:
	audit_buf = netlbl_audit_start(AUDIT_MAC_CALIPSO_ADD, audit_info);
	if (audit_buf) {
		const char *type_str;

		switch (doi_type) {
		case CALIPSO_MAP_PASS:
			type_str = "STR";
			break;
		default:
			type_str = "STR";
		}
		audit_log_format(audit_buf,
				 "STR",
				 doi, type_str, ret_val == 0 ? 1 : 0);
		audit_log_end(audit_buf);
	}

	return ret_val;
}