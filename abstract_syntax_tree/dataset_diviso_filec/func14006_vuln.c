v9fs_stat2inode(struct p9_wstat *stat, struct inode *inode,
	struct super_block *sb)
{
	umode_t mode;
	char ext[32];
	char tag_name[14];
	unsigned int i_nlink;
	struct v9fs_session_info *v9ses = sb->s_fs_info;
	struct v9fs_inode *v9inode = V9FS_I(inode);

	set_nlink(inode, 1);

	inode->i_atime.tv_sec = stat->atime;
	inode->i_mtime.tv_sec = stat->mtime;
	inode->i_ctime.tv_sec = stat->mtime;

	inode->i_uid = v9ses->dfltuid;
	inode->i_gid = v9ses->dfltgid;

	if (v9fs_proto_dotu(v9ses)) {
		inode->i_uid = stat->n_uid;
		inode->i_gid = stat->n_gid;
	}
	if ((S_ISREG(inode->i_mode)) || (S_ISDIR(inode->i_mode))) {
		if (v9fs_proto_dotu(v9ses) && (stat->extension[0] != '\0')) {
			
			strlcpy(ext, stat->extension, sizeof(ext));
			
			sscanf(ext, "STR", tag_name, &i_nlink);
			if (!strncmp(tag_name, "STR", 13))
				set_nlink(inode, i_nlink);
		}
	}
	mode = p9mode2perm(v9ses, stat);
	mode |= inode->i_mode & ~S_IALLUGO;
	inode->i_mode = mode;
	i_size_write(inode, stat->length);

	
	inode->i_blocks = (i_size_read(inode) + 512 - 1) >> 9;
	v9inode->cache_validity &= ~V9FS_INO_INVALID_ATTR;
}