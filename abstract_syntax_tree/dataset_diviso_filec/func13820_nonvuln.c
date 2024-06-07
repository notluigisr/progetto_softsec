int
router_digest_is_trusted_dir_type(const char *digest, dirinfo_type_t type)
{
  if (!trusted_dir_servers)
    return 0;
  if (authdir_mode(get_options()) && router_digest_is_me(digest))
    return 1;
  SMARTLIST_FOREACH(trusted_dir_servers, dir_server_t *, ent,
    if (tor_memeq(digest, ent->digest, DIGEST_LEN)) {
      return (!type) || ((type & ent->type) != 0);
    });
  return 0;