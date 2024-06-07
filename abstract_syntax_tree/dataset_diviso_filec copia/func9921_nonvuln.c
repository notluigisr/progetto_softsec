add_keyserver_modify (PKT_signature *sig,int enabled)
{
  const byte *s;
  size_t n;
  int i;
  char *buf;

  
  enabled=!enabled;

  s = parse_sig_subpkt (sig->hashed, SIGSUBPKT_KS_FLAGS, &n );
  
  if (s && n &&
      ((enabled && (s[0] & 0x80)) || (!enabled && !(s[0] & 0x80))))
    return;

  if (!s || !n) { 
    n = 1;
    buf = xmalloc_clear (n);
  }
  else {
    buf = xmalloc (n);
    memcpy (buf, s, n);
  }

  if(enabled)
    buf[0] |= 0x80; 
  else
    buf[0] &= ~0x80;

  
  for(i=0;i<n;i++)
    if(buf[i]!=0)
      break;

  if(i==n)
    delete_sig_subpkt (sig->hashed, SIGSUBPKT_KS_FLAGS);
  else
    build_sig_subpkt (sig, SIGSUBPKT_KS_FLAGS, buf, n);

  xfree (buf);
}