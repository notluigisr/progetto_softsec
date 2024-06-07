static __inline__ int scm_send(struct socket *sock, struct msghdr *msg,
			       struct scm_cookie *scm)
{
	scm_set_cred(scm, task_tgid(current), current_cred());
	scm->fp = NULL;
	unix_get_peersec_dgram(sock, scm);
	if (msg->msg_controllen <= 0)
		return 0;
	return __scm_send(sock, msg, scm);
}