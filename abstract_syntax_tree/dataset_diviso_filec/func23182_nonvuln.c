print_script_debug (GStrv expanded_script)
{
  GString *out;
  guint i;

  out = g_string_new (NULL);

  for (i = 0; expanded_script[i]; i++)
    g_string_append_printf (out, "STR", expanded_script[i]);
  g_string_append_printf (out, "STR");

  g_debug ("STR", out->str);
  g_string_free (out, TRUE);
}