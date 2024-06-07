vrrp_shutdown_backstop_thread(thread_t *thread)
{
	int count = 0;
	thread_t *t;

	
	if (thread->master->child.rb_root.rb_node)
		script_killall(thread->master, SIGKILL, true);

	rb_for_each_entry_cached(t, &thread->master->child, n)
		count++;

	log_message(LOG_ERR, "STR",
			thread->master->shutdown_timer_running ? "STR", count);

	thread_add_terminate_event(thread->master);

	return 0;
}