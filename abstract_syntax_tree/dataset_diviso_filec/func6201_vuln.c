parse_key_usage (PKT_signature * sig)
{
  int key_usage = 0;
  const byte *p;
  size_t n;
  byte flags;

  p = parse_sig_subpkt (sig->hashed, SIGSUBPKT_KEY_FLAGS, &n);
  if (p && n)
    {
      
      flags = *p;

      if (flags & 1)
	{
	  key_usage |= PUBKEY_USAGE_CERT;
	  flags &= ~1;
	}

      if (flags & 2)
	{
	  key_usage |= PUBKEY_USAGE_SIG;
	  flags &= ~2;
	}

      
      if (flags & (0x04 | 0x08))
	{
	  key_usage |= PUBKEY_USAGE_ENC;
	  flags &= ~(0x04 | 0x08);
	}

      if (flags & 0x20)
	{
	  key_usage |= PUBKEY_USAGE_AUTH;
	  flags &= ~0x20;
	}

      if (flags)
	key_usage |= PUBKEY_USAGE_UNKNOWN;
    }

  

  return key_usage;
}