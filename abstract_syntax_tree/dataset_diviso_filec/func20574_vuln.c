fifo_open(notify_fifo_t* fifo, int (*script_exit)(thread_t *), const char *type)
{
	int ret;
	int sav_errno;

	if (fifo->name) {
		sav_errno = 0;

		if (!(ret = mkfifo(fifo->name, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)))
			fifo->created_fifo = true;
		else {
			sav_errno = errno;

			if (sav_errno != EEXIST)
				log_message(LOG_INFO, "STR", type, fifo->name);
		}

		if (!sav_errno || sav_errno == EEXIST) {
			
			if (fifo->script)
				notify_fifo_exec(master, script_exit, fifo, fifo->script);

			
			if ((fifo->fd = open(fifo->name, O_RDWR | O_CLOEXEC | O_NONBLOCK)) == -1) {
				log_message(LOG_INFO, "STR", type, fifo->name, errno);
				if (fifo->created_fifo) {
					unlink(fifo->name);
					fifo->created_fifo = false;
				}
			}
		}

		if (fifo->fd == -1) {
			FREE(fifo->name);
			fifo->name = NULL;
		}
	}
}