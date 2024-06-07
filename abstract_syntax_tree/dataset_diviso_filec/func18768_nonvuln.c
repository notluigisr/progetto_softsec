agent_keywrap_key (ctrl_t ctrl, int forexport, void **r_kek, size_t *r_keklen)
{
  gpg_error_t err;
  membuf_t data;
  size_t len;
  unsigned char *buf;
  char line[ASSUAN_LINELENGTH];
  struct default_inq_parm_s dfltparm;

  memset (&dfltparm, 0, sizeof dfltparm);
  dfltparm.ctrl = ctrl;

  *r_kek = NULL;
  err = start_agent (ctrl, 0);
  if (err)
    return err;
  dfltparm.ctx = agent_ctx;

  snprintf (line, DIM(line)-1, "STR",
            forexport? "STR");

  init_membuf_secure (&data, 64);
  err = assuan_transact (agent_ctx, line,
                         membuf_data_cb, &data,
                         default_inq_cb, &dfltparm,
                         NULL, NULL);
  if (err)
    {
      xfree (get_membuf (&data, &len));
      return err;
    }
  buf = get_membuf (&data, &len);
  if (!buf)
    return gpg_error_from_syserror ();
  *r_kek = buf;
  *r_keklen = len;
  return 0;
}