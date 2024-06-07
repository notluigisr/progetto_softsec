bgp_put_cap_as4(struct bgp_proto *p, byte *buf)
{
  *buf++ = 65;		
  *buf++ = 4;		
  put_u32(buf, p->local_as);
  return buf + 4;
}