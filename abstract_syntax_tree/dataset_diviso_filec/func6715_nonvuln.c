static char **mask_password(int argc, char ***argv)
{
  char **temp_argv;
  temp_argv= (char **)(my_malloc(sizeof(char *) * argc, MYF(MY_WME)));
  argc--;
  while (argc > 0)
  {
    temp_argv[argc]= my_strdup((*argv)[argc], MYF(MY_FAE));
    if (find_type((*argv)[argc - 1],&command_typelib, FIND_TYPE_BASIC) == ADMIN_PASSWORD ||
        find_type((*argv)[argc - 1],&command_typelib, FIND_TYPE_BASIC) == ADMIN_OLD_PASSWORD)
    {
      char *start= (*argv)[argc];
      while (*start)
        *start++= 'x';
      start= (*argv)[argc];
      if (*start)
        start[1]= 0;                         
     }
    argc--;
  }
  temp_argv[argc]= my_strdup((*argv)[argc], MYF(MY_FAE));
  return(temp_argv);
}