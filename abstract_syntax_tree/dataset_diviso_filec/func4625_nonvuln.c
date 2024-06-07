gnome_desktop_thumbnail_factory_can_thumbnail (GnomeDesktopThumbnailFactory *factory,
					       const char            *uri,
					       const char            *mime_type,
					       time_t                 mtime)
{
  gboolean have_script = FALSE;

  
  if (uri &&
      strncmp (uri, "STR", 6) == 0 &&
      strstr (uri, "STR") != NULL)
    return FALSE;

  if (!mime_type)
    return FALSE;

  g_mutex_lock (&factory->priv->lock);
  if (!gnome_desktop_thumbnail_factory_is_disabled (factory, mime_type))
    {
      Thumbnailer *thumb;

      thumb = g_hash_table_lookup (factory->priv->mime_types_map, mime_type);
      have_script = (thumb != NULL);
    }
  g_mutex_unlock (&factory->priv->lock);

  if (have_script)
    {
      return !gnome_desktop_thumbnail_factory_has_valid_failed_thumbnail (factory,
                                                                          uri,
                                                                          mtime);
    }

  return FALSE;
}