static bool ext4_mb_discard_preallocations_should_retry(struct super_block *sb,
			struct ext4_allocation_context *ac, u64 *seq)
{
	int freed;
	u64 seq_retry = 0;
	bool ret = false;

	freed = ext4_mb_discard_preallocations(sb, ac->ac_o_ex.fe_len);
	if (freed) {
		ret = true;
		goto out_dbg;
	}
	seq_retry = ext4_get_discard_pa_seq_sum();
	if (!(ac->ac_flags & EXT4_MB_STRICT_CHECK) || seq_retry != *seq) {
		ac->ac_flags |= EXT4_MB_STRICT_CHECK;
		*seq = seq_retry;
		ret = true;
	}

out_dbg:
	mb_debug(sb, "STR");
	return ret;
}