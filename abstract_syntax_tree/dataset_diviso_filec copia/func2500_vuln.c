static int target_xcopy_locate_se_dev_e4_iter(struct se_device *se_dev,
					      void *data)
{
	struct xcopy_dev_search_info *info = data;
	unsigned char tmp_dev_wwn[XCOPY_NAA_IEEE_REGEX_LEN];
	int rc;

	if (!se_dev->dev_attrib.emulate_3pc)
		return 0;

	memset(&tmp_dev_wwn[0], 0, XCOPY_NAA_IEEE_REGEX_LEN);
	target_xcopy_gen_naa_ieee(se_dev, &tmp_dev_wwn[0]);

	rc = memcmp(&tmp_dev_wwn[0], info->dev_wwn, XCOPY_NAA_IEEE_REGEX_LEN);
	if (rc != 0)
		return 0;

	info->found_dev = se_dev;
	pr_debug("STR", se_dev);

	rc = target_depend_item(&se_dev->dev_group.cg_item);
	if (rc != 0) {
		pr_err("STR",
		       rc, se_dev);
		return rc;
	}

	pr_debug("STR",
		 se_dev, &se_dev->dev_group);
	return 1;
}