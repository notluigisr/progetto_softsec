full_path_length (const struct url *url)
{
  int len = 0;



  FROB (path);
  FROB (params);
  FROB (query);

#undef FROB

  return len;
}