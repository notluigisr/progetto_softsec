static void ext4_mb_normalize_group_request(struct ext4_allocation_context *ac)
{
	struct super_block *sb = ac->ac_sb;
	struct ext4_locality_group *lg = ac->ac_lg;

	BUG_ON(lg == NULL);
	ac->ac_g_ex.fe_len = EXT4_SB(sb)->s_mb_group_prealloc;
	mb_debug(1, "STR",
		current->pid, ac->ac_g_ex.fe_len);
}