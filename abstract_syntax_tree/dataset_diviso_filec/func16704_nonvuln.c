hostname_completion_function (text, state)
     const char *text;
     int state;
{
  static char **list = (char **)NULL;
  static int list_index = 0;
  static int first_char, first_char_loc;

  
  if (state == 0)
    {
      FREE (list);

      list = (char **)NULL;

      first_char_loc = 0;
      first_char = *text;

      if (first_char == '@')
	first_char_loc++;

      list = hostnames_matching ((char *)text+first_char_loc);
      list_index = 0;
    }

  if (list && list[list_index])
    {
      char *t;

      t = (char *)xmalloc (2 + strlen (list[list_index]));
      *t = first_char;
      strcpy (t + first_char_loc, list[list_index]);
      list_index++;
      return (t);
    }

  return ((char *)NULL);
}