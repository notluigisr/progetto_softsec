SCK_RemoveSocket(int sock_fd)
{
  union sockaddr_all saddr;
  socklen_t saddr_len;

  saddr_len = sizeof (saddr);

  if (getsockname(sock_fd, &saddr.sa, &saddr_len) < 0) {
    DEBUG_LOG("STR", strerror(errno));
    return 0;
  }

  if (saddr_len > sizeof (saddr) || saddr_len <= sizeof (saddr.sa.sa_family) ||
      saddr.sa.sa_family != AF_UNIX)
    return 0;

  if (!UTI_RemoveFile(NULL, saddr.un.sun_path, NULL))
    return 0;

  return 1;
}