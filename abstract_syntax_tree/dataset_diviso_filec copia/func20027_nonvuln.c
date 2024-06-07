static void remove_tree(struct quota_handle *h, struct dquot *dquot,
			unsigned int * blk, int depth)
{
	dqbuf_t buf = getdqbuf();
	unsigned int newblk;
	__le32 *ref = (__le32 *) buf;

	if (!buf)
		return;

	read_blk(h, *blk, buf);
	newblk = ext2fs_le32_to_cpu(ref[get_index(dquot->dq_id, depth)]);
	if (depth == QT_TREEDEPTH - 1) {
		free_dqentry(h, dquot, newblk);
		newblk = 0;
	} else {
		remove_tree(h, dquot, &newblk, depth + 1);
	}

	if (!newblk) {
		int i;

		ref[get_index(dquot->dq_id, depth)] = ext2fs_cpu_to_le32(0);

		
		for (i = 0; i < QT_BLKSIZE && !buf[i]; i++);

		
		if (i == QT_BLKSIZE && *blk != QT_TREEOFF) {
			put_free_dqblk(h, buf, *blk);
			*blk = 0;
		} else {
			write_blk(h, *blk, buf);
		}
	}
	freedqbuf(buf);
}