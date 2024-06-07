int ext4_mb_add_groupinfo(struct super_block *sb, ext4_group_t group,
			  struct ext4_group_desc *desc)
{
	int i;
	int metalen = 0;
	int idx = group >> EXT4_DESC_PER_BLOCK_BITS(sb);
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct ext4_group_info **meta_group_info;
	struct kmem_cache *cachep = get_groupinfo_cache(sb->s_blocksize_bits);

	
	if (group % EXT4_DESC_PER_BLOCK(sb) == 0) {
		metalen = sizeof(*meta_group_info) <<
			EXT4_DESC_PER_BLOCK_BITS(sb);
		meta_group_info = kmalloc(metalen, GFP_NOFS);
		if (meta_group_info == NULL) {
			ext4_msg(sb, KERN_ERR, "STR"
				 "STR");
			goto exit_meta_group_info;
		}
		rcu_read_lock();
		rcu_dereference(sbi->s_group_info)[idx] = meta_group_info;
		rcu_read_unlock();
	}

	meta_group_info = sbi_array_rcu_deref(sbi, s_group_info, idx);
	i = group & (EXT4_DESC_PER_BLOCK(sb) - 1);

	meta_group_info[i] = kmem_cache_zalloc(cachep, GFP_NOFS);
	if (meta_group_info[i] == NULL) {
		ext4_msg(sb, KERN_ERR, "STR");
		goto exit_group_info;
	}
	set_bit(EXT4_GROUP_INFO_NEED_INIT_BIT,
		&(meta_group_info[i]->bb_state));

	
	if (ext4_has_group_desc_csum(sb) &&
	    (desc->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT))) {
		meta_group_info[i]->bb_free =
			ext4_free_clusters_after_init(sb, group, desc);
	} else {
		meta_group_info[i]->bb_free =
			ext4_free_group_clusters(sb, desc);
	}

	INIT_LIST_HEAD(&meta_group_info[i]->bb_prealloc_list);
	init_rwsem(&meta_group_info[i]->alloc_sem);
	meta_group_info[i]->bb_free_root = RB_ROOT;
	meta_group_info[i]->bb_largest_free_order = -1;  

	mb_group_bb_bitmap_alloc(sb, meta_group_info[i], group);
	return 0;

exit_group_info:
	
	if (group % EXT4_DESC_PER_BLOCK(sb) == 0) {
		struct ext4_group_info ***group_info;

		rcu_read_lock();
		group_info = rcu_dereference(sbi->s_group_info);
		kfree(group_info[idx]);
		group_info[idx] = NULL;
		rcu_read_unlock();
	}
exit_meta_group_info:
	return -ENOMEM;
} 