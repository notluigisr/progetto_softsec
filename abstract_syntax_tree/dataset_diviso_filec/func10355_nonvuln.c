bgp_create_route_refresh(struct bgp_channel *c, byte *buf)
{
  struct bgp_proto *p = (void *) c->c.proto;

  BGP_TRACE(D_PACKETS, "STR");

  
  put_af4(buf, c->afi);
  buf[2] = BGP_RR_REQUEST;

  return buf+4;
}