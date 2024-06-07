static struct dentry *sockfs_mount(struct file_system_type *fs_type,
			 int flags, const char *dev_name, void *data)
{
	return mount_pseudo_xattr(fs_type, "STR", &sockfs_ops,
				  sockfs_xattr_handlers,
				  &sockfs_dentry_operations, SOCKFS_MAGIC);
}