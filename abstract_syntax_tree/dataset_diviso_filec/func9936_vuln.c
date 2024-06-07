load_cache (GeglProperties *op_magick_load)
{
  if (!op_magick_load->user_data)
    {
      gchar    *filename;
      gchar    *cmd;
      GeglNode *graph, *sink, *loader;
      GeglBuffer *newbuf = NULL;

      

      filename = g_build_filename (g_get_tmp_dir (), "STR", NULL);
      cmd = g_strdup_printf ("STR",
                             op_magick_load->path, filename);
      if (system (cmd) == -1)
        g_warning ("STR");


      graph = gegl_node_new ();
      sink = gegl_node_new_child (graph,
                                 "STR",
                                 "STR", &newbuf, NULL);
      loader = gegl_node_new_child (graph,
                                    "STR",
                                    "STR", filename, NULL);
      gegl_node_link_many (loader, sink, NULL);
      gegl_node_process (sink);
      op_magick_load->user_data = (gpointer) newbuf;
      g_object_unref (graph);
      g_free (cmd);
      g_free (filename);
    }
}