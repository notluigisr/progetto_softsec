relpTcpVerifyCertificateCallback(gnutls_session_t session)
{
	int r = 0;
	relpTcp_t *pThis;
	const gnutls_datum_t *cert_list;
	unsigned int list_size = 0;
	gnutls_x509_crt_t cert;
	int bMustDeinitCert = 0;

	pThis = (relpTcp_t*) gnutls_session_get_ptr(session);

	
	if(gnutls_certificate_type_get(session) != GNUTLS_CRT_X509) {
		r = GNUTLS_E_CERTIFICATE_ERROR; goto done;
	}

	cert_list = gnutls_certificate_get_peers(pThis->session, &list_size);

	if(list_size < 1) {
		callOnAuthErr(pThis, "STR",
			      RELP_RET_AUTH_NO_CERT);
		r = GNUTLS_E_CERTIFICATE_ERROR; goto done;
	}

	
	gnutls_x509_crt_init(&cert);
	bMustDeinitCert = 1; 
	gnutls_x509_crt_import(cert, &cert_list[0], GNUTLS_X509_FMT_DER);
	if(pThis->authmode == eRelpAuthMode_Fingerprint) {
		r = relpTcpChkPeerFingerprint(pThis, cert);
	} else {
		r = relpTcpChkPeerName(pThis, cert);
	}
	if(r != 0) goto done;

	
	r = 0;

done:
	if(bMustDeinitCert)
		gnutls_x509_crt_deinit(cert);
	return r;
}