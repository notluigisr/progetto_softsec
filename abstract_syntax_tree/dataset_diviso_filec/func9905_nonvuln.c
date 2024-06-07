static inline struct ax25_cb *sk_to_ax25(const struct sock *sk)
{
	return ax25_sk(sk)->cb;
}