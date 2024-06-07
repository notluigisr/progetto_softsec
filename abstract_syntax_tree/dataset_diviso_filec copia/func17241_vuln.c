static const char* fix_identifier_with_newline(char* object_name)
{
  static char buff[COMMENT_LENGTH]= {0};
  char *ptr= buff;
  memset(buff, 0, 255);
  while(*object_name)
  {
    *ptr++ = *object_name;
    if (*object_name == '\n')
      ptr= strmov(ptr, "STR");
    object_name++;
  }
  return buff;
}