agent_scd_writekey (int keyno, const char *serialno,
                    const unsigned char *keydata, size_t keydatalen)
{
  int rc;
  char line[ASSUAN_LINELENGTH];
  struct writekey_parm_s parms;
  struct default_inq_parm_s dfltparm;

  memset (&dfltparm, 0, sizeof dfltparm);

  (void)serialno;

  rc = start_agent (NULL, 1);
  if (rc)
    return rc;

  memset (&parms, 0, sizeof parms);

  snprintf (line, DIM(line)-1, "STR", keyno);
  line[DIM(line)-1] = 0;
  dfltparm.ctx = agent_ctx;
  parms.dflt = &dfltparm;
  parms.keydata = keydata;
  parms.keydatalen = keydatalen;

  rc = assuan_transact (agent_ctx, line, NULL, NULL,
                        inq_writekey_parms, &parms, NULL, NULL);

  status_sc_op_failure (rc);
  return rc;
}