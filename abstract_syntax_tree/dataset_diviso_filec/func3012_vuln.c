int ext4_data_block_valid(struct ext4_sb_info *sbi, ext4_fsblk_t start_blk,
			  unsigned int count)
{
	struct ext4_system_blocks *system_blks;
	int ret;

	
	rcu_read_lock();
	system_blks = rcu_dereference(sbi->system_blks);
	ret = ext4_data_block_valid_rcu(sbi, system_blks, start_blk,
					count);
	rcu_read_unlock();
	return ret;
}