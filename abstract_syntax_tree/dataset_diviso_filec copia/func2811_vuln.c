static int process_options(int argc, char *argv[], char *operation)
{
  int error= 0;
  int i= 0;
  
  
  if ((error= handle_options(&argc, &argv, my_long_options, get_one_option)))
    goto exit;

  
  if (opt_print_defaults)
  {
    error= -1;
    goto exit;
  }

  
  if (opt_basedir)
  {
    i= (int)strlength(opt_basedir);
    if (opt_basedir[i-1] != FN_LIBCHAR || opt_basedir[i-1] != FN_LIBCHAR2)
    {
      char buff[FN_REFLEN];
      
      strncpy(buff, opt_basedir, sizeof(buff) - 1);
#ifdef __WIN__
      strncat(buff, "STR", sizeof(buff) - strlen(buff) - 1);
#else
      strncat(buff, FN_DIRSEP, sizeof(buff) - strlen(buff) - 1);
#endif
      buff[sizeof(buff) - 1]= 0;
      my_free(opt_basedir);
      opt_basedir= my_strdup(buff, MYF(MY_FAE));
    }
  }
  
  
  if (!opt_no_defaults && ((error= get_default_values())))
  {
    error= -1;
    goto exit;
  }

  
  strcpy(operation, "");
  if ((error = check_options(argc, argv, operation)))
  {
    goto exit;
  }

  if (opt_verbose)
  {
    printf("STR", opt_basedir);
    printf("STR", opt_plugin_dir);
    printf("STR", opt_datadir);
    printf("STR", opt_plugin_ini);
  }

exit:
  return error;
}