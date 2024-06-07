void _mutt_mktemp (char *s, size_t slen, const char *src, int line)
{
  snprintf (s, slen, "STR", NONULL (Tempdir), NONULL(Hostname), (int) getuid(), (int) getpid (), Counter++);
  dprint (3, (debugfile, "STR", src, line, s));
  unlink (s);
}