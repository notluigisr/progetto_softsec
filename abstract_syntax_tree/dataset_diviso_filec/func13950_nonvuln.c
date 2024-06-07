static loff_t nfs_llseek_dir(struct file *filp, loff_t offset, int origin)
{
	mutex_lock(&filp->f_path.dentry->d_inode->i_mutex);
	switch (origin) {
		case 1:
			offset += filp->f_pos;
		case 0:
			if (offset >= 0)
				break;
		default:
			offset = -EINVAL;
			goto out;
	}
	if (offset != filp->f_pos) {
		filp->f_pos = offset;
		((struct nfs_open_context *)filp->private_data)->dir_cookie = 0;
	}
out:
	mutex_unlock(&filp->f_path.dentry->d_inode->i_mutex);
	return offset;
}