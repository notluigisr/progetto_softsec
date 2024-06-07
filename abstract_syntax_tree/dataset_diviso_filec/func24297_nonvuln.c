void btrfs_create_pending_block_groups(struct btrfs_trans_handle *trans)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_block_group *block_group;
	int ret = 0;

	if (!trans->can_flush_pending_bgs)
		return;

	while (!list_empty(&trans->new_bgs)) {
		int index;

		block_group = list_first_entry(&trans->new_bgs,
					       struct btrfs_block_group,
					       bg_list);
		if (ret)
			goto next;

		index = btrfs_bg_flags_to_raid_index(block_group->flags);

		ret = insert_block_group_item(trans, block_group);
		if (ret)
			btrfs_abort_transaction(trans, ret);
		ret = btrfs_finish_chunk_alloc(trans, block_group->start,
					block_group->length);
		if (ret)
			btrfs_abort_transaction(trans, ret);
		add_block_group_free_space(trans, block_group);

		
		if (block_group->space_info->block_group_kobjs[index] == NULL)
			btrfs_sysfs_add_block_group_type(block_group);

		
next:
		btrfs_delayed_refs_rsv_release(fs_info, 1);
		list_del_init(&block_group->bg_list);
	}
	btrfs_trans_release_chunk_metadata(trans);
}