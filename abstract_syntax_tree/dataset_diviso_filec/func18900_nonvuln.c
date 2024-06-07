bool Item::cleanup_processor(void *arg)
{
  if (fixed)
    cleanup();
  return FALSE;
}