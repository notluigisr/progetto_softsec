
static int io_register_iowq_aff(struct io_ring_ctx *ctx, void __user *arg,
				unsigned len)
{
	struct io_uring_task *tctx = current->io_uring;
	cpumask_var_t new_mask;
	int ret;

	if (!tctx || !tctx->io_wq)
		return -EINVAL;

	if (!alloc_cpumask_var(&new_mask, GFP_KERNEL))
		return -ENOMEM;

	cpumask_clear(new_mask);
	if (len > cpumask_size())
		len = cpumask_size();

	if (copy_from_user(new_mask, arg, len)) {
		free_cpumask_var(new_mask);
		return -EFAULT;
	}

	ret = io_wq_cpu_affinity(tctx->io_wq, new_mask);
	free_cpumask_var(new_mask);
	return ret;