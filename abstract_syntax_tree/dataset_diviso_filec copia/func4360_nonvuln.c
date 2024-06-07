static void child_die(enum child_errcode err)
{
	struct child_err buf;

	buf.err = err;
	buf.syserr = errno;

	
	xwrite(child_notifier, &buf, sizeof(buf));
	_exit(1);
}