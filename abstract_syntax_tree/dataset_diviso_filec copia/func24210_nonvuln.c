read_all(tor_socket_t fd, char *buf, size_t count, int isSocket)
{
  size_t numread = 0;
  ssize_t result;

  if (count > SIZE_T_CEILING || count > SSIZE_T_MAX)
    return -1;

  while (numread != count) {
    if (isSocket)
      result = tor_socket_recv(fd, buf+numread, count-numread, 0);
    else
      result = read((int)fd, buf+numread, count-numread);
    if (result<0)
      return -1;
    else if (result == 0)
      break;
    numread += result;
  }
  return (ssize_t)numread;
}