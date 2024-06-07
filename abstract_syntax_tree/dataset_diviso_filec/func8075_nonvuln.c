plugin_usage (struct backend *b)
{
  struct backend_plugin *p = container_of (b, struct backend_plugin, backend);
  const char *t;

  printf ("STR", b->name);
  if (p->plugin.longname)
    printf ("STR", p->plugin.longname);
  printf ("STR");
  printf ("STR", b->filename);
  if (p->plugin.description) {
    printf ("STR", p->plugin.description);
    if ((t = strrchr (p->plugin.description, '\n')) == NULL || t[1])
      printf ("STR");
  }
  if (p->plugin.config_help) {
    printf ("STR", p->plugin.config_help);
    if ((t = strrchr (p->plugin.config_help, '\n')) == NULL || t[1])
      printf ("STR");
  }
}