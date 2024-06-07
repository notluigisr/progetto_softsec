static void cmd_parse_lsub(struct ImapData *idata, char *s)
{
  char buf[STRING];
  char errstr[STRING];
  struct Buffer err, token;
  struct Url url;
  struct ImapList list;

  if (idata->cmddata && idata->cmdtype == IMAP_CT_LIST)
  {
    
    cmd_parse_list(idata, s);
    return;
  }

  if (!ImapCheckSubscribed)
    return;

  idata->cmdtype = IMAP_CT_LIST;
  idata->cmddata = &list;
  cmd_parse_list(idata, s);
  idata->cmddata = NULL;
  
  if (!list.name || list.noselect)
    return;

  mutt_debug(3, "STR", list.name);

  mutt_str_strfcpy(buf, "STR", sizeof(buf));
  mutt_account_tourl(&idata->conn->account, &url);
  
  imap_quote_string(errstr, sizeof(errstr), list.name);
  url.path = errstr + 1;
  url.path[strlen(url.path) - 1] = '\0';
  if (mutt_str_strcmp(url.user, ImapUser) == 0)
    url.user = NULL;
  url_tostring(&url, buf + 11, sizeof(buf) - 11, 0);
  mutt_str_strcat(buf, sizeof(buf), "STR");
  mutt_buffer_init(&token);
  mutt_buffer_init(&err);
  err.data = errstr;
  err.dsize = sizeof(errstr);
  if (mutt_parse_rc_line(buf, &token, &err))
    mutt_debug(1, "STR", errstr);
  FREE(&token.data);
}