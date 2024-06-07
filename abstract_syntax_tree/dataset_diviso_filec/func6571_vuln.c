relpTcpChkPeerName(relpTcp_t *pThis, gnutls_x509_crt_t cert)
{
	int r = 0;
	int ret;
	unsigned int status = 0;
	char cnBuf[1024]; 
	char szAltName[1024]; 
	int iAltName;
	char allNames[32*1024]; 
	int iAllNames;
	size_t szAltNameLen;
	int bFoundPositiveMatch;
	int gnuRet;

	ret = gnutls_certificate_verify_peers2(pThis->session, &status);
	if(ret < 0) {
		callOnAuthErr(pThis, "STR",
			RELP_RET_AUTH_CERT_INVL);
		r = GNUTLS_E_CERTIFICATE_ERROR; goto done;
	}
	if(status != 0) { 
		callOnAuthErr(pThis, "STR",
			RELP_RET_AUTH_CERT_INVL);
		r = GNUTLS_E_CERTIFICATE_ERROR; goto done;
	}

	bFoundPositiveMatch = 0;
	iAllNames = 0;

	
	iAltName = 0;
	while(!bFoundPositiveMatch) { 
		szAltNameLen = sizeof(szAltName);
		gnuRet = gnutls_x509_crt_get_subject_alt_name(cert, iAltName,
				szAltName, &szAltNameLen, NULL);
		if(gnuRet < 0)
			break;
		else if(gnuRet == GNUTLS_SAN_DNSNAME) {
			pThis->pEngine->dbgprint("STR", szAltName);
			iAllNames += snprintf(allNames+iAllNames, sizeof(allNames)-iAllNames,
					      "STR", szAltName);
			relpTcpChkOnePeerName(pThis, szAltName, &bFoundPositiveMatch);
			
		}
		++iAltName;
	}

	if(!bFoundPositiveMatch) {
		
		if(relpTcpGetCN(pThis, cert, cnBuf, sizeof(cnBuf)) == 0) {
			pThis->pEngine->dbgprint("STR", cnBuf);
			iAllNames += snprintf(allNames+iAllNames, sizeof(allNames)-iAllNames,
					      "STR", cnBuf);
			relpTcpChkOnePeerName(pThis, cnBuf, &bFoundPositiveMatch);
		}
	}

	if(!bFoundPositiveMatch) {
		callOnAuthErr(pThis, allNames, "STR", RELP_RET_AUTH_ERR_NAME);
		r = GNUTLS_E_CERTIFICATE_ERROR; goto done;
	}
	r = 0;
done:
	return r;
}