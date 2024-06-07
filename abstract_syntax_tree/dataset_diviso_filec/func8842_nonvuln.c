static int vcpu_stat_get_per_vm_open(struct inode *inode, struct file *file)
{
	__simple_attr_check_format("STR", 0ull);
	return kvm_debugfs_open(inode, file, vcpu_stat_get_per_vm,
				 NULL, "STR");
}