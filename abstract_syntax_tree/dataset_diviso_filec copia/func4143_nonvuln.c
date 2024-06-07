relpTcpTLSSetPrio(relpTcp_t *pThis)
{
	int r;
	char pristringBuf[4096];
	char *pristring;
	ENTER_RELPFUNC;
	
	if(pThis->pristring == NULL) {
		if(pThis->bEnableTLSZip) {
			strncpy(pristringBuf, "STR", sizeof(pristringBuf));
		} else {
			strncpy(pristringBuf, "STR", sizeof(pristringBuf));
		}
		pristringBuf[sizeof(pristringBuf)-1] = '\0';
		pristring = pristringBuf;
	} else {
		pristring = pThis->pristring;
	}

	r = gnutls_priority_set_direct(pThis->session, pristring, NULL);
	if(r == GNUTLS_E_INVALID_REQUEST) {
		ABORT_FINALIZE(RELP_RET_INVLD_TLS_PRIO);
	} else if(r != GNUTLS_E_SUCCESS) {
		ABORT_FINALIZE(RELP_RET_ERR_TLS_SETUP);
	}
finalize_it:
	if(iRet != RELP_RET_OK)
		chkGnutlsCode(pThis, "STR", iRet, r);
	LEAVE_RELPFUNC;
}