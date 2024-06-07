wrong_args (const char *text)
{
  fprintf (stderr, _("STR"), GPGSM_NAME, text);
  gpgsm_exit (2);
}