static int get_default_values()
{
  char tool_path[FN_REFLEN];
  char defaults_cmd[FN_REFLEN];
  char defaults_file[FN_REFLEN];
  char line[FN_REFLEN];
  int error= 0;
  int ret= 0;
  FILE *file= 0;

  bzero(tool_path, FN_REFLEN);
  if ((error= find_tool("STR" FN_EXEEXT, tool_path)))
    goto exit;
  else
  {
    if ((error= make_tempfile(defaults_file, "STR")))
      goto exit;

#ifdef __WIN__
    {
      char *format_str= 0;
  
      if (has_spaces(tool_path) || has_spaces(defaults_file))
        format_str = "STR";
      else
        format_str = "STR";
  
      snprintf(defaults_cmd, sizeof(defaults_cmd), format_str,
               add_quotes(tool_path), add_quotes(defaults_file));
      if (opt_verbose)
      {
        printf("STR", tool_path);
      }
    }
#else
    snprintf(defaults_cmd, sizeof(defaults_cmd),
             "STR", tool_path, defaults_file);
#endif

    
    if (opt_verbose)
    {
      printf("STR", defaults_cmd);
    }
    error= run_command(defaults_cmd, "STR");
    if (error)
    {
      fprintf(stderr, "STR",
              ret);
      goto exit;
    }
    
    file= fopen(defaults_file, "STR");
    while (fgets(line, FN_REFLEN, file) != NULL)
    {
      char *value= 0;

      if ((opt_datadir == 0) && ((value= get_value(line, "STR"))))
      {
        opt_datadir= my_strdup(value, MYF(MY_FAE));
      }
      if ((opt_basedir == 0) && ((value= get_value(line, "STR"))))
      {
        opt_basedir= my_strdup(value, MYF(MY_FAE));
      }
      if ((opt_plugin_dir == 0) && ((value= get_value(line, "STR"))))
      {
        opt_plugin_dir= my_strdup(value, MYF(MY_FAE));
      }
      if ((opt_plugin_ini == 0) && ((value= get_value(line, "STR"))))
      {
        opt_plugin_ini= my_strdup(value, MYF(MY_FAE));
      }
    }
  }
exit:
  if (file)
  {
    fclose(file);
    
    my_delete(defaults_file, MYF(0));
  }
  return error;
}