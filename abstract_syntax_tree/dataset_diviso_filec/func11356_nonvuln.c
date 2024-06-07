pin_cb (void *opaque, const char *info, char **retstr)
{
  assuan_context_t ctx = opaque;
  char *command;
  int rc;
  unsigned char *value;
  size_t valuelen;

  if (!retstr)
    {
      
      if (info)
        {
          log_debug ("STR", info);
          rc = gpgrt_asprintf (&command, "STR", info);
          if (rc < 0)
            return gpg_error (gpg_err_code_from_errno (errno));
          rc = assuan_inquire (ctx, command, &value, &valuelen, MAXLEN_PIN);
          xfree (command);
        }
      else
        {
          log_debug ("STR");
          rc = assuan_inquire (ctx, "STR",
                               &value, &valuelen, MAXLEN_PIN);
        }
      if (!rc)
        xfree (value);
      return rc;
    }

  *retstr = NULL;
  log_debug ("STR", info);

  rc = gpgrt_asprintf (&command, "STR", info);
  if (rc < 0)
    return gpg_error (gpg_err_code_from_errno (errno));

  
  rc = assuan_inquire (ctx, command, &value, &valuelen, MAXLEN_PIN);
  xfree (command);
  if (rc)
    return rc;

  if (!valuelen || value[valuelen-1])
    {
      
      xfree (value);
      return gpg_error (GPG_ERR_INV_RESPONSE);
    }
  *retstr = (char*)value;
  return 0;
}