
static int io_sq_offload_create(struct io_ring_ctx *ctx,
				struct io_uring_params *p)
{
	int ret;

	
	if ((ctx->flags & (IORING_SETUP_ATTACH_WQ | IORING_SETUP_SQPOLL)) ==
				IORING_SETUP_ATTACH_WQ) {
		struct fd f;

		f = fdget(p->wq_fd);
		if (!f.file)
			return -ENXIO;
		if (f.file->f_op != &io_uring_fops) {
			fdput(f);
			return -EINVAL;
		}
		fdput(f);
	}
	if (ctx->flags & IORING_SETUP_SQPOLL) {
		struct io_sq_data *sqd;

		ret = -EPERM;
		if (!capable(CAP_SYS_ADMIN) && !capable(CAP_SYS_NICE))
			goto err;

		sqd = io_get_sq_data(p);
		if (IS_ERR(sqd)) {
			ret = PTR_ERR(sqd);
			goto err;
		}

		ctx->sq_data = sqd;
		io_sq_thread_park(sqd);
		mutex_lock(&sqd->ctx_lock);
		list_add(&ctx->sqd_list, &sqd->ctx_new_list);
		mutex_unlock(&sqd->ctx_lock);
		io_sq_thread_unpark(sqd);

		ctx->sq_thread_idle = msecs_to_jiffies(p->sq_thread_idle);
		if (!ctx->sq_thread_idle)
			ctx->sq_thread_idle = HZ;

		if (sqd->thread)
			return 0;

		if (p->flags & IORING_SETUP_SQ_AFF) {
			int cpu = p->sq_thread_cpu;

			ret = -EINVAL;
			if (cpu >= nr_cpu_ids)
				goto err;
			if (!cpu_online(cpu))
				goto err;

			sqd->sq_cpu = cpu;
		} else {
			sqd->sq_cpu = -1;
		}

		sqd->task_pid = current->pid;
		current->flags |= PF_IO_WORKER;
		ret = io_wq_fork_thread(io_sq_thread, sqd);
		current->flags &= ~PF_IO_WORKER;
		if (ret < 0) {
			sqd->thread = NULL;
			goto err;
		}
		wait_for_completion(&sqd->completion);
		ret = io_uring_alloc_task_context(sqd->thread, ctx);
		if (ret)
			goto err;
	} else if (p->flags & IORING_SETUP_SQ_AFF) {
		
		ret = -EINVAL;
		goto err;
	}

	return 0;
err:
	io_sq_thread_finish(ctx);
	return ret;