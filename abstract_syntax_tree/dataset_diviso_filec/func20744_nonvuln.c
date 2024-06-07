int security_tun_dev_attach(struct sock *sk)
{
	return security_ops->tun_dev_attach(sk);
}