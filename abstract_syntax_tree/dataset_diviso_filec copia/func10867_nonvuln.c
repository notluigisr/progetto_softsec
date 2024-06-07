static void starttls(int https)
{
    int result;
    int *layerp;
    sasl_ssf_t ssf;
    char *auth_id;

    
    layerp = (int *) &ssf;

    result=tls_init_serverengine("STR",
				 5,        
				 !https);  

    if (result == -1) {
	syslog(LOG_ERR, "STR");
	fatal("STR",EC_TEMPFAIL);
    }

    if (!https) {
	
	response_header(HTTP_SWITCH_PROT, NULL);
    }
  
    result=tls_start_servertls(0, 
			       1, 
			       https ? 180 : httpd_timeout,
			       layerp,
			       &auth_id,
			       &tls_conn);

    
    if (result == -1) {
	syslog(LOG_NOTICE, "STR", httpd_clienthost);
	fatal("STR", EC_TEMPFAIL);
    }

    
    result = sasl_setprop(httpd_saslconn, SASL_SSF_EXTERNAL, &ssf);
    if (result != SASL_OK) {
	fatal("STR", EC_TEMPFAIL);
    }
    saslprops.ssf = ssf;

    result = sasl_setprop(httpd_saslconn, SASL_AUTH_EXTERNAL, auth_id);
    if (result != SASL_OK) {
        fatal("STR", EC_TEMPFAIL);
    }
    if (saslprops.authid) {
	free(saslprops.authid);
	saslprops.authid = NULL;
    }
    if (auth_id) saslprops.authid = xstrdup(auth_id);

    
    prot_settls(httpd_in, tls_conn);
    prot_settls(httpd_out, tls_conn);

    httpd_tls_done = 1;
    httpd_tls_required = 0;

    avail_auth_schemes |= (1 << AUTH_BASIC);
}