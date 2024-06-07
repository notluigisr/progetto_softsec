int message_parser_parse_next_block(struct message_parser_ctx *ctx,
				    struct message_block *block_r)
{
	int ret;
	bool eof = FALSE, full;

	i_zero(block_r);

	while ((ret = ctx->parse_next_block(ctx, block_r)) == 0) {
		ret = message_parser_read_more(ctx, block_r, &full);
		if (ret == 0) {
			i_assert(!ctx->input->blocking);
			return 0;
		}
		if (ret == -1) {
			i_assert(!eof);
			eof = TRUE;
		}
	}

	block_r->part = ctx->part;

	if (ret < 0 && ctx->part != NULL) {
		
		i_assert(ctx->input->eof || ctx->input->closed ||
			 ctx->input->stream_errno != 0 ||
			 ctx->broken_reason != NULL);
		while (ctx->part->parent != NULL)
			message_part_finish(ctx);
	}

	if (block_r->size == 0) {
		
		block_r->data = NULL;
	}
	return ret;
}