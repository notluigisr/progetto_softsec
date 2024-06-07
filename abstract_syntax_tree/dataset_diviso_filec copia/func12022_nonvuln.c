void ping_close(struct sock *sk, long timeout)
{
	pr_debug("STR",
		 inet_sk(sk), inet_sk(sk)->inet_num);
	pr_debug("STR", sk->sk_refcnt.counter);

	sk_common_release(sk);
}