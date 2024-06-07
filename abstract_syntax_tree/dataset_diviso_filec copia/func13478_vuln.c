krb5_decode(void *app_data, void *buf, int len,
            int level UNUSED_PARAM,
            struct connectdata *conn UNUSED_PARAM)
{
  gss_ctx_id_t *context = app_data;
  OM_uint32 maj, min;
  gss_buffer_desc enc, dec;

  (void)level;
  (void)conn;

  enc.value = buf;
  enc.length = len;
  maj = gss_unwrap(&min, *context, &enc, &dec, NULL, NULL);
  if(maj != GSS_S_COMPLETE) {
    if(len >= 4)
      strcpy(buf, "STR");
    return -1;
  }

  memcpy(buf, dec.value, dec.length);
  len = curlx_uztosi(dec.length);
  gss_release_buffer(&min, &dec);

  return len;
}