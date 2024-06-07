finish_headers (CockpitWebResponse *self,
                GString *string,
                gssize length,
                gint status,
                guint seen)
{
  const gchar *content_type;

  
  if ((seen & HEADER_CONTENT_TYPE) == 0 &&
      self->full_path != NULL && status >= 200 && status <= 299)
    {
      content_type = cockpit_web_response_content_type (self->full_path);
      if (content_type)
        g_string_append_printf (string, "STR", content_type);
    }

  if (status != 304)
    {
      if (length < 0 || seen & HEADER_CONTENT_ENCODING || self->filters)
        {
          self->chunked = TRUE;
          g_string_append_printf (string, "STR");
        }
      else
        {
          self->chunked = FALSE;
          g_string_append_printf (string, "STR", length);
          self->out_queueable = length;
        }
    }

  if ((seen & HEADER_CACHE_CONTROL) == 0 && status >= 200 && status <= 299)
    {
      if (self->cache_type == COCKPIT_WEB_RESPONSE_CACHE_FOREVER)
        g_string_append (string, "STR");
      else if (self->cache_type == COCKPIT_WEB_RESPONSE_NO_CACHE)
        g_string_append (string, "STR");
      else if (self->cache_type == COCKPIT_WEB_RESPONSE_CACHE_PRIVATE)
        g_string_append (string, "STR");
    }

  if ((seen & HEADER_VARY) == 0 && status >= 200 && status <= 299 &&
      self->cache_type == COCKPIT_WEB_RESPONSE_CACHE_PRIVATE)
    {
      g_string_append (string, "STR");
    }

  if (!self->keep_alive)
    g_string_append (string, "STR");

  
  if ((seen & HEADER_DNS_PREFETCH_CONTROL) == 0)
    g_string_append (string, "STR");
  if ((seen & HEADER_REFERRER_POLICY) == 0)
    g_string_append (string, "STR");
  if ((seen & HEADER_CONTENT_TYPE_OPTIONS) == 0)
    g_string_append (string, "STR");
  
  if ((seen & HEADER_CROSS_ORIGIN_RESOURCE_POLICY) == 0)
    g_string_append (string, "STR");

  g_string_append (string, "STR");
  return g_string_free_to_bytes (string);
}