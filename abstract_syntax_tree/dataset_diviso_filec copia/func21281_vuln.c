parse_keyserver_line (char *line,
		      const char *filename, unsigned int lineno)
{
  char *p;
  char *endp;
  struct keyserver_spec *server;
  int fieldno;
  int fail = 0;

  
  server = xcalloc (1, sizeof *server);
  for (fieldno = 1, p = line; p; p = endp, fieldno++ )
    {
      endp = strchr (p, ':');
      if (endp)
	*endp++ = '\0';
      trim_spaces (p);
      switch (fieldno)
	{
	case 1:
	  if (*p)
	    server->host = xstrdup (p);
	  else
	    {
	      log_error (_("STR"),
			 filename, lineno);
	      fail = 1;
	    }
	  break;

	case 2:
	  if (*p)
	    server->port = atoi (p);
	  break;

	case 3:
	  if (*p)
	    server->user = xstrdup (p);
	  break;

	case 4:
	  if (*p && !server->user)
	    {
	      log_error (_("STR"),
			 filename, lineno);
	      fail = 1;
	    }
	  else if (*p)
	    server->pass = xstrdup (p);
	  break;

	case 5:
	  if (*p)
	    server->base = xstrdup (p);
	  break;

	default:
	  
	  break;
	}
    }

  if (fail)
    {
      log_info (_("STR"), filename, lineno);
      keyserver_list_free (server);
    }

  return server;
}