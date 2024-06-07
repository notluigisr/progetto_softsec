static int remove_tree(struct qtree_mem_dqinfo *info, struct dquot *dquot,
		       uint *blk, int depth)
{
	char *buf = kmalloc(info->dqi_usable_bs, GFP_NOFS);
	int ret = 0;
	uint newblk;
	__le32 *ref = (__le32 *)buf;

	if (!buf)
		return -ENOMEM;
	ret = read_blk(info, *blk, buf);
	if (ret < 0) {
		quota_error(dquot->dq_sb, "STR",
			    *blk);
		goto out_buf;
	}
	newblk = le32_to_cpu(ref[get_index(info, dquot->dq_id, depth)]);
	if (depth == info->dqi_qtree_depth - 1) {
		ret = free_dqentry(info, dquot, newblk);
		newblk = 0;
	} else {
		ret = remove_tree(info, dquot, &newblk, depth+1);
	}
	if (ret >= 0 && !newblk) {
		int i;
		ref[get_index(info, dquot->dq_id, depth)] = cpu_to_le32(0);
		
		for (i = 0; i < (info->dqi_usable_bs >> 2) && !ref[i]; i++)
			;
		
		if (i == (info->dqi_usable_bs >> 2)
		    && *blk != QT_TREEOFF) {
			put_free_dqblk(info, buf, *blk);
			*blk = 0;
		} else {
			ret = write_blk(info, *blk, buf);
			if (ret < 0)
				quota_error(dquot->dq_sb,
					    "STR",
					    *blk);
		}
	}
out_buf:
	kfree(buf);
	return ret;
}