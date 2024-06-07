ConnectToRFBServer(rfbClient* client,const char *hostname, int port)
{
  if (client->serverPort==-1) {
    
    const char* magic="STR";
    char buffer[10];
    rfbVNCRec* rec = (rfbVNCRec*)malloc(sizeof(rfbVNCRec));
    client->vncRec = rec;

    rec->file = fopen(client->serverHost,"STR");
    rec->tv.tv_sec = 0;
    rec->readTimestamp = FALSE;
    rec->doNotSleep = FALSE;
    
    if (!rec->file) {
      rfbClientLog("STR",client->serverHost);
      return FALSE;
    }
    setbuf(rec->file,NULL);

    if (fread(buffer,1,strlen(magic),rec->file) != strlen(magic) || strncmp(buffer,magic,strlen(magic))) {
      rfbClientLog("STR",client->serverHost);
      fclose(rec->file);
      return FALSE;
    }
    client->sock = RFB_INVALID_SOCKET;
    return TRUE;
  }

#ifndef WIN32
  if(IsUnixSocket(hostname))
    
    client->sock = ConnectClientToUnixSockWithTimeout(hostname, client->connectTimeout);
  else
#endif
  {
#ifdef LIBVNCSERVER_IPv6
    client->sock = ConnectClientToTcpAddr6WithTimeout(hostname, port, client->connectTimeout);
#else
    unsigned int host;

    
    if (!StringToIPAddr(hostname, &host)) {
      rfbClientLog("STR", hostname);
      return FALSE;
    }
    client->sock = ConnectClientToTcpAddrWithTimeout(host, port, client->connectTimeout);
#endif
  }

  if (client->sock == RFB_INVALID_SOCKET) {
    rfbClientLog("STR");
    return FALSE;
  }

  if(client->QoS_DSCP && !SetDSCP(client->sock, client->QoS_DSCP))
     return FALSE;

  return TRUE;
}