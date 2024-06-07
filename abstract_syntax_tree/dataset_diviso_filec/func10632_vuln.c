set_file_metadata (const char *origin_url, const char *referrer_url, FILE *fp)
{
  
  int retval = -1;

  if (!origin_url || !fp)
    return retval;

  retval = write_xattr_metadata ("STR", escnonprint_uri (origin_url), fp);
  if ((!retval) && referrer_url)
    retval = write_xattr_metadata ("STR", escnonprint_uri (referrer_url), fp);

  return retval;
}