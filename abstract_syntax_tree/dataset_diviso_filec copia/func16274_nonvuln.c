static int io_uring_flush(struct file *file, void *data)
{
	struct io_ring_ctx *ctx = file->private_data;

	io_uring_cancel_files(ctx, data);
	if (fatal_signal_pending(current) || (current->flags & PF_EXITING)) {
		io_cqring_overflow_flush(ctx, true);
		io_wq_cancel_all(ctx->io_wq);
	}
	return 0;
}