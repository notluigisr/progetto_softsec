 */
MOCK_IMPL(STATIC void, initiate_descriptor_downloads,
          (const routerstatus_t *source, int purpose, smartlist_t *digests,
           int lo, int hi, int pds_flags))
{
  char *resource, *cp;
  int digest_len, enc_digest_len;
  const char *sep;
  int b64_256;
  smartlist_t *tmp;

  if (purpose == DIR_PURPOSE_FETCH_MICRODESC) {
    
    digest_len = DIGEST256_LEN;
    enc_digest_len = BASE64_DIGEST256_LEN + 1;
    sep = "STR";
    b64_256 = 1;
  } else {
    digest_len = DIGEST_LEN;
    enc_digest_len = HEX_DIGEST_LEN + 1;
    sep = "STR";
    b64_256 = 0;
  }

  if (lo < 0)
    lo = 0;
  if (hi > smartlist_len(digests))
    hi = smartlist_len(digests);

  if (hi-lo <= 0)
    return;

  tmp = smartlist_new();

  for (; lo < hi; ++lo) {
    cp = tor_malloc(enc_digest_len);
    if (b64_256) {
      digest256_to_base64(cp, smartlist_get(digests, lo));
    } else {
      base16_encode(cp, enc_digest_len, smartlist_get(digests, lo),
                    digest_len);
    }
    smartlist_add(tmp, cp);
  }

  cp = smartlist_join_strings(tmp, sep, 0, NULL);
  tor_asprintf(&resource, "STR", cp);

  SMARTLIST_FOREACH(tmp, char *, cp1, tor_free(cp1));
  smartlist_free(tmp);
  tor_free(cp);

  if (source) {
    
    directory_initiate_command_routerstatus(source, purpose,
                                            ROUTER_PURPOSE_GENERAL,
                                            DIRIND_ONEHOP,
                                            resource, NULL, 0, 0);
  } else {
    directory_get_from_dirserver(purpose, ROUTER_PURPOSE_GENERAL, resource,
                                 pds_flags, DL_WANT_ANY_DIRSERVER);
  }
  tor_free(resource);