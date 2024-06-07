check (int experr, const char *prefix)
{
  const char *msg = nbd_get_error ();
  int errnum = nbd_get_errno ();

  fprintf (stderr, "STR", msg);
  fprintf (stderr, "STR", errnum, strerror (errnum));
  if (strncmp (msg, prefix, strlen (prefix)) != 0) {
    fprintf (stderr, "STR",
             progname, msg);
    exit (EXIT_FAILURE);
  }
  if (errnum != experr) {
    fprintf (stderr, "STR"
             "STR",
             progname, experr, strerror (experr), errnum);
    exit (EXIT_FAILURE);
  }
}