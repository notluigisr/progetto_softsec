build_ecc_privkey_template (app_t app, int keyno,
                            const unsigned char *ecc_d, size_t ecc_d_len,
                            unsigned char **result, size_t *resultlen)
{
  unsigned char privkey[2];
  size_t privkey_len;
  unsigned char exthdr[2+2+1];
  size_t exthdr_len;
  unsigned char suffix[2+1];
  size_t suffix_len;
  unsigned char *tp;
  size_t datalen;
  unsigned char *template;
  size_t template_size;

  (void)app;

  *result = NULL;
  *resultlen = 0;

  
  datalen = 0;
  tp = privkey;

  tp += add_tlv (tp, 0x91, ecc_d_len); 
  datalen += ecc_d_len;

  privkey_len = tp - privkey;

  
  tp = exthdr;
  *tp++ = keyno ==0 ? 0xb6 : keyno == 1? 0xb8 : 0xa4;
  *tp++ = 0;
  tp += add_tlv (tp, 0x7f48, privkey_len);
  exthdr_len = tp - exthdr;

  
  tp = suffix;
  tp += add_tlv (tp, 0x5f48, datalen);
  suffix_len = tp - suffix;

  
  template_size = (1 + 1   
                   + exthdr_len
                   + privkey_len
                   + suffix_len
                   + datalen);
  tp = template = xtrymalloc_secure (template_size);
  if (!template)
    return gpg_error_from_syserror ();

  tp += add_tlv (tp, 0x4d, exthdr_len + privkey_len + suffix_len + datalen);
  memcpy (tp, exthdr, exthdr_len);
  tp += exthdr_len;
  memcpy (tp, privkey, privkey_len);
  tp += privkey_len;
  memcpy (tp, suffix, suffix_len);
  tp += suffix_len;

  memcpy (tp, ecc_d, ecc_d_len);
  tp += ecc_d_len;

  assert (tp - template == template_size);

  *result = template;
  *resultlen = tp - template;
  return 0;
}