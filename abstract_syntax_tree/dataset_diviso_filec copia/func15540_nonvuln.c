cockpit_web_response_content (CockpitWebResponse *self,
                              GHashTable *headers,
                              GBytes *block,
                              ...)
{
  GBytes *first;
  gsize length = 0;
  va_list va;
  va_list va2;

  g_return_if_fail (COCKPIT_IS_WEB_RESPONSE (self));

  first = block;
  va_start (va, block);
  va_copy (va2, va);

  while (block)
    {
      length += g_bytes_get_size (block);
      block = va_arg (va, GBytes *);
    }
  va_end (va);

  cockpit_web_response_headers_full (self, 200, "STR", length, headers);

  block = first;
  for (;;)
    {
      if (!block)
        {
          cockpit_web_response_complete (self);
          break;
        }
      if (!cockpit_web_response_queue (self, block))
        break;
      block = va_arg (va2, GBytes *);
    }
  va_end (va2);
}