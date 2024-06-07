static void nlmclnt_unlock_callback(struct rpc_task *task, void *data)
{
	struct nlm_rqst	*req = data;
	u32 status = ntohl(req->a_res.status);

	if (RPC_ASSASSINATED(task))
		goto die;

	if (task->tk_status < 0) {
		dprintk("STR", -task->tk_status);
		goto retry_rebind;
	}
	if (status == NLM_LCK_DENIED_GRACE_PERIOD) {
		rpc_delay(task, NLMCLNT_GRACE_WAIT);
		goto retry_unlock;
	}
	if (status != NLM_LCK_GRANTED)
		printk(KERN_WARNING "STR", status);
die:
	return;
 retry_rebind:
	nlm_rebind_host(req->a_host);
 retry_unlock:
	rpc_restart_call(task);
}