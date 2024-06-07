static int pcrypt_sysfs_add(struct padata_instance *pinst, const char *name)
{
	int ret;

	pinst->kobj.kset = pcrypt_kset;
	ret = kobject_add(&pinst->kobj, NULL, name);
	if (!ret)
		kobject_uevent(&pinst->kobj, KOBJ_ADD);

	return ret;
}