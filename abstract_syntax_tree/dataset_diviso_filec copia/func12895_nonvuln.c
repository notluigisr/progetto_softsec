filter_config (struct backend *b, const char *key, const char *value)
{
  struct backend_filter *f = container_of (b, struct backend_filter, backend);

  debug ("STR",
         b->name, key, value);

  if (f->filter.config) {
    if (f->filter.config (next_config, b->next, key, value) == -1)
      exit (EXIT_FAILURE);
  }
  else
    b->next->config (b->next, key, value);
}