int nfs41_setup_sequence(struct nfs4_session *session,
				struct nfs4_sequence_args *args,
				struct nfs4_sequence_res *res,
				int cache_reply,
				struct rpc_task *task)
{
	struct nfs4_slot *slot;
	struct nfs4_slot_table *tbl;
	u8 slotid;

	dprintk("STR", __func__);
	
	if (res->sr_slot != NULL)
		return 0;

	tbl = &session->fc_slot_table;

	spin_lock(&tbl->slot_tbl_lock);
	if (test_bit(NFS4_SESSION_DRAINING, &session->session_state) &&
	    !rpc_task_has_priority(task, RPC_PRIORITY_PRIVILEGED)) {
		
		rpc_sleep_on(&tbl->slot_tbl_waitq, task, NULL);
		spin_unlock(&tbl->slot_tbl_lock);
		dprintk("STR", __func__);
		return -EAGAIN;
	}

	if (!rpc_queue_empty(&tbl->slot_tbl_waitq) &&
	    !rpc_task_has_priority(task, RPC_PRIORITY_PRIVILEGED)) {
		rpc_sleep_on(&tbl->slot_tbl_waitq, task, NULL);
		spin_unlock(&tbl->slot_tbl_lock);
		dprintk("STR", __func__);
		return -EAGAIN;
	}

	slotid = nfs4_find_slot(tbl);
	if (slotid == NFS4_MAX_SLOT_TABLE) {
		rpc_sleep_on(&tbl->slot_tbl_waitq, task, NULL);
		spin_unlock(&tbl->slot_tbl_lock);
		dprintk("STR", __func__);
		return -EAGAIN;
	}
	spin_unlock(&tbl->slot_tbl_lock);

	rpc_task_set_priority(task, RPC_PRIORITY_NORMAL);
	slot = tbl->slots + slotid;
	args->sa_session = session;
	args->sa_slotid = slotid;
	args->sa_cache_this = cache_reply;

	dprintk("STR", __func__, slotid, slot->seq_nr);

	res->sr_session = session;
	res->sr_slot = slot;
	res->sr_renewal_time = jiffies;
	res->sr_status_flags = 0;
	
	res->sr_status = 1;
	return 0;
}