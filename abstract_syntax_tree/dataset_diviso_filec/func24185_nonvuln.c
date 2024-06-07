cgi_initialize_cookies(void)
{
  const char	*cookie;		
  char		name[128],		
		value[512],		
		*ptr;			


  if ((cookie = getenv("STR")) == NULL)
    return;

  while (*cookie)
  {
    int	skip = 0;			

   

    while (isspace(*cookie & 255))
      cookie ++;
    if (!*cookie)
      break;

   

    for (ptr = name; *cookie && *cookie != '=';)
      if (ptr < (name + sizeof(name) - 1))
      {
        *ptr++ = *cookie++;
      }
      else
      {
        skip = 1;
	cookie ++;
      }

    if (*cookie != '=')
      break;

    *ptr = '\0';
    cookie ++;

   

    if (*cookie == '\"')
    {
      for (cookie ++, ptr = value; *cookie && *cookie != '\"';)
        if (ptr < (value + sizeof(value) - 1))
	{
	  *ptr++ = *cookie++;
	}
	else
	{
	  skip = 1;
	  cookie ++;
	}

      if (*cookie == '\"')
        cookie ++;
      else
        skip = 1;
    }
    else
    {
      for (ptr = value; *cookie && *cookie != ';';)
        if (ptr < (value + sizeof(value) - 1))
	{
	  *ptr++ = *cookie++;
	}
	else
	{
	  skip = 1;
	  cookie ++;
	}
    }

    if (*cookie == ';')
      cookie ++;
    else if (*cookie)
      skip = 1;

    *ptr = '\0';

   

    if (name[0] != '$' && !skip)
      num_cookies = cupsAddOption(name, value, num_cookies, &cookies);
  }
}