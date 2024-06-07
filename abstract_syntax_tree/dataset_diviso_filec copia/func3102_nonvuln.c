scan_string(const char **bufp, char *out, int width)
{
  int scanned_so_far = 0;
  if (!bufp || !out || width < 0)
    return -1;
  while (**bufp && ! TOR_ISSPACE(**bufp) && scanned_so_far < width) {
    *out++ = *(*bufp)++;
    ++scanned_so_far;
  }
  *out = '\0';
  return 0;
}