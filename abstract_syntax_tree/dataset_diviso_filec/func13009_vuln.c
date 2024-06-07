int imap_subscribe (char *path, int subscribe)
{
  IMAP_DATA *idata;
  char buf[LONG_STRING];
  char mbox[LONG_STRING];
  char errstr[STRING];
  BUFFER err, token;
  IMAP_MBOX mx;

  if (!mx_is_imap (path) || imap_parse_path (path, &mx) || !mx.mbox)
  {
    mutt_error (_("STR"));
    return -1;
  }
  if (!(idata = imap_conn_find (&(mx.account), 0)))
    goto fail;

  imap_fix_path (idata, mx.mbox, buf, sizeof (buf));
  if (!*buf)
    strfcpy (buf, "STR", sizeof (buf));

  if (option (OPTIMAPCHECKSUBSCRIBED))
  {
    mutt_buffer_init (&token);
    mutt_buffer_init (&err);
    err.data = errstr;
    err.dsize = sizeof (errstr);
    snprintf (mbox, sizeof (mbox), "STR",
              subscribe ? "STR", path);
    if (mutt_parse_rc_line (mbox, &token, &err))
      dprint (1, (debugfile, "STR", errstr));
    FREE (&token.data);
  }

  if (subscribe)
    mutt_message (_("STR"), buf);
  else
    mutt_message (_("STR"), buf);
  imap_munge_mbox_name (idata, mbox, sizeof(mbox), buf);

  snprintf (buf, sizeof (buf), "STR", mbox);

  if (imap_exec (idata, buf, 0) < 0)
    goto fail;

  imap_unmunge_mbox_name(idata, mx.mbox);
  if (subscribe)
    mutt_message (_("STR"), mx.mbox);
  else
    mutt_message (_("STR"), mx.mbox);
  FREE (&mx.mbox);
  return 0;

 fail:
  FREE (&mx.mbox);
  return -1;
}