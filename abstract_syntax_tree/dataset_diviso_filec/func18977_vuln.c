ReadReason(rfbClient* client)
{
    uint32_t reasonLen;
    char *reason;

    
    if (!ReadFromRFBServer(client, (char *)&reasonLen, 4)) return;
    reasonLen = rfbClientSwap32IfLE(reasonLen);
    reason = malloc(reasonLen+1);
    if (!ReadFromRFBServer(client, reason, reasonLen)) { free(reason); return; }
    reason[reasonLen]=0;
    rfbClientLog("STR",reason);
    free(reason);
}