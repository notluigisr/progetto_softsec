hugetlbfs_fill_super(struct super_block *sb, void *data, int silent)
{
	int ret;
	struct hugetlbfs_config config;
	struct hugetlbfs_sb_info *sbinfo;

	save_mount_options(sb, data);

	config.max_hpages = -1; 
	config.nr_inodes = -1; 
	config.uid = current_fsuid();
	config.gid = current_fsgid();
	config.mode = 0755;
	config.hstate = &default_hstate;
	config.min_hpages = -1; 
	ret = hugetlbfs_parse_options(data, &config);
	if (ret)
		return ret;

	sbinfo = kmalloc(sizeof(struct hugetlbfs_sb_info), GFP_KERNEL);
	if (!sbinfo)
		return -ENOMEM;
	sb->s_fs_info = sbinfo;
	sbinfo->hstate = config.hstate;
	spin_lock_init(&sbinfo->stat_lock);
	sbinfo->max_inodes = config.nr_inodes;
	sbinfo->free_inodes = config.nr_inodes;
	sbinfo->spool = NULL;
	
	if (config.max_hpages != -1 || config.min_hpages != -1) {
		sbinfo->spool = hugepage_new_subpool(config.hstate,
							config.max_hpages,
							config.min_hpages);
		if (!sbinfo->spool)
			goto out_free;
	}
	sb->s_maxbytes = MAX_LFS_FILESIZE;
	sb->s_blocksize = huge_page_size(config.hstate);
	sb->s_blocksize_bits = huge_page_shift(config.hstate);
	sb->s_magic = HUGETLBFS_MAGIC;
	sb->s_op = &hugetlbfs_ops;
	sb->s_time_gran = 1;
	sb->s_root = d_make_root(hugetlbfs_get_root(sb, &config));
	if (!sb->s_root)
		goto out_free;
	return 0;
out_free:
	kfree(sbinfo->spool);
	kfree(sbinfo);
	return -ENOMEM;
}