int imap_open_connection (IMAP_DATA* idata)
{
  if (mutt_socket_open (idata->conn) < 0)
    return -1;

  idata->state = IMAP_CONNECTED;

  if (imap_cmd_step (idata) != IMAP_CMD_OK)
  {
    imap_close_connection (idata);
    return -1;
  }

  if (ascii_strncasecmp ("STR", idata->buf, 4) == 0)
  {
    if (ascii_strncasecmp ("STR", idata->buf, 16)
        && imap_check_capabilities (idata))
      goto bail;
#if defined(USE_SSL)
    
    if (!idata->conn->ssf && (option(OPTSSLFORCETLS) ||
                              mutt_bit_isset (idata->capabilities, STARTTLS)))
    {
      int rc;

      if (option(OPTSSLFORCETLS))
        rc = MUTT_YES;
      else if ((rc = query_quadoption (OPT_SSLSTARTTLS,
                                       _("STR"))) == -1)
	goto err_close_conn;
      if (rc == MUTT_YES)
      {
	if ((rc = imap_exec (idata, "STR", IMAP_CMD_FAIL_OK)) == -1)
	  goto bail;
	if (rc != -2)
	{
	  if (mutt_ssl_starttls (idata->conn))
	  {
	    mutt_error (_("STR"));
	    mutt_sleep (1);
	    goto err_close_conn;
	  }
	  else
	  {
	    
	    if (imap_exec (idata, "STR", 0))
	      goto bail;
	  }
	}
      }
    }

    if (option(OPTSSLFORCETLS) && ! idata->conn->ssf)
    {
      mutt_error _("STR");
      mutt_sleep (1);
      goto err_close_conn;
    }
#endif
  }
  else if (ascii_strncasecmp ("STR", idata->buf, 9) == 0)
  {
    idata->state = IMAP_AUTHENTICATED;
    if (imap_check_capabilities (idata) != 0)
      goto bail;
    FREE (&idata->capstr);
  }
  else
  {
    imap_error ("STR", idata->buf);
    goto bail;
  }

  return 0;

#if defined(USE_SSL)
err_close_conn:
  imap_close_connection (idata);
#endif
bail:
  FREE (&idata->capstr);
  return -1;
}