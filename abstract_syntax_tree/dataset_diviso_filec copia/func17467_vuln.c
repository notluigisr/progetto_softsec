finalizer_thread (gpointer unused)
{
	while (!finished) {
		

		g_assert (mono_domain_get () == mono_get_root_domain ());

#ifdef MONO_HAS_SEMAPHORES
		MONO_SEM_WAIT (&finalizer_sem);
#else
		
		WaitForSingleObjectEx (finalizer_event, INFINITE, FALSE);
#endif

		mono_console_handle_async_ops ();

#ifndef DISABLE_ATTACH
		mono_attach_maybe_start ();
#endif

		if (domains_to_finalize) {
			mono_finalizer_lock ();
			if (domains_to_finalize) {
				DomainFinalizationReq *req = domains_to_finalize->data;
				domains_to_finalize = g_slist_remove (domains_to_finalize, req);
				mono_finalizer_unlock ();

				finalize_domain_objects (req);
			} else {
				mono_finalizer_unlock ();
			}
		}				

		
		mono_gc_invoke_finalizers ();

		SetEvent (pending_done_event);
	}

	SetEvent (shutdown_event);
	return 0;
}