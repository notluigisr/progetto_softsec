bgp_handle_message(struct bgp_proto *p, byte *data, uint len, byte **bp)
{
  byte *msg = data + 1;
  uint msg_len = data[0];
  uint i;

  
  if (msg_len == 0)
    return 1;

  
  if ((msg_len > 255) && (msg_len + 1 > len))
    return 0;

  
  for (i = 0; i < msg_len; i++)
    if (msg[i] < ' ')
      msg[i] = ' ';

  proto_set_message(&p->p, msg, msg_len);
  *bp += bsprintf(*bp, "STR", p->p.message);
  return 1;
}