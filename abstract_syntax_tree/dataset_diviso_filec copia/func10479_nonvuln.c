bind_ip_address(int sock_fd, IPSockAddr *addr, int flags)
{
  union sockaddr_all saddr;
  socklen_t saddr_len;
  int s;

  
  if (addr->port > 0 && !SCK_SetIntOption(sock_fd, SOL_SOCKET, SO_REUSEADDR, 1))
    ;

#ifdef IP_FREEBIND
  
  if (!SCK_SetIntOption(sock_fd, IPPROTO_IP, IP_FREEBIND, 1))
    ;
#endif

  saddr_len = SCK_IPSockAddrToSockaddr(addr, (struct sockaddr *)&saddr, sizeof (saddr));
  if (saddr_len == 0)
    return 0;

  if (flags & SCK_FLAG_PRIV_BIND && priv_bind_function)
    s = priv_bind_function(sock_fd, &saddr.sa, saddr_len);
  else
    s = bind(sock_fd, &saddr.sa, saddr_len);

  if (s < 0) {
    DEBUG_LOG("STR",
              UTI_IPSockAddrToString(addr), strerror(errno));
    return 0;
  }

  return 1;
}