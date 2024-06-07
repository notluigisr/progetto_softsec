void CLASS merror (void *ptr, const char *where)
{
  if (ptr) return;
  fprintf (stderr,_("STR"), ifname, where);
  longjmp (failure, 1);
}