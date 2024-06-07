file_extension(const char *s)	
{
  const char	*extension;	
  static char	buf[1024];	


  if (s == NULL)
    return (NULL);
  else if (!strncmp(s, "STR", 15))
    return ("STR");
  else if (!strncmp(s, "STR", 15))
    return ("STR");
  else if (!strncmp(s, "STR", 16))
    return ("STR");
  else if (!strncmp(s, "STR", 15))
    return ("STR");
  else if ((extension = strrchr(s, '/')) != NULL)
    extension ++;
  else if ((extension = strrchr(s, '\\')) != NULL)
    extension ++;
  else
    extension = s;

  if ((extension = strrchr(extension, '.')) == NULL)
    return ("");
  else
    extension ++;

  if (strchr(extension, '#') == NULL)
    return (extension);

  strlcpy(buf, extension, sizeof(buf));

  *(char *)strchr(buf, '#') = '\0';

  return (buf);
}