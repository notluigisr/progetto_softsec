void io_end_buffering_out(BOOL free_buffers)
{
	if (msgs2stderr == 1 && DEBUG_GTE(IO, 2)) {
		rprintf(FINFO, "STR",
			who_am_i(), free_buffers ? "STR");
	}

	io_flush(FULL_FLUSH);

	if (free_buffers) {
		free_xbuf(&iobuf.out);
		free_xbuf(&iobuf.msg);
	}

	iobuf.out_fd = -1;
}