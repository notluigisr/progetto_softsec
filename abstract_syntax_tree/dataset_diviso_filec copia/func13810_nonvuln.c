void kgdb_unregister_io_module(struct kgdb_io *old_dbg_io_ops)
{
	BUG_ON(kgdb_connected);

	
	kgdb_unregister_callbacks();

	spin_lock(&kgdb_registration_lock);

	WARN_ON_ONCE(dbg_io_ops != old_dbg_io_ops);
	dbg_io_ops = NULL;

	spin_unlock(&kgdb_registration_lock);

	if (old_dbg_io_ops->deinit)
		old_dbg_io_ops->deinit();

	pr_info("STR",
		old_dbg_io_ops->name);
}