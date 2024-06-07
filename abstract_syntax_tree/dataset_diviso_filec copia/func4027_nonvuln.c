static void __sctp_write_space(struct sctp_association *asoc)
{
	struct sock *sk = asoc->base.sk;
	struct socket *sock = sk->sk_socket;

	if ((sctp_wspace(asoc) > 0) && sock) {
		if (waitqueue_active(&asoc->wait))
			wake_up_interruptible(&asoc->wait);

		if (sctp_writeable(sk)) {
			if (sk_sleep(sk) && waitqueue_active(sk_sleep(sk)))
				wake_up_interruptible(sk_sleep(sk));

			
			if (sock->fasync_list &&
			    !(sk->sk_shutdown & SEND_SHUTDOWN))
				sock_wake_async(sock,
						SOCK_WAKE_SPACE, POLL_OUT);
		}
	}
}