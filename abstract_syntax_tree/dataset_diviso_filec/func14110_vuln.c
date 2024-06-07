static struct sock * unix_create1(struct socket *sock)
{
	struct sock *sk = NULL;
	struct unix_sock *u;

	if (atomic_read(&unix_nr_socks) >= 2*get_max_files())
		goto out;

	sk = sk_alloc(PF_UNIX, GFP_KERNEL, &unix_proto, 1);
	if (!sk)
		goto out;

	atomic_inc(&unix_nr_socks);

	sock_init_data(sock,sk);
	lockdep_set_class(&sk->sk_receive_queue.lock,
				&af_unix_sk_receive_queue_lock_key);

	sk->sk_write_space	= unix_write_space;
	sk->sk_max_ack_backlog	= sysctl_unix_max_dgram_qlen;
	sk->sk_destruct		= unix_sock_destructor;
	u	  = unix_sk(sk);
	u->dentry = NULL;
	u->mnt	  = NULL;
	spin_lock_init(&u->lock);
	atomic_set(&u->inflight, sock ? 0 : -1);
	mutex_init(&u->readlock); 
	init_waitqueue_head(&u->peer_wait);
	unix_insert_socket(unix_sockets_unbound, sk);
out:
	return sk;
}