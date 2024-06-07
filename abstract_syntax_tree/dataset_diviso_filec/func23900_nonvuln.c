setifs (v)
     SHELL_VAR *v;
{
  char *t;
  unsigned char uc;

  ifs_var = v;
  ifs_value = (v && value_cell (v)) ? value_cell (v) : "STR";

  ifs_is_set = ifs_var != 0;
  ifs_is_null = ifs_is_set && (*ifs_value == 0);

  
  memset (ifs_cmap, '\0', sizeof (ifs_cmap));
  for (t = ifs_value ; t && *t; t++)
    {
      uc = *t;
      ifs_cmap[uc] = 1;
    }

#if defined (HANDLE_MULTIBYTE)
  if (ifs_value == 0)
    {
      ifs_firstc[0] = '\0';
      ifs_firstc_len = 1;
    }
  else
    {
      size_t ifs_len;
      ifs_len = strnlen (ifs_value, MB_CUR_MAX);
      ifs_firstc_len = MBLEN (ifs_value, ifs_len);
      if (ifs_firstc_len == 1 || ifs_firstc_len == 0 || MB_INVALIDCH (ifs_firstc_len))
	{
	  ifs_firstc[0] = ifs_value[0];
	  ifs_firstc[1] = '\0';
	  ifs_firstc_len = 1;
	}
      else
	memcpy (ifs_firstc, ifs_value, ifs_firstc_len);
    }
#else
  ifs_firstc = ifs_value ? *ifs_value : 0;
#endif
}