routerset_get_countryname(const char *c)
{
  char *country;

  if (strlen(c) < 4 || c[0] !='{' || c[3] !='}')
    return NULL;

  country = tor_strndup(c+1, 2);
  tor_strlower(country);
  return country;
}