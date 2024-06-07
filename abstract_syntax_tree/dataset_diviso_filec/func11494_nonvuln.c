static void pp_init(struct parallel_processes *pp,
		    int n,
		    get_next_task_fn get_next_task,
		    start_failure_fn start_failure,
		    task_finished_fn task_finished,
		    void *data)
{
	int i;

	if (n < 1)
		n = online_cpus();

	pp->max_processes = n;

	trace_printf("STR", n);

	pp->data = data;
	if (!get_next_task)
		die("STR");
	pp->get_next_task = get_next_task;

	pp->start_failure = start_failure ? start_failure : default_start_failure;
	pp->task_finished = task_finished ? task_finished : default_task_finished;

	pp->nr_processes = 0;
	pp->output_owner = 0;
	pp->shutdown = 0;
	pp->children = xcalloc(n, sizeof(*pp->children));
	pp->pfd = xcalloc(n, sizeof(*pp->pfd));
	strbuf_init(&pp->buffered_output, 0);

	for (i = 0; i < n; i++) {
		strbuf_init(&pp->children[i].err, 0);
		child_process_init(&pp->children[i].process);
		pp->pfd[i].events = POLLIN | POLLHUP;
		pp->pfd[i].fd = -1;
	}

	pp_for_signal = pp;
	sigchain_push_common(handle_children_on_signal);
}