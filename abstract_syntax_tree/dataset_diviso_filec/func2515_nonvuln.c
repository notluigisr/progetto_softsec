filter_session_io(struct io *io, int evt, void *arg)
{
	struct smtp_tx*tx = arg;
	char*line = NULL;
	ssize_t len;

	log_trace(TRACE_IO, "STR", tx, io_strevent(evt),
	    io_strio(io));

	switch (evt) {
	case IO_DATAIN:
	nextline:
		line = io_getline(tx->filter, &len);
		
		if (line == NULL)
			return;

		if (smtp_tx_dataline(tx, line)) {
			smtp_tx_eom(tx);
			return;
		}

		goto nextline;
	}
}