agent_scd_genkey (struct agent_card_genkey_s *info, int keyno, int force,
                  const char *serialno, u32 createtime)
{
  int rc;
  char line[ASSUAN_LINELENGTH];
  gnupg_isotime_t tbuf;
  struct scd_genkey_parm_s parms;
  struct default_inq_parm_s dfltparm;

  memset (&dfltparm, 0, sizeof dfltparm);

  (void)serialno;

  memset (&parms, 0, sizeof parms);
  parms.cgk = info;

  rc = start_agent (NULL, 1);
  if (rc)
    return rc;

  if (createtime)
    epoch2isotime (tbuf, createtime);
  else
    *tbuf = 0;

  snprintf (line, DIM(line)-1, "STR",
            *tbuf? "STR", tbuf,
            force? "STR",
            keyno);
  line[DIM(line)-1] = 0;

  dfltparm.ctx = agent_ctx;
  memset (info, 0, sizeof *info);
  rc = assuan_transact (agent_ctx, line,
                        NULL, NULL, default_inq_cb, &dfltparm,
                        scd_genkey_cb, &parms);

  xfree (parms.savedbytes);

  status_sc_op_failure (rc);
  return rc;
}