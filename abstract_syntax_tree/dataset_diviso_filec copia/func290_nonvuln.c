static void do_async_commit(struct work_struct *work)
{
	struct btrfs_async_commit *ac =
		container_of(work, struct btrfs_async_commit, work);

	
	if (ac->newtrans->type & __TRANS_FREEZABLE)
		__sb_writers_acquired(ac->newtrans->fs_info->sb, SB_FREEZE_FS);

	current->journal_info = ac->newtrans;

	btrfs_commit_transaction(ac->newtrans);
	kfree(ac);
}