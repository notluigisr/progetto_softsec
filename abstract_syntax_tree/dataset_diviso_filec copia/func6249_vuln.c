R_API int r_socket_read(RSocket *s, unsigned char *buf, int len) {
	if (!s) {
		return -1;
	}
#if HAVE_LIB_SSL
	if (s->is_ssl) {
		if (s->bio) {
			return BIO_read (s->bio, buf, len);
		}
		return SSL_read (s->sfd, buf, len);
	}
#endif
#if __WINDOWS__
rep:
	{
	int ret = recv (s->fd, (void *)buf, len, 0);
	if (ret == -1) {
		goto rep;
	}
	return ret;
	}
#else
	
	int r = recv (s->fd, buf, len, 0);
	D { eprintf ("STR"); }
	return r;
#endif
}