n_tty_receive_char_fast(struct tty_struct *tty, unsigned char c)
{
	struct n_tty_data *ldata = tty->disc_data;

	if (tty->stopped && !tty->flow_stopped && I_IXON(tty) && I_IXANY(tty)) {
		start_tty(tty);
		process_echoes(tty);
	}
	if (L_ECHO(tty)) {
		finish_erasing(ldata);
		
		if (ldata->canon_head == ldata->read_head)
			echo_set_canon_col(ldata);
		echo_char(c, tty);
		commit_echoes(tty);
	}
	put_tty_queue(c, ldata);
}