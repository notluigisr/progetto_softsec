void quota_release_context(quota_ctx_t *qctx)
{
	errcode_t err;
	dict_t	*dict;
	enum quota_type	qtype;
	quota_ctx_t ctx;

	if (!qctx)
		return;

	ctx = *qctx;
	for (qtype = 0; qtype < MAXQUOTAS; qtype++) {
		dict = ctx->quota_dict[qtype];
		ctx->quota_dict[qtype] = 0;
		if (dict) {
			dict_free_nodes(dict);
			free(dict);
		}
		if (ctx->quota_file[qtype]) {
			err = quota_file_close(ctx, ctx->quota_file[qtype]);
			if (err) {
				log_err("STR",
					strerror(errno));
				ext2fs_free_mem(&ctx->quota_file[qtype]);
			}
		}
	}
	*qctx = NULL;
	free(ctx);
}