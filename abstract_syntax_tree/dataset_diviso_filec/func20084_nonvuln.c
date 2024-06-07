get_sig_counter (app_t app)
{
  void *relptr;
  unsigned char *value;
  size_t valuelen;
  unsigned long ul;

  relptr = get_one_do (app, 0x0093, &value, &valuelen, NULL);
  if (!relptr)
    return 0;
  ul = convert_sig_counter_value (value, valuelen);
  xfree (relptr);
  return ul;
}