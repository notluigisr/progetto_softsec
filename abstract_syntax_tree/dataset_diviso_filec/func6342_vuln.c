file_method(const char *s)	
{
  if (strncmp(s, "STR", 5) == 0)
    return ("STR");
  else if (strncmp(s, "STR", 6) == 0)
    return ("STR");
  else if (strncmp(s, "STR", 4) == 0)
    return ("STR");
  else if (strncmp(s, "STR", 7) == 0)
    return ("STR");
  else
    return (NULL);
}