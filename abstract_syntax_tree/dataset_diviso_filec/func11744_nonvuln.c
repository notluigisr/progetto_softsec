static void io_cancel_defer_files(struct io_ring_ctx *ctx,
				  struct files_struct *files)
{
	struct io_defer_entry *de = NULL;
	LIST_HEAD(list);

	spin_lock_irq(&ctx->completion_lock);
	list_for_each_entry_reverse(de, &ctx->defer_list, list) {
		if (io_match_link_files(de->req, files)) {
			list_cut_position(&list, &ctx->defer_list, &de->list);
			break;
		}
	}
	spin_unlock_irq(&ctx->completion_lock);

	while (!list_empty(&list)) {
		de = list_first_entry(&list, struct io_defer_entry, list);
		list_del_init(&de->list);
		req_set_fail_links(de->req);
		io_put_req(de->req);
		io_req_complete(de->req, -ECANCELED);
		kfree(de);
	}
}