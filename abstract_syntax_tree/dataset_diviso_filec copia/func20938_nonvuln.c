static RETSIGTYPE sigusr2_handler(UNUSED(int val))
{
	if (!am_server)
		output_summary();
	close_all();
	if (got_xfer_error)
		_exit(RERR_PARTIAL);
	_exit(0);
}