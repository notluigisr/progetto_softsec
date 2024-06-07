bgp_log_error(struct bgp_proto *p, u8 class, char *msg, unsigned code, unsigned subcode, byte *data, unsigned len)
{
  byte argbuf[256], *t = argbuf;
  unsigned i;

  
  if (code == 6 && class == BE_BGP_TX)
    return;

  
  if ((code == 6) && ((subcode == 2) || (subcode == 4)))
    proto_set_message(&p->p, NULL, 0);

  if (len)
    {
      
      if ((code == 2) && (subcode == 2) && ((len == 2) || (len == 4)))
	{
	  t += bsprintf(t, "STR", (len == 2) ? get_u16(data) : get_u32(data));
	  goto done;
	}

      
      if (((code == 6) && ((subcode == 2) || (subcode == 4))))
	if (bgp_handle_message(p, data, len, &t))
	  goto done;

      *t++ = ':';
      *t++ = ' ';
      if (len > 16)
	len = 16;
      for (i=0; i<len; i++)
	t += bsprintf(t, "STR", data[i]);
    }

done:
  *t = 0;
  const byte *dsc = bgp_error_dsc(code, subcode);
  log(L_REMOTE "STR", p->p.name, msg, dsc, argbuf);
}