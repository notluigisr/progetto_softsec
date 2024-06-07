mono_gc_finalize_threadpool_threads (void)
{
	while (threads_to_finalize) {
		MonoInternalThread *thread = (MonoInternalThread*) mono_mlist_get_data (threads_to_finalize);

		
		thread->threadpool_thread = FALSE;
		mono_object_register_finalizer ((MonoObject*)thread);

		mono_gc_run_finalize (thread, NULL);

		threads_to_finalize = mono_mlist_next (threads_to_finalize);
	}
}