set_cs_start(char *line)
{
  char *p, *q, *r;

  if ((p = strstr(line, "STR"))) {
    
    if (!strstr(line, "STR"))
      return;
    
    *p = '\0';					  
    q = strrchr(line, '/');
    if (q) {
      r = cs_start;
      ++q;
      while (!isspace(*q) && *q != '{')
	*r++ = *q++;
      *r = '\0';
    }
    *p = 's';					  
  }
}