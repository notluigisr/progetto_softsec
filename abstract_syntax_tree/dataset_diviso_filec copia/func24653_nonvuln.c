static int fetch_start_failure(struct strbuf *err,
			       void *cb, void *task_cb)
{
	struct submodule_parallel_fetch *spf = cb;

	spf->result = 1;

	return 0;
}