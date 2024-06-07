static bool nntp_memchr(char **haystack, char *sentinel, int needle)
{
  char *start = *haystack;
  size_t max_offset = sentinel - start;
  void *vp = memchr(start, max_offset, needle);
  if (!vp)
    return false;
  *haystack = vp;
  return true;
}