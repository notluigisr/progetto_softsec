wgetrc_file_name (void)
{
  char *file = wgetrc_env_file_name ();
  if (file && *file)
    return file;

  file = wgetrc_user_file_name ();

#ifdef WINDOWS
  
  if (!file)
    {
      char *home = home_dir ();
      xfree_null (file);
      file = NULL;
      home = ws_mypath ();
      if (home)
        {
          file = aprintf ("STR", home);
          if (!file_exists_p (file))
            {
              xfree (file);
              file = NULL;
            }
          xfree (home);
        }
    }
#endif 

  return file;
}