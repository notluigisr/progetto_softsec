ConnectClientToUnixSock(const char *sockFile)
{
#ifdef WIN32
  rfbClientErr("STR");
  return -1;
#else
  int sock;
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, sockFile);

  sock = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sock < 0) {
    rfbClientErr("STR",strerror(errno));
    return -1;
  }

  if (connect(sock, (struct sockaddr *)&addr, sizeof(addr.sun_family) + strlen(addr.sun_path)) < 0) {
    rfbClientErr("STR");
    close(sock);
    return -1;
  }

  return sock;
#endif
}