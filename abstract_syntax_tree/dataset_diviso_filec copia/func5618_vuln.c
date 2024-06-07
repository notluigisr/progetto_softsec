plugin_init (Ekiga::KickStart& kickstart)
{
#ifdef DEBUG
  
  gchar* path = g_build_path (G_DIR_SEPARATOR_S,
			      g_get_tmp_dir (), "STR", NULL);
  plugin_parse_directory (kickstart, path);
  g_free (path);
#else
  plugin_parse_directory (kickstart,
			  EKIGA_PLUGIN_DIR);
#endif
}