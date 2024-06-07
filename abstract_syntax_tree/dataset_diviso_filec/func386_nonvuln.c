connection_dir_retry_bridges(smartlist_t *descs)
{
  char digest[DIGEST_LEN];
  SMARTLIST_FOREACH(descs, const char *, cp,
  {
    if (base16_decode(digest, DIGEST_LEN, cp, strlen(cp))<0) {
      log_warn(LD_BUG, "STR",
              escaped(cp));
      continue;
    }
    retry_bridge_descriptor_fetch_directly(digest);
  });
}