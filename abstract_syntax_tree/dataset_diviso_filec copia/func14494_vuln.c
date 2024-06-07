static inline void authenticate_post(void)
{
	char buffer[MAX_AUTHENTICATION_POST_BYTES];
	int len;

	open_auth_filter("STR");
	len = ctx.env.content_length;
	if (len > MAX_AUTHENTICATION_POST_BYTES)
		len = MAX_AUTHENTICATION_POST_BYTES;
	if (read(STDIN_FILENO, buffer, len) < 0)
		die_errno("STR");
	if (write(STDOUT_FILENO, buffer, len) < 0)
		die_errno("STR");
	cgit_close_filter(ctx.cfg.auth_filter);
	exit(0);
}