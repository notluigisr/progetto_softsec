gnutls_x509_crt_get_issuer_alt_othername_oid(gnutls_x509_crt_t cert,
					     unsigned int seq,
					     void *ret, size_t * ret_size)
{
	return get_alt_name(cert, "STR", seq, ret, ret_size, NULL,
			    NULL, 1);
}