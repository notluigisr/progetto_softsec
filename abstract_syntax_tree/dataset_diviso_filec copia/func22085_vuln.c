rfbBool ConnectToRFBRepeater(rfbClient* client,const char *repeaterHost, int repeaterPort, const char *destHost, int destPort)
{
  rfbProtocolVersionMsg pv;
  int major,minor;
  char tmphost[250];

#ifdef LIBVNCSERVER_IPv6
  client->sock = ConnectClientToTcpAddr6(repeaterHost, repeaterPort);
  if (client->sock == -1)
#endif
  {
    unsigned int host;
    if (!StringToIPAddr(repeaterHost, &host)) {
      rfbClientLog("STR", repeaterHost);
      return FALSE;
    }

    client->sock = ConnectClientToTcpAddr(host, repeaterPort);
  }

  if (client->sock < 0) {
    rfbClientLog("STR");
    return FALSE;
  }

  if (!SetNonBlocking(client->sock))
    return FALSE;

  if (!ReadFromRFBServer(client, pv, sz_rfbProtocolVersionMsg))
    return FALSE;
  pv[sz_rfbProtocolVersionMsg] = 0;

  
  if (sscanf(pv,rfbProtocolVersionFormat,&major,&minor) != 2 || major != 0 || minor != 0) {
    rfbClientLog("STR",pv);
    return FALSE;
  }

  rfbClientLog("STR", major, minor);

  snprintf(tmphost, sizeof(tmphost), "STR", destHost, destPort);
  if (!WriteToRFBServer(client, tmphost, sizeof(tmphost)))
    return FALSE;

  return TRUE;
}