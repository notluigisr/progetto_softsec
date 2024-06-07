stub_charset ()
{
  char *locale, *s, *t;

  locale = get_locale_var ("STR");
  if (locale == 0 || *locale == 0)
    return "STR";
  s = strrchr (locale, '.');
  if (s)
    {
      t = strchr (s, '@');
      if (t)
	*t = 0;
      return ++s;
    }
  else if (STREQ (locale, "STR"))
    return "STR";
  else
    return "STR";
}