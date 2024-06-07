static void pass1b(e2fsck_t ctx, char *block_buf)
{
	ext2_filsys fs = ctx->fs;
	ext2_ino_t ino = 0;
	struct ext2_inode_large inode;
	ext2_inode_scan	scan;
	struct process_block_struct pb;
	struct problem_context pctx;
	problem_t op;

	clear_problem_context(&pctx);

	if (!(ctx->options & E2F_OPT_PREEN))
		fix_problem(ctx, PR_1B_PASS_HEADER, &pctx);
	pctx.errcode = ext2fs_open_inode_scan(fs, ctx->inode_buffer_blocks,
					      &scan);
	if (pctx.errcode) {
		fix_problem(ctx, PR_1B_ISCAN_ERROR, &pctx);
		ctx->flags |= E2F_FLAG_ABORT;
		return;
	}
	ctx->stashed_inode = EXT2_INODE(&inode);
	pb.ctx = ctx;
	pb.pctx = &pctx;
	pctx.str = "STR";
	while (1) {
		if (ino % (fs->super->s_inodes_per_group * 4) == 1) {
			if (e2fsck_mmp_update(fs))
				fatal_error(ctx, 0);
		}
		pctx.errcode = ext2fs_get_next_inode_full(scan, &ino,
				EXT2_INODE(&inode), sizeof(inode));
		if (pctx.errcode == EXT2_ET_BAD_BLOCK_IN_INODE_TABLE)
			continue;
		if (pctx.errcode) {
			pctx.ino = ino;
			fix_problem(ctx, PR_1B_ISCAN_ERROR, &pctx);
			ctx->flags |= E2F_FLAG_ABORT;
			return;
		}
		if (!ino)
			break;
		pctx.ino = ctx->stashed_ino = ino;
		if ((ino != EXT2_BAD_INO) &&
		    !ext2fs_test_inode_bitmap2(ctx->inode_used_map, ino))
			continue;

		pb.ino = ino;
		pb.dup_blocks = 0;
		pb.inode = &inode;
		pb.cur_cluster = ~0;
		pb.phys_cluster = ~0;
		pb.last_blk = 0;
		pb.pctx->blk = pb.pctx->blk2 = 0;

		if (ext2fs_inode_has_valid_blocks2(fs, EXT2_INODE(&inode)) ||
		    (ino == EXT2_BAD_INO))
			pctx.errcode = ext2fs_block_iterate3(fs, ino,
					     BLOCK_FLAG_READ_ONLY, block_buf,
					     process_pass1b_block, &pb);
		
		if (ext2fs_has_feature_xattr(fs->super) &&
		    ext2fs_file_acl_block(fs, EXT2_INODE(&inode))) {
			blk64_t blk = ext2fs_file_acl_block(fs, EXT2_INODE(&inode));
			process_pass1b_block(fs, &blk,
					     BLOCK_COUNT_EXTATTR, 0, 0, &pb);
			ext2fs_file_acl_block_set(fs, EXT2_INODE(&inode), blk);
		}
		if (pb.dup_blocks) {
			if (ino != EXT2_BAD_INO) {
				op = pctx.blk == pctx.blk2 ?
					PR_1B_DUP_BLOCK : PR_1B_DUP_RANGE;
				fix_problem(ctx, op, pb.pctx);
			}
			end_problem_latch(ctx, PR_LATCH_DBLOCK);
			if (ino >= EXT2_FIRST_INODE(fs->super) ||
			    ino == EXT2_ROOT_INO)
				dup_inode_count++;
		}
		if (pctx.errcode)
			fix_problem(ctx, PR_1B_BLOCK_ITERATE, &pctx);
	}
	ext2fs_close_inode_scan(scan);
	e2fsck_use_inode_shortcuts(ctx, 0);
}