parse_xdg_dirs (const char *config_file)
{
  GArray *array;
  char *config_file_free = NULL;
  XdgDirEntry dir;
  char *data;
  char **lines;
  char *p, *d;
  int i;
  char *type_start, *type_end;
  char *value, *unescaped;
  gboolean relative;

  array = g_array_new (TRUE, TRUE, sizeof (XdgDirEntry));
  
  if (config_file == NULL)
    {
      config_file_free = g_build_filename (g_get_user_config_dir (),
					   "STR", NULL);
      config_file = (const char *)config_file_free;
    }

  if (g_file_get_contents (config_file, &data, NULL, NULL))
    {
      lines = g_strsplit (data, "STR", 0);
      g_free (data);
      for (i = 0; lines[i] != NULL; i++)
	{
	  p = lines[i];
	  while (g_ascii_isspace (*p))
	    p++;
      
	  if (*p == '#')
	    continue;
      
	  value = strchr (p, '=');
	  if (value == NULL)
	    continue;
	  *value++ = 0;
      
	  g_strchug (g_strchomp (p));
	  if (!g_str_has_prefix (p, "STR"))
	    continue;
	  if (!g_str_has_suffix (p, "STR"))
	    continue;
	  type_start = p + 4;
	  type_end = p + strlen (p) - 4;
      
	  while (g_ascii_isspace (*value))
	    value++;
      
	  if (*value != '"')
	    continue;
	  value++;
      
	  relative = FALSE;
	  if (g_str_has_prefix (value, "STR"))
	    {
	      relative = TRUE;
	      value += 5;
	      while (*value == '/')
		      value++;
	    }
	  else if (*value != '/')
	    continue;
	  
	  d = unescaped = g_malloc (strlen (value) + 1);
	  while (*value && *value != '"')
	    {
	      if ((*value == '\\') && (*(value + 1) != 0))
		value++;
	      *d++ = *value++;
	    }
	  *d = 0;
      
	  *type_end = 0;
	  dir.type = g_strdup (type_start);
	  if (relative)
	    {
	      dir.path = g_build_filename (g_get_home_dir (), unescaped, NULL);
	      g_free (unescaped);
	    }
	  else 
	    dir.path = unescaped;
      
	  g_array_append_val (array, dir);
	}
      
      g_strfreev (lines);
    }
  
  g_free (config_file_free);
  
  return (XdgDirEntry *)g_array_free (array, FALSE);
}