static ssize_t remove_slot_store(struct kobject *kobj,
				 struct kobj_attribute *attr,
				 const char *buf, size_t nbytes)
{
	char drc_name[MAX_DRC_NAME_LEN];
	int rc;
	char *end;

	if (nbytes >= MAX_DRC_NAME_LEN)
		return 0;

	memcpy(drc_name, buf, nbytes);

	end = strchr(drc_name, '\n');
	if (!end)
		end = &drc_name[nbytes];
	*end = '\0';

	rc = dlpar_remove_slot(drc_name);
	if (rc)
		return rc;

	return nbytes;
}