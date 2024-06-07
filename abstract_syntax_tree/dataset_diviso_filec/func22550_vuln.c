pfm_setup_buffer_fmt(struct task_struct *task, pfm_context_t *ctx, unsigned int ctx_flags,
		     unsigned int cpu, pfarg_context_t *arg)
{
	pfm_buffer_fmt_t *fmt = NULL;
	unsigned long size = 0UL;
	void *uaddr = NULL;
	void *fmt_arg = NULL;
	int ret = 0;


	
	fmt = pfm_find_buffer_fmt(arg->ctx_smpl_buf_id);
	if (fmt == NULL) {
		DPRINT(("STR", task->pid));
		return -EINVAL;
	}

	
	if (fmt->fmt_arg_size) fmt_arg = PFM_CTXARG_BUF_ARG(arg);

	ret = pfm_buf_fmt_validate(fmt, task, ctx_flags, cpu, fmt_arg);

	DPRINT(("STR", task->pid, ctx_flags, cpu, fmt_arg, ret));

	if (ret) goto error;

	
	ctx->ctx_buf_fmt = fmt;

	
	ret = pfm_buf_fmt_getsize(fmt, task, ctx_flags, cpu, fmt_arg, &size);
	if (ret) goto error;

	if (size) {
		
		ret = pfm_smpl_buffer_alloc(current, ctx, size, &uaddr);
		if (ret) goto error;

		
		arg->ctx_smpl_vaddr = uaddr;
	}
	ret = pfm_buf_fmt_init(fmt, task, ctx->ctx_smpl_hdr, ctx_flags, cpu, fmt_arg);

error:
	return ret;
}