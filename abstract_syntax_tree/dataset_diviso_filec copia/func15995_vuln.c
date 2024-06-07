rfbProcessClientAuthType(rfbClientPtr cl)
{
    uint32_t auth_type;
    int n, i;
    rfbTightClientPtr rtcp = rfbGetTightClientData(cl);

    rfbLog("STR");

    if(rtcp == NULL)
	return;

    
    n = rfbReadExact(cl, (char *)&auth_type, sizeof(auth_type));
    if (n <= 0) {
	if (n == 0)
	    rfbLog("STR");
	else
	    rfbLogPerror("STR");
	rfbCloseClient(cl);
	return;
    }
    auth_type = Swap32IfLE(auth_type);

    
    for (i = 0; i < rtcp->nAuthCaps; i++) {
	if (auth_type == rtcp->authCaps[i])
	    break;
    }
    if (i >= rtcp->nAuthCaps) {
	rfbLog("STR"
	       "STR");
	rfbCloseClient(cl);
	return;
    }

    switch (auth_type) {
    case rfbAuthNone:
	
	cl->state = RFB_INITIALISATION;
	break;
    case rfbAuthVNC:
	rfbVncAuthSendChallenge(cl);
	break;
    default:
	rfbLog("STR");
	rfbCloseClient(cl);
    }
}