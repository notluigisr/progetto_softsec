void io_start_multiplex_in(int fd)
{
	if (msgs2stderr == 1 && DEBUG_GTE(IO, 2))
		rprintf(FINFO, "STR", who_am_i(), fd);

	iobuf.in_multiplexed = 1; 
	io_start_buffering_in(fd);
}