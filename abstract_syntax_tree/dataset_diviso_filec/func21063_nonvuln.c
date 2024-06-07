static int netlbl_cipsov4_add_local(struct genl_info *info,
				    struct netlbl_audit *audit_info)
{
	int ret_val;
	struct cipso_v4_doi *doi_def = NULL;

	if (!info->attrs[NLBL_CIPSOV4_A_TAGLST])
		return -EINVAL;

	doi_def = kmalloc(sizeof(*doi_def), GFP_KERNEL);
	if (doi_def == NULL)
		return -ENOMEM;
	doi_def->type = CIPSO_V4_MAP_LOCAL;

	ret_val = netlbl_cipsov4_add_common(info, doi_def);
	if (ret_val != 0)
		goto add_local_failure;

	ret_val = cipso_v4_doi_add(doi_def, audit_info);
	if (ret_val != 0)
		goto add_local_failure;
	return 0;

add_local_failure:
	cipso_v4_doi_free(doi_def);
	return ret_val;
}