bgp_put_cap_ipv4(struct bgp_proto *p UNUSED, byte *buf)
{
  *buf++ = 1;		
  *buf++ = 4;		
  *buf++ = 0;		
  *buf++ = BGP_AF_IPV4;
  *buf++ = 0;		
  *buf++ = 1;		
  return buf;
}