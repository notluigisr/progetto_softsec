static void raw_sock_seq_show(struct seq_file *seq, struct sock *sp, int i)
{
	struct inet_sock *inet = inet_sk(sp);
	__be32 dest = inet->inet_daddr,
	       src = inet->inet_rcv_saddr;
	__u16 destp = 0,
	      srcp  = inet->inet_num;

	seq_printf(seq, "STR"
		"STR",
		i, src, srcp, dest, destp, sp->sk_state,
		sk_wmem_alloc_get(sp),
		sk_rmem_alloc_get(sp),
		0, 0L, 0, sock_i_uid(sp), 0, sock_i_ino(sp),
		atomic_read(&sp->sk_refcnt), sp, atomic_read(&sp->sk_drops));
}