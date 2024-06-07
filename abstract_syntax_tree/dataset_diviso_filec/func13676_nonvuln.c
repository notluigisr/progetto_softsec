static int smack_sem_alloc_security(struct sem_array *sma)
{
	struct kern_ipc_perm *isp = &sma->sem_perm;

	isp->security = current_security();
	return 0;
}