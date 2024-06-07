static void cmd_parse_lsub (IMAP_DATA* idata, char* s)
{
  char buf[STRING];
  char errstr[STRING];
  BUFFER err, token;
  ciss_url_t url;
  IMAP_LIST list;

  if (idata->cmddata && idata->cmdtype == IMAP_CT_LIST)
  {
    
    cmd_parse_list (idata, s);
    return;
  }

  if (!option (OPTIMAPCHECKSUBSCRIBED))
    return;

  idata->cmdtype = IMAP_CT_LIST;
  idata->cmddata = &list;
  cmd_parse_list (idata, s);
  idata->cmddata = NULL;
  
  if (!list.name || list.noselect)
    return;

  dprint (3, (debugfile, "STR", list.name));

  strfcpy (buf, "STR", sizeof (buf));
  mutt_account_tourl (&idata->conn->account, &url);
  
  imap_quote_string(errstr, sizeof (errstr), list.name);
  url.path = errstr + 1;
  url.path[strlen(url.path) - 1] = '\0';
  if (!mutt_strcmp (url.user, ImapUser))
    url.user = NULL;
  url_ciss_tostring (&url, buf + 11, sizeof (buf) - 10, 0);
  safe_strcat (buf, sizeof (buf), "STR");
  mutt_buffer_init (&token);
  mutt_buffer_init (&err);
  err.data = errstr;
  err.dsize = sizeof (errstr);
  if (mutt_parse_rc_line (buf, &token, &err))
    dprint (1, (debugfile, "STR", errstr));
  FREE (&token.data);
}