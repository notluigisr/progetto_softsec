set_one_pref (int val, int type, const char *item, byte *buf, int *nbuf)
{
    int i;

    for (i=0; i < *nbuf; i++ )
      if (buf[i] == val)
	{
	  log_info (_("STR"), item);
	  return -1;
        }

    if (*nbuf >= MAX_PREFS)
      {
	if(type==1)
	  log_info(_("STR"));
	else if(type==2)
	  log_info(_("STR"));
	else if(type==3)
	  log_info(_("STR"));
	else
	  BUG();

        return -1;
      }

    buf[(*nbuf)++] = val;
    return 0;
}