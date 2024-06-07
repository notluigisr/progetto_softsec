int nfs40_walk_client_list(struct nfs_client *new,
			   struct nfs_client **result,
			   const struct cred *cred)
{
	struct nfs_net *nn = net_generic(new->cl_net, nfs_net_id);
	struct nfs_client *pos, *prev = NULL;
	struct nfs4_setclientid_res clid = {
		.clientid	= new->cl_clientid,
		.confirm	= new->cl_confirm,
	};
	int status = -NFS4ERR_STALE_CLIENTID;

	spin_lock(&nn->nfs_client_lock);
	list_for_each_entry(pos, &nn->nfs_client_list, cl_share_link) {

		if (pos == new)
			goto found;

		status = nfs4_match_client(pos, new, &prev, nn);
		if (status < 0)
			goto out_unlock;
		if (status != 0)
			continue;
		
		if ((new != pos) && nfs4_same_verifier(&pos->cl_confirm,
						       &new->cl_confirm))
			continue;
		
found:
		refcount_inc(&pos->cl_count);
		spin_unlock(&nn->nfs_client_lock);

		nfs_put_client(prev);
		prev = pos;

		status = nfs4_proc_setclientid_confirm(pos, &clid, cred);
		switch (status) {
		case -NFS4ERR_STALE_CLIENTID:
			break;
		case 0:
			nfs4_swap_callback_idents(pos, new);
			pos->cl_confirm = new->cl_confirm;
			nfs_mark_client_ready(pos, NFS_CS_READY);

			prev = NULL;
			*result = pos;
			goto out;
		case -ERESTARTSYS:
		case -ETIMEDOUT:
			
			nfs4_schedule_path_down_recovery(pos);
			goto out;
		default:
			goto out;
		}

		spin_lock(&nn->nfs_client_lock);
	}
out_unlock:
	spin_unlock(&nn->nfs_client_lock);

	
out:
	nfs_put_client(prev);
	return status;
}