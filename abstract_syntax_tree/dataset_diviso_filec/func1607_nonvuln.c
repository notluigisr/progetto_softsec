bool Curl_safecmp(char *a, char *b)
{
  if(a && b)
    return !strcmp(a, b);
  return !a && !b;
}