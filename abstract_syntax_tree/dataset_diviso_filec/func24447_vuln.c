rfbSendAuthCaps(rfbClientPtr cl)
{
    rfbAuthenticationCapsMsg caps;
    rfbCapabilityInfo caplist[MAX_AUTH_CAPS];
    int count = 0;
    rfbTightClientPtr rtcp = rfbGetTightClientData(cl);

    rfbLog("STR");

    if(rtcp == NULL)
	return;

    if (cl->screen->authPasswdData && !cl->reverseConnection) {
	
	    SetCapInfo(&caplist[count], rfbAuthVNC, rfbStandardVendor);
	    rtcp->authCaps[count++] = rfbAuthVNC;
    }

    rtcp->nAuthCaps = count;
    caps.nAuthTypes = Swap32IfLE((uint32_t)count);
    if (rfbWriteExact(cl, (char *)&caps, sz_rfbAuthenticationCapsMsg) < 0) {
	rfbLogPerror("STR");
	rfbCloseClient(cl);
	return;
    }

    if (count) {
	if (rfbWriteExact(cl, (char *)&caplist[0],
		       count * sz_rfbCapabilityInfo) < 0) {
	    rfbLogPerror("STR");
	    rfbCloseClient(cl);
	    return;
	}
	
	
	rfbProcessClientAuthType(cl);
    } else {
	
	cl->state = RFB_INITIALISATION;
    }
}