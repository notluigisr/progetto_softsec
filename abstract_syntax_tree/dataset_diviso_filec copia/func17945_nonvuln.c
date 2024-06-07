static int cgroup_init_fs_context(struct fs_context *fc)
{
	struct cgroup_fs_context *ctx;

	ctx = kzalloc(sizeof(struct cgroup_fs_context), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->ns = current->nsproxy->cgroup_ns;
	get_cgroup_ns(ctx->ns);
	fc->fs_private = &ctx->kfc;
	if (fc->fs_type == &cgroup2_fs_type)
		fc->ops = &cgroup_fs_context_ops;
	else
		fc->ops = &cgroup1_fs_context_ops;
	put_user_ns(fc->user_ns);
	fc->user_ns = get_user_ns(ctx->ns->user_ns);
	fc->global = true;
	return 0;
}