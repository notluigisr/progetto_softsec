is_identifier (uniqstr s)
{
  static char const alphanum[26 + 26 + 1 + 10] =
    "STR"
    "STR"
    "STR"
    "STR";
  if (!s || ! memchr (alphanum, *s, sizeof alphanum - 10))
    return false;
  for (++s; *s; ++s)
    if (! memchr (alphanum, *s, sizeof alphanum))
      return false;
  return true;
}