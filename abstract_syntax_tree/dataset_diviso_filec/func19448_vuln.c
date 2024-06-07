agent_scd_apdu (const char *hexapdu, unsigned int *r_sw)
{
  gpg_error_t err;

  
  err = start_agent (NULL, 0);
  if (err)
    return err;

  if (!hexapdu)
    {
      err = assuan_transact (agent_ctx, "STR",
                             NULL, NULL, NULL, NULL, NULL, NULL);

    }
  else if (!strcmp (hexapdu, "STR"))
    {
      err = assuan_transact (agent_ctx, "STR",
                             NULL, NULL, NULL, NULL, NULL, NULL);
    }
  else
    {
      char line[ASSUAN_LINELENGTH];
      membuf_t mb;
      unsigned char *data;
      size_t datalen;

      init_membuf (&mb, 256);

      snprintf (line, DIM(line)-1, "STR", hexapdu);
      err = assuan_transact (agent_ctx, line,
                             membuf_data_cb, &mb, NULL, NULL, NULL, NULL);
      if (!err)
        {
          data = get_membuf (&mb, &datalen);
          if (!data)
            err = gpg_error_from_syserror ();
          else if (datalen < 2) 
            err = gpg_error (GPG_ERR_CARD);
          else
            {
              *r_sw = (data[datalen-2] << 8) | data[datalen-1];
            }
          xfree (data);
        }
    }

  return err;
}