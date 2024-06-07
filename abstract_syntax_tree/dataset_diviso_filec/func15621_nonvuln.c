static int link_opipe_prep(struct pipe_inode_info *pipe, unsigned int flags)
{
	int ret;

	
	if (pipe->nrbufs < PIPE_BUFFERS)
		return 0;

	ret = 0;
	mutex_lock(&pipe->inode->i_mutex);

	while (pipe->nrbufs >= PIPE_BUFFERS) {
		if (!pipe->readers) {
			send_sig(SIGPIPE, current, 0);
			ret = -EPIPE;
			break;
		}
		if (flags & SPLICE_F_NONBLOCK) {
			ret = -EAGAIN;
			break;
		}
		if (signal_pending(current)) {
			ret = -ERESTARTSYS;
			break;
		}
		pipe->waiting_writers++;
		pipe_wait(pipe);
		pipe->waiting_writers--;
	}

	mutex_unlock(&pipe->inode->i_mutex);
	return ret;
}