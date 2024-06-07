strv_have_prefix (gchar **strv,
                  const gchar *prefix)
{
  gint i;

  for (i = 0; strv && strv[i] != NULL; i++)
    {
      if (g_str_has_prefix (strv[i], prefix))
        return TRUE;
    }
  return FALSE;
}