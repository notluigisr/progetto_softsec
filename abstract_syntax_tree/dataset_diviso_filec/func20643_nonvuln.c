static int complete_hosts(char *buf, size_t buflen)
{
  
  int rc = -1;
  size_t matchlen;

  matchlen = mutt_str_strlen(buf);
  struct MailboxList ml = STAILQ_HEAD_INITIALIZER(ml);
  neomutt_mailboxlist_get_all(&ml, NeoMutt, MUTT_MAILBOX_ANY);
  struct MailboxNode *np = NULL;
  STAILQ_FOREACH(np, &ml, entries)
  {
    if (!mutt_str_startswith(mailbox_path(np->mailbox), buf, CASE_MATCH))
      continue;

    if (rc)
    {
      mutt_str_strfcpy(buf, mailbox_path(np->mailbox), buflen);
      rc = 0;
    }
    else
      longest_common_prefix(buf, mailbox_path(np->mailbox), matchlen, buflen);
  }
  neomutt_mailboxlist_clear(&ml);

#if 0
  TAILQ_FOREACH(conn, mutt_socket_head(), entries)
  {
    struct Url url = { 0 };
    char urlstr[1024];

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
#endif

  return rc;
}