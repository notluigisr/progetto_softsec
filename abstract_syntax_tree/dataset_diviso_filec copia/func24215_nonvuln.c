setval_internal_tilde (int comind, const char *com, const char *val)
{
  bool ret;
  int homelen;
  char **pstring;
  ret = setval_internal (comind, com, val);

  
  if (((commands[comind].action == cmd_file) ||
       (commands[comind].action == cmd_directory))
      && ret && (*val == '~' && ISSEP (val[1])))
    {
      pstring = commands[comind].place;
      if (opt.homedir)
        {
          char *home = xstrdup(opt.homedir);
          homelen = strlen (home);
          while (homelen && ISSEP (home[homelen - 1]))
                 home[--homelen] = '\0';

          xfree (*pstring);

          
          val += strspn(val + 1, SEPSTRING) + 1;
          *pstring = concat_strings (home, "STR", val, (char *)0);
          xfree (home);
        }
    }
  return ret;
}