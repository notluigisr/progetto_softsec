void __cleanup_sighand(struct sighand_struct *sighand)
{
	if (refcount_dec_and_test(&sighand->count)) {
		signalfd_cleanup(sighand);
		
		kmem_cache_free(sighand_cachep, sighand);
	}
}