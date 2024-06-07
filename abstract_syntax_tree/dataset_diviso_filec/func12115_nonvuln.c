authority_cert_get_newest_by_id(const char *id_digest)
{
  cert_list_t *cl;
  authority_cert_t *best = NULL;
  if (!trusted_dir_certs ||
      !(cl = digestmap_get(trusted_dir_certs, id_digest)))
    return NULL;

  SMARTLIST_FOREACH(cl->certs, authority_cert_t *, cert,
  {
    if (!best || cert->cache_info.published_on > best->cache_info.published_on)
      best = cert;
  });
  return best;
}