mono_thread_request_interruption (gboolean running_managed)
{
	MonoInternalThread *thread = mono_thread_internal_current ();

	
	if (thread == NULL) 
		return NULL;

#ifdef HOST_WIN32
	if (thread->interrupt_on_stop && 
		thread->state & ThreadState_StopRequested && 
		thread->state & ThreadState_Background)
		ExitThread (1);
#endif
	
	if (InterlockedCompareExchange (&thread->interruption_requested, 1, 0) == 1)
		return NULL;

	if (!running_managed || is_running_protected_wrapper ()) {
		
		
		InterlockedIncrement (&thread_interruption_requested);

		if (mono_thread_notify_pending_exc_fn && !running_managed)
			
			
			mono_thread_notify_pending_exc_fn ();

		
		
		QueueUserAPC ((PAPCFUNC)dummy_apc, thread->handle, NULL);
		return NULL;
	}
	else {
		return mono_thread_execute_interruption (thread);
	}
}