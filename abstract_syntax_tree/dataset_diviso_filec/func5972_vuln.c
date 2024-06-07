ephy_string_shorten (char  *str,
                     gsize  target_length)
{
  char *new_str;
  glong actual_length;
  gulong bytes;

  g_assert (target_length > 0);

  if (!str)
    return NULL;

  
  actual_length = g_utf8_strlen (str, -1);

  
  if ((gsize)actual_length <= target_length)
    return str;

  
  bytes = GPOINTER_TO_UINT (g_utf8_offset_to_pointer (str, target_length - 1) - str);

  
  new_str = g_new (gchar, bytes + 1 + 1);

  strncpy (new_str, str, bytes);
  strcat (new_str, "STR");

  g_free (str);

  return new_str;
}