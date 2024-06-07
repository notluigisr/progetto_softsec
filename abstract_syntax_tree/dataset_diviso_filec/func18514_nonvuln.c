static struct sock *sctp_accept(struct sock *sk, int flags, int *err, bool kern)
{
	struct sctp_sock *sp;
	struct sctp_endpoint *ep;
	struct sock *newsk = NULL;
	struct sctp_association *asoc;
	long timeo;
	int error = 0;

	lock_sock(sk);

	sp = sctp_sk(sk);
	ep = sp->ep;

	if (!sctp_style(sk, TCP)) {
		error = -EOPNOTSUPP;
		goto out;
	}

	if (!sctp_sstate(sk, LISTENING)) {
		error = -EINVAL;
		goto out;
	}

	timeo = sock_rcvtimeo(sk, flags & O_NONBLOCK);

	error = sctp_wait_for_accept(sk, timeo);
	if (error)
		goto out;

	
	asoc = list_entry(ep->asocs.next, struct sctp_association, asocs);

	newsk = sp->pf->create_accept_sk(sk, asoc, kern);
	if (!newsk) {
		error = -ENOMEM;
		goto out;
	}

	
	error = sctp_sock_migrate(sk, newsk, asoc, SCTP_SOCKET_TCP);
	if (error) {
		sk_common_release(newsk);
		newsk = NULL;
	}

out:
	release_sock(sk);
	*err = error;
	return newsk;
}