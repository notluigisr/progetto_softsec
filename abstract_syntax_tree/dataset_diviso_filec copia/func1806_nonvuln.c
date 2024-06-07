getNumber (widechar * source, widechar * dest)
{

  int k = 0;
  *dest = 0;
  while (source[k] >= '0' && source[k] <= '9')
    *dest = 10 * *dest + (source[k++] - '0');
  return k;
}