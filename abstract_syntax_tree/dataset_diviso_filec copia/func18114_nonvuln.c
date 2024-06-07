g_tcp_can_recv(int sck, int millis)
{
  fd_set rfds;
  struct timeval time;
  int rv;

  time.tv_sec = millis / 1000;
  time.tv_usec = (millis * 1000) % 1000000;
  FD_ZERO(&rfds);
  if (sck > 0)
  {
    FD_SET(((unsigned int)sck), &rfds);
    rv = select(sck + 1, &rfds, 0, 0, &time);
    if (rv > 0)
    {
      return g_tcp_socket_ok(sck);
    }
  }
  return 0;
}