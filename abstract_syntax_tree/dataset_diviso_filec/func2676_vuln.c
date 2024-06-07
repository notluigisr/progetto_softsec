int ip_ra_control(struct sock *sk, unsigned char on,
		  void (*destructor)(struct sock *))
{
	struct ip_ra_chain *ra, *new_ra;
	struct ip_ra_chain __rcu **rap;
	struct net *net = sock_net(sk);

	if (sk->sk_type != SOCK_RAW || inet_sk(sk)->inet_num == IPPROTO_RAW)
		return -EINVAL;

	new_ra = on ? kmalloc(sizeof(*new_ra), GFP_KERNEL) : NULL;

	mutex_lock(&net->ipv4.ra_mutex);
	for (rap = &net->ipv4.ra_chain;
	     (ra = rcu_dereference_protected(*rap,
			lockdep_is_held(&net->ipv4.ra_mutex))) != NULL;
	     rap = &ra->next) {
		if (ra->sk == sk) {
			if (on) {
				mutex_unlock(&net->ipv4.ra_mutex);
				kfree(new_ra);
				return -EADDRINUSE;
			}
			
			ra->sk = NULL;
			RCU_INIT_POINTER(*rap, ra->next);
			mutex_unlock(&net->ipv4.ra_mutex);

			if (ra->destructor)
				ra->destructor(sk);
			
			ra->saved_sk = sk;
			call_rcu(&ra->rcu, ip_ra_destroy_rcu);
			return 0;
		}
	}
	if (!new_ra) {
		mutex_unlock(&net->ipv4.ra_mutex);
		return -ENOBUFS;
	}
	new_ra->sk = sk;
	new_ra->destructor = destructor;

	RCU_INIT_POINTER(new_ra->next, ra);
	rcu_assign_pointer(*rap, new_ra);
	sock_hold(sk);
	mutex_unlock(&net->ipv4.ra_mutex);

	return 0;
}