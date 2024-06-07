rfbHandleAuthResult(rfbClient* client)
{
    uint32_t authResult=0, reasonLen=0;
    char *reason=NULL;

    if (!ReadFromRFBServer(client, (char *)&authResult, 4)) return FALSE;

    authResult = rfbClientSwap32IfLE(authResult);

    switch (authResult) {
    case rfbVncAuthOK:
      rfbClientLog("STR");
      return TRUE;
      break;
    case rfbVncAuthFailed:
      if (client->major==3 && client->minor>7)
      {
        
        if (!ReadFromRFBServer(client, (char *)&reasonLen, 4)) return FALSE;
        reasonLen = rfbClientSwap32IfLE(reasonLen);
        reason = malloc((uint64_t)reasonLen+1);
        if (!ReadFromRFBServer(client, reason, reasonLen)) { free(reason); return FALSE; }
        reason[reasonLen]=0;
        rfbClientLog("STR",reason);
        free(reason);
        return FALSE;
      }
      rfbClientLog("STR");
      return FALSE;
    case rfbVncAuthTooMany:
      rfbClientLog("STR");
      return FALSE;
    }

    rfbClientLog("STR",
                 (int)authResult);
    return FALSE;
}