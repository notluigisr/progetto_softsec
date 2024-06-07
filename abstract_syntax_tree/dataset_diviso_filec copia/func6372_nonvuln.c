collect_appdomain_thread (gpointer key, gpointer value, gpointer user_data)
{
	MonoInternalThread *thread = (MonoInternalThread*)value;
	abort_appdomain_data *data = (abort_appdomain_data*)user_data;
	MonoDomain *domain = data->domain;

	if (mono_thread_internal_has_appdomain_ref (thread, domain)) {
		

		if(data->wait.num<MAXIMUM_WAIT_OBJECTS) {
			HANDLE handle = OpenThread (THREAD_ALL_ACCESS, TRUE, thread->tid);
			if (handle == NULL)
				return;
			data->wait.handles [data->wait.num] = handle;
			data->wait.threads [data->wait.num] = thread;
			data->wait.num++;
		} else {
			
		}
	}
}