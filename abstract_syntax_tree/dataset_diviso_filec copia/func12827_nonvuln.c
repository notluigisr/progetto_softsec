static inline void v2_mem2diskdqinfo(struct v2_disk_dqinfo *d,
				     struct util_dqinfo *m)
{
	d->dqi_bgrace = ext2fs_cpu_to_le32(m->dqi_bgrace);
	d->dqi_igrace = ext2fs_cpu_to_le32(m->dqi_igrace);
	d->dqi_flags = ext2fs_cpu_to_le32(m->u.v2_mdqi.dqi_flags & V2_DQF_MASK);
	d->dqi_blocks = ext2fs_cpu_to_le32(m->u.v2_mdqi.dqi_qtree.dqi_blocks);
	d->dqi_free_blk =
		ext2fs_cpu_to_le32(m->u.v2_mdqi.dqi_qtree.dqi_free_blk);
	d->dqi_free_entry =
		ext2fs_cpu_to_le32(m->u.v2_mdqi.dqi_qtree.dqi_free_entry);
}