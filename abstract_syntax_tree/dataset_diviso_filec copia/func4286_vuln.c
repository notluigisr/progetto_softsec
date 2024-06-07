static int nntp_hcache_namer(const char *path, char *dest, size_t destlen)
{
  return snprintf(dest, destlen, "STR", path);
}