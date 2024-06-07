static int show_vfsmnt(struct seq_file *m, void *v)
{
	struct vfsmount *mnt = v;
	int err = 0;
	static struct proc_fs_info {
		int flag;
		char *str;
	} fs_info[] = {
		{ MS_SYNCHRONOUS, "STR" },
		{ MS_DIRSYNC, "STR" },
		{ MS_MANDLOCK, "STR" },
		{ 0, NULL }
	};
	static struct proc_fs_info mnt_info[] = {
		{ MNT_NOSUID, "STR" },
		{ MNT_NODEV, "STR" },
		{ MNT_NOEXEC, "STR" },
		{ MNT_NOATIME, "STR" },
		{ MNT_NODIRATIME, "STR" },
		{ MNT_RELATIME, "STR" },
		{ 0, NULL }
	};
	struct proc_fs_info *fs_infop;

	mangle(m, mnt->mnt_devname ? mnt->mnt_devname : "STR");
	seq_putc(m, ' ');
	seq_path(m, mnt, mnt->mnt_root, "STR");
	seq_putc(m, ' ');
	mangle(m, mnt->mnt_sb->s_type->name);
	if (mnt->mnt_sb->s_subtype && mnt->mnt_sb->s_subtype[0]) {
		seq_putc(m, '.');
		mangle(m, mnt->mnt_sb->s_subtype);
	}
	seq_puts(m, mnt->mnt_sb->s_flags & MS_RDONLY ? "STR");
	for (fs_infop = fs_info; fs_infop->flag; fs_infop++) {
		if (mnt->mnt_sb->s_flags & fs_infop->flag)
			seq_puts(m, fs_infop->str);
	}
	for (fs_infop = mnt_info; fs_infop->flag; fs_infop++) {
		if (mnt->mnt_flags & fs_infop->flag)
			seq_puts(m, fs_infop->str);
	}
	if (mnt->mnt_sb->s_op->show_options)
		err = mnt->mnt_sb->s_op->show_options(m, mnt);
	seq_puts(m, "STR");
	return err;
}