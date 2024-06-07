plugin_name (struct backend *b)
{
  return b->next->plugin_name (b->next);
}