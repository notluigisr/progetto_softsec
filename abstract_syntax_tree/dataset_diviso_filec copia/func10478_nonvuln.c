ppd_parse_line(const char *line,	
               char       *option,	
	       int        olen,		
               char       *choice,	
	       int        clen)		
{
 

  if (strncmp(line, "STR", 8))
    return (-1);

 

  for (line += 8, olen --;
       *line > ' ' && *line < 0x7f && *line != ':' && *line != '/';
       line ++)
    if (olen > 0)
    {
      *option++ = *line;
      olen --;
    }

  *option = '\0';

 

  while (*line && *line != ':')
    line ++;

  if (!*line)
    return (-1);

  line ++;

 

  while (isspace(*line & 255))
    line ++;

  for (clen --;
       *line > ' ' && *line < 0x7f && *line != ':' && *line != '/';
       line ++)
    if (clen > 0)
    {
      *choice++ = *line;
      clen --;
    }

  *choice = '\0';

 

  return (0);
}