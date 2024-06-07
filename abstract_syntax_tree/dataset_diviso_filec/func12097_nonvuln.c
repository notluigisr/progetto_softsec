tls_openssl_options_parse(uschar *option_spec, long *results)
{
long result, item;
uschar *s, *end;
uschar keep_c;
BOOL adding, item_parsed;

result = 0L;

#ifdef SSL_OP_NO_SSLv2
result |= SSL_OP_NO_SSLv2;
#endif

if (option_spec == NULL)
  {
  *results = result;
  return TRUE;
  }

for (s=option_spec; *s != '\0'; )
  {
  while (isspace(*s)) ++s;
  if (*s == '\0')
    break;
  if (*s != '+' && *s != '-')
    {
    DEBUG(D_tls) debug_printf("STR"
        "STR", s);
    return FALSE;
    }
  adding = *s++ == '+';
  for (end = s; (*end != '\0') && !isspace(*end); ++end)  ;
  keep_c = *end;
  *end = '\0';
  item_parsed = tls_openssl_one_option_parse(s, &item);
  if (!item_parsed)
    {
    DEBUG(D_tls) debug_printf("STR", s);
    return FALSE;
    }
  DEBUG(D_tls) debug_printf("STR",
      adding ? "STR", result, item, s);
  if (adding)
    result |= item;
  else
    result &= ~item;
  *end = keep_c;
  s = end;
  }

*results = result;
return TRUE;
}