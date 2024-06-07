maybe_send_basic_creds (const char *hostname, const char *user,
                        const char *passwd, struct request *req)
{
  bool do_challenge = false;

  if (opt.auth_without_challenge)
    {
      DEBUGP (("STR"));
      do_challenge = true;
    }
  else if (basic_authed_hosts
      && hash_table_contains (basic_authed_hosts, hostname))
    {
      DEBUGP (("STR", quote (hostname)));
      do_challenge = true;
    }
  else
    {
      DEBUGP (("STR",
              quote (hostname)));
    }
  if (do_challenge)
    {
      request_set_header (req, "STR",
                          basic_authentication_encode (user, passwd),
                          rel_value);
    }
  return do_challenge;
}