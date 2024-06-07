static void __rpc_do_wake_up_task(struct rpc_wait_queue *queue, struct rpc_task *task)
{
	dprintk("STR",
			task->tk_pid, jiffies);

	
	if (!RPC_IS_ACTIVATED(task)) {
		printk(KERN_ERR "STR", task);
		return;
	}

	__rpc_remove_wait_queue(queue, task);

	rpc_make_runnable(task);

	dprintk("STR");
}