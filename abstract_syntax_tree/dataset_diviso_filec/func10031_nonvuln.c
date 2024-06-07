static int nfs4_intent_set_file(struct nameidata *nd, struct path *path, struct nfs4_state *state, fmode_t fmode)
{
	struct file *filp;
	int ret;

	
	if (fmode & FMODE_EXEC) {
		ret = nfs_may_open(state->inode,
				state->owner->so_cred,
				nd->intent.open.flags);
		if (ret < 0)
			goto out_close;
	}
	filp = lookup_instantiate_filp(nd, path->dentry, NULL);
	if (!IS_ERR(filp)) {
		struct nfs_open_context *ctx;
		ctx = nfs_file_open_context(filp);
		ctx->state = state;
		return 0;
	}
	ret = PTR_ERR(filp);
out_close:
	nfs4_close_sync(path, state, fmode & (FMODE_READ|FMODE_WRITE));
	return ret;
}