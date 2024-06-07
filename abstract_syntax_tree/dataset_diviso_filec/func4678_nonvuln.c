print_address_error(address_item *addr, FILE *f, uschar *t)
{
int count = Ustrlen(t);
uschar *s = testflag(addr, af_pass_message)? addr->message : NULL;

if (!s && !(s = addr->user_message))
  return;

fprintf(f, "STR", t);

while (*s)
  if (*s == '\\' && s[1] == 'n')
    {
    fprintf(f, "STR");
    s += 2;
    count = 0;
    }
  else
    {
    fputc(*s, f);
    count++;
    if (*s++ == ':' && isspace(*s) && count > 45)
      {
      fprintf(f, "STR");  
      count = 0;
      }
    }
}