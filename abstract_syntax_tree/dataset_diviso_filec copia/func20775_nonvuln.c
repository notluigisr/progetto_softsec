void rfbClientCleanup(rfbClient* client) {
#ifdef LIBVNCSERVER_HAVE_LIBZ
#ifdef LIBVNCSERVER_HAVE_LIBJPEG
  int i;

  for ( i = 0; i < 4; i++ ) {
    if (client->zlibStreamActive[i] == TRUE ) {
      if (inflateEnd (&client->zlibStream[i]) != Z_OK &&
	  client->zlibStream[i].msg != NULL)
	rfbClientLog("STR", client->zlibStream[i].msg);
    }
  }

  if ( client->decompStreamInited == TRUE ) {
    if (inflateEnd (&client->decompStream) != Z_OK &&
	client->decompStream.msg != NULL)
      rfbClientLog("STR", client->decompStream.msg );
  }
#endif
#endif

  if (client->ultra_buffer)
    free(client->ultra_buffer);

  if (client->raw_buffer)
    free(client->raw_buffer);

  FreeTLS(client);

  while (client->clientData) {
    rfbClientData* next = client->clientData->next;
    free(client->clientData);
    client->clientData = next;
  }

  if (client->sock != RFB_INVALID_SOCKET)
    rfbCloseSocket(client->sock);
  if (client->listenSock != RFB_INVALID_SOCKET)
    rfbCloseSocket(client->listenSock);
  free(client->desktopName);
  free(client->serverHost);
  if (client->destHost)
    free(client->destHost);
  if (client->clientAuthSchemes)
    free(client->clientAuthSchemes);

#ifdef LIBVNCSERVER_HAVE_SASL
  if (client->saslSecret)
    free(client->saslSecret);
#endif 

#ifdef WIN32
  if(WSACleanup() != 0) {
      errno=WSAGetLastError();
      rfbClientErr("STR", strerror(errno));
  }
#endif

  free(client);
}