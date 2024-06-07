static int process_pass1b_block(ext2_filsys fs EXT2FS_ATTR((unused)),
				blk64_t	*block_nr,
				e2_blkcnt_t blockcnt,
				blk64_t ref_blk EXT2FS_ATTR((unused)),
				int ref_offset EXT2FS_ATTR((unused)),
				void *priv_data)
{
	struct process_block_struct *p;
	e2fsck_t ctx;
	blk64_t	lc, pc;
	problem_t op;

	if (*block_nr == 0)
		return 0;
	p = (struct process_block_struct *) priv_data;
	ctx = p->ctx;
	lc = EXT2FS_B2C(fs, blockcnt);
	pc = EXT2FS_B2C(fs, *block_nr);

	if (!ext2fs_test_block_bitmap2(ctx->block_dup_map, *block_nr))
		goto finish;

	
	if (p->ino != EXT2_BAD_INO) {
		if (p->last_blk + 1 != *block_nr) {
			if (p->last_blk) {
				op = p->pctx->blk == p->pctx->blk2 ?
						PR_1B_DUP_BLOCK :
						PR_1B_DUP_RANGE;
				fix_problem(ctx, op, p->pctx);
			}
			p->pctx->blk = *block_nr;
		}
		p->pctx->blk2 = *block_nr;
		p->last_blk = *block_nr;
	}
	p->dup_blocks++;
	ext2fs_mark_inode_bitmap2(inode_dup_map, p->ino);

	
	if (blockcnt < 0 || lc != p->cur_cluster || pc != p->phys_cluster)
		add_dupe(ctx, p->ino, EXT2FS_B2C(fs, *block_nr), p->inode);

finish:
	p->cur_cluster = lc;
	p->phys_cluster = pc;
	return 0;
}