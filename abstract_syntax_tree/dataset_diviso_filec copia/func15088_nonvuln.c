int X509_check_email(X509 *x, const unsigned char *chk, size_t chklen,
					unsigned int flags)
	{
	return do_x509_check(x, chk, chklen, flags, GEN_EMAIL);
	}