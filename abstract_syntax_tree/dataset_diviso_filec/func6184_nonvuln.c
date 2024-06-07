static int complete_hosts(char *buf, size_t buflen)
{
  struct Buffy *mailbox = NULL;
  struct Connection *conn = NULL;
  int rc = -1;
  size_t matchlen;

  matchlen = mutt_str_strlen(buf);
  for (mailbox = Incoming; mailbox; mailbox = mailbox->next)
  {
    if (mutt_str_strncmp(buf, mailbox->path, matchlen) == 0)
    {
      if (rc)
      {
        mutt_str_strfcpy(buf, mailbox->path, buflen);
        rc = 0;
      }
      else
        longest_common_prefix(buf, mailbox->path, matchlen, buflen);
    }
  }

  TAILQ_FOREACH(conn, mutt_socket_head(), entries)
  {
    struct Url url;
    char urlstr[LONG_STRING];

    if (conn->account.type != MUTT_ACCT_TYPE_IMAP)
      continue;

    mutt_account_tourl(&conn->account, &url);
    
    url.user = NULL;
    url.path = NULL;
    url_tostring(&url, urlstr, sizeof(urlstr), 0);
    if (mutt_str_strncmp(buf, urlstr, matchlen) == 0)
    {
      if (rc)
      {
        mutt_str_strfcpy(buf, urlstr, buflen);
        rc = 0;
      }
      else
        longest_common_prefix(buf, urlstr, matchlen, buflen);
    }
  }

  return rc;
}