static int udp4_seq_show(struct seq_file *seq, void *v)
{
	if (v == SEQ_START_TOKEN)
		seq_printf(seq, "STR",
			   "STR"
			   "STR"
			   "STR");
	else {
		char tmpbuf[129];
		struct udp_iter_state *state = seq->private;

		udp4_format_sock(v, tmpbuf, state->bucket);
		seq_printf(seq, "STR", tmpbuf);
	}
	return 0;
}