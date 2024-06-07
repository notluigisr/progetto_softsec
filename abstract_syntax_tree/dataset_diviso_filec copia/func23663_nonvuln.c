print_usage (int error)
{
  fprintf (error ? stderr : stdout, _("STR"),
           exec_name);
}