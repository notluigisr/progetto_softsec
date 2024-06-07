int ssl_set_peer_cert_type(SESS_CERT *sc,int type)
	{
	sc->peer_cert_type = type;
	return(1);
	}