static int add_quoted_string(File fptr, const char *quotestr)
{
  String orgstr(quotestr, system_charset_info);
  String escapedstr;
  int err= add_string(fptr, "STR");
  err+= append_escaped(&escapedstr, &orgstr);
  err+= add_string(fptr, escapedstr.c_ptr_safe());
  return err + add_string(fptr, "STR");
}