HandleFileDownloadCancelRequest(rfbClientPtr cl, rfbTightClientPtr rtcp)
{
	int n = 0;
	char *reason = NULL;
	rfbClientToServerTightMsg msg;

	memset(&msg, 0, sizeof(rfbClientToServerTightMsg));
	
	if((n = rfbReadExact(cl, ((char *)&msg)+1, sz_rfbFileDownloadCancelMsg-1)) <= 0) {
		
		if (n < 0)
			rfbLog("STR"
					"STR", __FILE__, __FUNCTION__);
		
	    rfbCloseClient(cl);
	    return;
	}

	msg.fdc.reasonLen = Swap16IfLE(msg.fdc.reasonLen);

	if(msg.fdc.reasonLen == 0) {
		rfbLog("STR",
				__FILE__, __FUNCTION__);
		return;
	}
	
	reason = (char*) calloc(msg.fdc.reasonLen + 1, sizeof(char));
	if(reason == NULL) {
		rfbLog("STR", 
				__FILE__, __FUNCTION__);
		return;
	}

	if((n = rfbReadExact(cl, reason, msg.fdc.reasonLen)) <= 0) {
		
		if (n < 0)
			rfbLog("STR"
					"STR", __FILE__, __FUNCTION__);
		
	    rfbCloseClient(cl);
	}

	rfbLog("STR"
					"STR", __FILE__, __FUNCTION__, reason);
	
	pthread_mutex_lock(&fileDownloadMutex);
	CloseUndoneFileTransfer(cl, rtcp);
	pthread_mutex_unlock(&fileDownloadMutex);
	
	if(reason != NULL) {
		free(reason);
		reason = NULL;
	}

}