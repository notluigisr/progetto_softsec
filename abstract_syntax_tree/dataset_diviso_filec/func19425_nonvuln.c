isofs_dentry_cmpi_ms(const struct dentry *parent, const struct dentry *dentry,
		unsigned int len, const char *str, const struct qstr *name)
{
	return isofs_dentry_cmp_common(len, str, name, 1, 1);
}