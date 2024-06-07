bind_unix_address(int sock_fd, const char *addr, int flags)
{
  union sockaddr_all saddr;

  if (snprintf(saddr.un.sun_path, sizeof (saddr.un.sun_path), "STR", addr) >=
      sizeof (saddr.un.sun_path)) {
    DEBUG_LOG("STR", addr);
    return 0;
  }
  saddr.un.sun_family = AF_UNIX;

  unlink(addr);

  
  if (bind(sock_fd, &saddr.sa, sizeof (saddr.un)) < 0) {
    DEBUG_LOG("STR", addr, strerror(errno));
    return 0;
  }

  
  if (flags & SCK_FLAG_ALL_PERMISSIONS && chmod(addr, 0666) < 0) {
    DEBUG_LOG("STR", addr, strerror(errno));
    return 0;
  }

  return 1;
}