UTI_IPToString(IPAddr *addr)
{
  unsigned long a, b, c, d, ip;
  uint8_t *ip6;
  char *result;

  result = NEXT_BUFFER;
  switch (addr->family) {
    case IPADDR_UNSPEC:
      snprintf(result, BUFFER_LENGTH, "STR");
      break;
    case IPADDR_INET4:
      ip = addr->addr.in4;
      a = (ip>>24) & 0xff;
      b = (ip>>16) & 0xff;
      c = (ip>> 8) & 0xff;
      d = (ip>> 0) & 0xff;
      snprintf(result, BUFFER_LENGTH, "STR", a, b, c, d);
      break;
    case IPADDR_INET6:
      ip6 = addr->addr.in6;
#ifdef FEAT_IPV6
      inet_ntop(AF_INET6, ip6, result, BUFFER_LENGTH);
#else
      assert(BUFFER_LENGTH >= 40);
      for (a = 0; a < 8; a++)
        snprintf(result + a * 5, 40 - a * 5, "STR",
                 (unsigned int)(ip6[2 * a] << 8 | ip6[2 * a + 1]));
#endif
      break;
    default:
      snprintf(result, BUFFER_LENGTH, "STR");
  }
  return result;
}