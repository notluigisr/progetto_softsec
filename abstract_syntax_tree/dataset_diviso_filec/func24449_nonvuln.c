static int can_idmap_mount(const struct mount_kattr *kattr, struct mount *mnt)
{
	struct vfsmount *m = &mnt->mnt;

	if (!kattr->mnt_userns)
		return 0;

	
	if (mnt_user_ns(m) != &init_user_ns)
		return -EPERM;

	
	if (!(m->mnt_sb->s_type->fs_flags & FS_ALLOW_IDMAP))
		return -EINVAL;

	
	if (m->mnt_sb->s_user_ns != &init_user_ns)
		return -EINVAL;

	
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	
	if (!is_anon_ns(mnt->mnt_ns))
		return -EINVAL;

	return 0;
}