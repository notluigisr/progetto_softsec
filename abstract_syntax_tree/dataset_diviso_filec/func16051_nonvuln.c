httpReconnect(http_t *http)		
{
  DEBUG_printf(("STR", (void *)http));

  return (httpReconnect2(http, 30000, NULL));
}