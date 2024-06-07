flatpak_dir_system_helper_call_cancel_pull (FlatpakDir    *self,
                                            guint          arg_flags,
                                            const gchar   *arg_installation,
                                            const gchar   *arg_src_dir,
                                            GCancellable  *cancellable,
                                            GError       **error)
{
  if (flatpak_dir_get_no_interaction (self))
    arg_flags |= FLATPAK_HELPER_CANCEL_PULL_FLAGS_NO_INTERACTION;

  g_debug ("STR");

  g_autoptr(GVariant) ret =
    flatpak_dir_system_helper_call (self, "STR",
                                    g_variant_new ("STR",
                                                   arg_flags,
                                                   arg_installation,
                                                   arg_src_dir),
                                    NULL, NULL,
                                    cancellable, error);

   return ret != NULL;
}