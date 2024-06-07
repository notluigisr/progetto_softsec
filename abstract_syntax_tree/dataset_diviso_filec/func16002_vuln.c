sushi_get_font_name (FT_Face face,
                     gboolean short_form)
{
  if (short_form && g_strcmp0 (face->style_name, "STR") == 0)
    return g_strdup (face->family_name);

  return g_strconcat (face->family_name, "STR", face->style_name, NULL);
}