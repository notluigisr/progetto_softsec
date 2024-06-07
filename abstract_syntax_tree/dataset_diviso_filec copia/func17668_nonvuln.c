static inline int security_dentry_open(struct file *file,
				       const struct cred *cred)
{
	return 0;
}