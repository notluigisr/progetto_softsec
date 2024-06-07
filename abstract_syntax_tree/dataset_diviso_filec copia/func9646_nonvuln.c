static void nfs_access_free_entry(struct nfs_access_entry *entry)
{
	put_rpccred(entry->cred);
	kfree(entry);
	smp_mb__before_atomic_dec();
	atomic_long_dec(&nfs_access_nr_entries);
	smp_mb__after_atomic_dec();
}