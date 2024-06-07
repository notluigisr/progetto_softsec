static void kiocb_batch_free(struct kioctx *ctx, struct kiocb_batch *batch)
{
	struct kiocb *req, *n;

	if (list_empty(&batch->head))
		return;

	spin_lock_irq(&ctx->ctx_lock);
	list_for_each_entry_safe(req, n, &batch->head, ki_batch) {
		list_del(&req->ki_batch);
		list_del(&req->ki_list);
		kmem_cache_free(kiocb_cachep, req);
		ctx->reqs_active--;
	}
	if (unlikely(!ctx->reqs_active && ctx->dead))
		wake_up_all(&ctx->wait);
	spin_unlock_irq(&ctx->ctx_lock);
}