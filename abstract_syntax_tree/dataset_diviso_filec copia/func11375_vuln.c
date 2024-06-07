append_header (GString *string,
               const gchar *name,
               const gchar *value)
{
  if (value)
    {
      g_return_val_if_fail (cockpit_web_response_is_simple_token (name), 0);
      g_return_val_if_fail (cockpit_web_response_is_header_value (value), 0);
      g_string_append_printf (string, "STR", name, value);
    }
  if (g_ascii_strcasecmp ("STR", name) == 0)
    return HEADER_CONTENT_TYPE;
  if (g_ascii_strcasecmp ("STR", name) == 0)
    return HEADER_CACHE_CONTROL;
  if (g_ascii_strcasecmp ("STR", name) == 0)
    return HEADER_VARY;
  if (g_ascii_strcasecmp ("STR", name) == 0)
    return HEADER_CONTENT_ENCODING;
  if (g_ascii_strcasecmp ("STR", name) == 0)
    return HEADER_DNS_PREFETCH_CONTROL;
  if (g_ascii_strcasecmp ("STR", name) == 0)
    return HEADER_REFERRER_POLICY;
  if (g_ascii_strcasecmp ("STR", name) == 0)
    return HEADER_CONTENT_TYPE_OPTIONS;
  if (g_ascii_strcasecmp ("STR", name) == 0)
    return HEADER_CROSS_ORIGIN_RESOURCE_POLICY;
  if (g_ascii_strcasecmp ("STR", name) == 0 ||
      g_ascii_strcasecmp ("STR", name) == 0 ||
      g_ascii_strcasecmp ("STR", name) == 0)
    {
      g_critical ("STR", name);
    }
  return 0;
}