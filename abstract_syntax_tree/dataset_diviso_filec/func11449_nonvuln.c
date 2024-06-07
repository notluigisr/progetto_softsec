static int ext4_mb_good_group_nolock(struct ext4_allocation_context *ac,
				     ext4_group_t group, int cr)
{
	struct ext4_group_info *grp = ext4_get_group_info(ac->ac_sb, group);
	struct super_block *sb = ac->ac_sb;
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	bool should_lock = ac->ac_flags & EXT4_MB_STRICT_CHECK;
	ext4_grpblk_t free;
	int ret = 0;

	if (should_lock)
		ext4_lock_group(sb, group);
	free = grp->bb_free;
	if (free == 0)
		goto out;
	if (cr <= 2 && free < ac->ac_g_ex.fe_len)
		goto out;
	if (unlikely(EXT4_MB_GRP_BBITMAP_CORRUPT(grp)))
		goto out;
	if (should_lock)
		ext4_unlock_group(sb, group);

	
	if (unlikely(EXT4_MB_GRP_NEED_INIT(grp))) {
		struct ext4_group_desc *gdp =
			ext4_get_group_desc(sb, group, NULL);
		int ret;

		
		if (cr < 2 &&
		    (!sbi->s_log_groups_per_flex ||
		     ((group & ((1 << sbi->s_log_groups_per_flex) - 1)) != 0)) &&
		    !(ext4_has_group_desc_csum(sb) &&
		      (gdp->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT))))
			return 0;
		ret = ext4_mb_init_group(sb, group, GFP_NOFS);
		if (ret)
			return ret;
	}

	if (should_lock)
		ext4_lock_group(sb, group);
	ret = ext4_mb_good_group(ac, group, cr);
out:
	if (should_lock)
		ext4_unlock_group(sb, group);
	return ret;
}