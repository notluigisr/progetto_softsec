int compat_ip_getsockopt(struct sock *sk, int level, int optname,
			 char __user *optval, int __user *optlen)
{
	int err;

	if (optname == MCAST_MSFILTER)
		return compat_mc_getsockopt(sk, level, optname, optval, optlen,
			ip_getsockopt);

	err = do_ip_getsockopt(sk, level, optname, optval, optlen);

#ifdef CONFIG_NETFILTER
	
	if (err == -ENOPROTOOPT && optname != IP_PKTOPTIONS &&
			!ip_mroute_opt(optname)) {
		int len;

		if (get_user(len, optlen))
			return -EFAULT;

		lock_sock(sk);
		err = compat_nf_getsockopt(sk, PF_INET, optname, optval, &len);
		release_sock(sk);
		if (err >= 0)
			err = put_user(len, optlen);
		return err;
	}
#endif
	return err;
}