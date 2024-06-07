static char *smack_of_msq(struct msg_queue *msq)
{
	return (char *)msq->q_perm.security;
}