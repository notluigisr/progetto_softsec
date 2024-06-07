static size_t escape_string (char *dst, size_t len, const char* src)
{
  char* p = dst;

  if (!len)
    return 0;
  len--; 

  while (p - dst < len && src && *src)
  {
    switch (*src)
    {
    case '\n':
      ESC_CHAR('n');
      break;
    case '\r':
      ESC_CHAR('r');
      break;
    case '\t':
      ESC_CHAR('t');
      break;
    default:
      if ((*src == '\\' || *src == '"') && p - dst < len - 1)
	*p++ = '\\';
      *p++ = *src;
    }
    src++;
  }
#undef ESC_CHAR
  *p = '\0';
  return p - dst;
}