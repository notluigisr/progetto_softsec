void hfi1_mmu_rb_unregister(struct mmu_rb_handler *handler)
{
	struct mmu_rb_node *rbnode;
	struct rb_node *node;
	unsigned long flags;
	struct list_head del_list;

	
	mmu_notifier_unregister(&handler->mn, handler->mm);

	
	flush_work(&handler->del_work);

	INIT_LIST_HEAD(&del_list);

	spin_lock_irqsave(&handler->lock, flags);
	while ((node = rb_first_cached(&handler->root))) {
		rbnode = rb_entry(node, struct mmu_rb_node, node);
		rb_erase_cached(node, &handler->root);
		
		list_move(&rbnode->list, &del_list);
	}
	spin_unlock_irqrestore(&handler->lock, flags);

	do_remove(handler, &del_list);

	kfree(handler);
}