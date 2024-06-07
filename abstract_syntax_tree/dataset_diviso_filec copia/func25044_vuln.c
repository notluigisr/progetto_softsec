call_bind_status(struct rpc_task *task)
{
	int status = -EIO;

	if (task->tk_status >= 0) {
		dprint_status(task);
		task->tk_status = 0;
		task->tk_action = call_connect;
		return;
	}

	switch (task->tk_status) {
	case -ENOMEM:
		dprintk("STR", task->tk_pid);
		rpc_delay(task, HZ >> 2);
		goto retry_timeout;
	case -EACCES:
		dprintk("STR"
				"STR", task->tk_pid);
		
		if (task->tk_msg.rpc_proc->p_proc == 0) {
			status = -EOPNOTSUPP;
			break;
		}
		rpc_delay(task, 3*HZ);
		goto retry_timeout;
	case -ETIMEDOUT:
		dprintk("STR",
				task->tk_pid);
		goto retry_timeout;
	case -EPFNOSUPPORT:
		
		dprintk("STR",
				task->tk_pid);
		break;
	case -EPROTONOSUPPORT:
		dprintk("STR",
				task->tk_pid);
		task->tk_status = 0;
		task->tk_action = call_bind;
		return;
	case -ECONNREFUSED:		
	case -ECONNRESET:
	case -ENOTCONN:
	case -EHOSTDOWN:
	case -EHOSTUNREACH:
	case -ENETUNREACH:
	case -EPIPE:
		dprintk("STR",
				task->tk_pid, task->tk_status);
		if (!RPC_IS_SOFTCONN(task)) {
			rpc_delay(task, 5*HZ);
			goto retry_timeout;
		}
		status = task->tk_status;
		break;
	default:
		dprintk("STR",
				task->tk_pid, -task->tk_status);
	}

	rpc_exit(task, status);
	return;

retry_timeout:
	task->tk_action = call_timeout;
}