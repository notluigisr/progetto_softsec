mono_gc_cleanup (void)
{
#ifdef DEBUG
	g_message ("STR", __func__);
#endif

	if (!gc_disabled) {
		ResetEvent (shutdown_event);
		finished = TRUE;
		if (mono_thread_internal_current () != gc_thread) {
			mono_gc_finalize_notify ();
			
			
			if (WaitForSingleObjectEx (shutdown_event, 2000, FALSE) == WAIT_TIMEOUT) {
				int ret;

				
				suspend_finalizers = TRUE;

				
				mono_thread_internal_stop (gc_thread);

				
				ret = WaitForSingleObjectEx (gc_thread->handle, 100, TRUE);

				if (ret == WAIT_TIMEOUT) {
					
					g_warning ("STR");
				} else {
					
					Sleep (100);
				}

			}
		}
		gc_thread = NULL;
#ifdef HAVE_BOEHM_GC
		GC_finalizer_notifier = NULL;
#endif
	}

	DeleteCriticalSection (&handle_section);
	DeleteCriticalSection (&allocator_section);
	DeleteCriticalSection (&finalizer_mutex);
}