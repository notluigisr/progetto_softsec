static int packet_seq_show(struct seq_file *seq, void *v)
{
	if (v == SEQ_START_TOKEN)
		seq_puts(seq, "STR");
	else {
		struct sock *s = sk_entry(v);
		const struct packet_sock *po = pkt_sk(s);

		seq_printf(seq,
			   "STR",
			   s,
			   atomic_read(&s->sk_refcnt),
			   s->sk_type,
			   ntohs(po->num),
			   po->ifindex,
			   po->running,
			   atomic_read(&s->sk_rmem_alloc),
			   from_kuid_munged(seq_user_ns(seq), sock_i_uid(s)),
			   sock_i_ino(s));
	}

	return 0;
}