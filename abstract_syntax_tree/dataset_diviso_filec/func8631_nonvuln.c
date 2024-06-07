m4_translit (struct obstack *obs, int argc, token_data **argv)
{
  const char *data;
  const char *from;
  const char *to;
  char map[256] = {0};
  char found[256] = {0};
  unsigned char ch;

  if (bad_argc (argv[0], argc, 3, 4))
    {
      
      if (argc == 2)
	obstack_grow (obs, ARG (1), strlen (ARG (1)));
      return;
    }

  from = ARG (2);
  if (strchr (from, '-') != NULL)
    {
      from = expand_ranges (from, obs);
      if (from == NULL)
	return;
    }

  to = ARG (3);
  if (strchr (to, '-') != NULL)
    {
      to = expand_ranges (to, obs);
      if (to == NULL)
	return;
    }

  
  for ( ; (ch = *from) != '\0'; from++)
    {
      if (! found[ch])
	{
	  found[ch] = 1;
	  map[ch] = *to;
	}
      if (*to != '\0')
	to++;
    }

  for (data = ARG (1); (ch = *data) != '\0'; data++)
    {
      if (! found[ch])
	obstack_1grow (obs, ch);
      else if (map[ch])
	obstack_1grow (obs, map[ch]);
    }
}